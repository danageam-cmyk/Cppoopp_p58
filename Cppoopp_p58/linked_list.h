#pragma once
#include <format>
#include <iostream>
#include <stdexcept>

template<typename T>
struct ListNode {
	T data;
	ListNode* prev = NULL;
	ListNode* next = NULL;
};

template<typename T>
class LinkedList {
private:
	ListNode<T>* first = NULL;
	ListNode<T>* last = NULL;
	size_t size = 0;
public:
	void   add(T data);
	void   insertBefore(T data, size_t index);
	T      remove(size_t index);
	size_t getSize() const { return size; }

	void print();

	LinkedList<T>* clone() const;
	void clear();
	LinkedList() : first{ NULL }, last{ NULL }, size{0} { //
		

	}

	LinkedList(const LinkedList<T>& other) { // copy
		ListNode<T>* node = other.first;
		while (node) {
			this->add(node->data);
			node = node->next;
		}
	}

	LinkedList(LinkedList<T>&& other) : //move
		first{ other.first }, last{ other.last }, size{ other.size }
	{
		other.first = other.last = NULL;
	}


	LinkedList<T>& operator = (const LinkedList<T>& other) {
		//
		ListNode<T>* node = first;
		while (node) {
			first = first->next;
			delete node;
			node = first;
		}
		first = last = NULL;
		///
		node = other.first;
		while (node) {
			this->add(node->data);
			node = node->next;
		}
	}
	LinkedList<T>& operator = (LinkedList<T>&& other) {
		
	this->clear();
		ListNode<T>* node = first;
		while (node) {
			first = first->next;
			delete node;
			node = first;
		}
		first = last = NULL;

		while (node) {
			this->add(node->data);
			node = node->next;
		}
}
	



	~LinkedList() {   //destructor
		while (first) {
			last = first;
			first = first->next;
			delete last;
		}
	}
};

// #include "linked_list.cpp"

template<typename T>
LinkedList<T>* LinkedList<T>::clone() const {
	LinkedList<T>* res = new LinkedList<T>;
	ListNode<T>* node = this->first;
	while (node) {
		res->add(node->data);
		node = node->next;
	}
	return res;

}

template<typename T>
void LinkedList<T>::add(T data) {
	if (last) {  //                           |попередній = last
		last->next = new ListNode<T>{ data, last, NULL };
		last = last->next;
	}
	else {
		first = last = new ListNode<T>{ data, NULL, NULL };
	}
	size += 1;
}

template<typename T>
void LinkedList<T>::insertBefore(T data, size_t index) {
	if (index == 0) {
		// додавання в першу позицію (перед першим)
		if (first) {
			first = first->prev = new ListNode<T>{ data, NULL, first };
			size += 1;
		}
		else {
			add(data);
		}
	}
	else {
		if (index < size) {
			ListNode<T>* node = first;
			for (size_t i = 0; i < index - 1; ++i) {
				node = node->next;
			}
			// зупинились перед index, додаємо після нього
			node->next = new ListNode<T>{ data, node, node->next };
			node->next->next->prev = node->next;
			size += 1;
		}
		else {
			// помилка - index out of range
			throw std::range_error(
				std::format("LinkedList<T>::insertBefore: Unable to insert element. Max list index {} but got {}", size - 1, index)
			);
		}
	}
}

template<typename T>
void LinkedList<T>::print() {
	ListNode<T>* node = first;
	if (node == NULL) {
		std::cout << "Empty list, size = " << size << std::endl;
	}
	else {
		std::cout << size << " element(s): ";
		while (node) {
			std::cout << node->data << " ";
			node = node->next;
		}
		std::cout << std::endl;
	}
}

template<typename T>
T LinkedList<T>::remove(size_t index) {
	if (index < size) {
		if (index == 0) {  // видаляємо перший елемент
			ListNode<T>* node = first;  //  first                    last
			T data = node->data;		//   [p|0|n]<->[p|1|n]<->[p|2|n]
			first = first->next;		// NULL        f              NULL
			if (first) {				// first = first->next;
				first->prev = NULL;		// 
			}							//  first last
			delete node;				//   [p|0|n]
			size -= 1;					// NULL   NULL
			if (size == 0) {			// 
				last = NULL;			// 100   200   300  400  
			}							//  1     3     2    4   [200|4|NULL]
			return data;				// 
		}								// [NULL|1|300]  [100|2|200] [300|3|400]

		if (index == size - 1) {        // видаляємо останній елемент
			ListNode<T>* node = last;
			T data = node->data;
			last = last->prev;
			if (last) {
				last->next = NULL;
			}
			delete node;
			size -= 1;
			if (size == 0) {
				first = NULL;
			}
			return data;
		}
		else {  // видалення з середини: ані перший, ані останній
			ListNode<T>* node = first;
			for (size_t i = 0; i < index; ++i) {  //  first      node         last
				node = node->next;                //   [p|0|n]<->[p|1|n]<->[p|2|n]
			}                                     // NULL                       NULL
			node->prev->next = node->next;        //   [p|0|n]<----------->[p|2|n]
			node->next->prev = node->prev;        // [NULL|1|300]  [100|2|200] [300|3|400]
			T data = node->data;                  // [NULL|1|200]              [100|3|400]
			delete node;
			size -= 1;
			return data;
		}
	}
	else {
		// error
		throw std::range_error(
			std::format("LinkedList<T>::remove: Unable to remove element. Max list index {} but got {}", size - 1, index)
		);
	}
}
/*
	node
0<-[p|d|n]<->[p|d|n]->0

[p|d|n] - struct (ListNode) - комплексний об'єкт, що складається з трьох полів:
дані (d) та два покажчики (адреси) n (next) на наступний та p (prev) на
попередній
new ListNode - створює новий об'єкт, розміщує його у випадковому
місці пам'яті та повертає адресу цього місця
first - окрема змінна (поле), що зберігає адресу першого об'єкта списку
				 1
				  \
first(100)       node(200)
[NULL|1|200]  [100|2|300]  [200|3|400] [400|4|NULL]
					  /     /
					 2     3
1: node - змінна, що зберігає адресу об'єкта
2: node->next - поле next об'єкта за адресою node (200)
 семантика: покажчик на наступний елемент (з адресою 300)
3: node->next->prev - поле prev об'єкта за адресою node->next (300)
 семантика: покажчик на поточний елемент (node)
 ? чи еквівалентні тоді операції:
  node = ...
  node->next->prev = ...
  Ні:
  node = ... змінить вміст змінної node
  node->next->prev = ... змінить зміст поле prev об'єкта за адресою node->next (300)

 ? чи еквівалентні операції:
 node->data = 10
 node->next->prev->data = 10
 Так, обидві операції змінять поле data за об'єкта за адресою 200
  тільки перша операція одразу звернеться до адреси 200,
  а друга за кілька розіменувань

 ? що зміниться після команди: node->next = 500
 ! поле next в об'єкті за адресою node(200), на об'єкт node->next (300)
   ніякого впливу не буде
 ? що зміниться після команди: node->next->data = 5
 ! зміниться поле data об'єкта за адресою node->next (300) - у
   наступному (третьому) елементі
*/

/*
Оброблення виняткових ситуацій.
Виняток (виняткова ситуація, Exception) - перехід середовища виконання програми
у спеціальний режим оброблення винятків.
Виняткова ситуація створюється оператором throw
Цей оператор зупиняє нормальне виконання програми і переводить її в режим
 оброблення ("ловлення") винятків.
"Зловити" виняток може оператор catch, якщо жодний оператор не "спіймав"
 виняток, то програма зупиняється в аварійному режимі (з помилкою необробленого
 винятку)

Загальна схема роботи з винятками має вигляд:
try {
  блок з контролем за винятковими ситуаціями
  десь у цьому блоці або у функціях, що тут
  викликаються, трапляється оператор throw:

  throw std::range_error("index out of range")
}                              |
catch(const std::range_error& ex) {
  дії з оброблення виняткової ситуації з винятком std::range_error
  деталі винятку можна вилучити з ex.what() --> "index out of range" -
  те, що передавалось при створенні винятку
}
catch(const std::runtime_error& ex) {
  блоків catch може бути декілька, під різні типи винятків
  тут "ловиться" виняток std::runtime_error
}
catch(const std::exception& ex) {
  всі винятки є нащадками std::exception, відповідно, даний
  блок буде приймати всі винятки, не спіймані вищими блоками.
}

Поради:
- створювати винятки тільки для задач, коли неможлива подальша робота коду
   (не використовувати для організації "далеких" переходів в нормальній роботі)
- використовувати конкретні (типізовані) винятки, не вживати загальний
   std::exception. Якщо немає потрібного, то краще створити свій (новий)
   https://en.cppreference.com/cpp/error/exception
- блоки try поділяти за логікою роботи: погано занадто обтяжувати блок, вміщуючи
   в нього велику кількість коду, так і, навпаки, оточувати кожну інструкцію
   власним блоком try-catch. Наприклад, окремий блок для задач зчитування даних
   та формування з них переліку. Окремий блок для роботи з переліком.
- формувати детальні повідомлення про помилки, які дозволять
  = знайти точку помилки
  = дізнатись параметри, що призвели до помилки
  = дізнатись детальну причину помилки
  поганий приклад повідомлення: "parse error"
  гарний приклад: "Number parse error: unprocessable char '*' in position 2: '1*2'"
*/