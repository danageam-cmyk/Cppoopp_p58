#pragma once
#include <format>
#include <iostream>
#include <stdexcept>

template<typename T>
struct ListNode {
    T data;
    ListNode<T>* prev = nullptr;
    ListNode<T>* next = nullptr;
};

template<typename T>
class LinkedList {
private:
    ListNode<T>* first = nullptr;
    ListNode<T>* last = nullptr;
    size_t size = 0;

public:
    void   add(T data);
    void   insertBefore(T data, size_t index);
    T      remove(size_t index);
    size_t getSize() const { return size; }

    void print();

    
    LinkedList<T>* clone() const {
        LinkedList<T>* clonedList = new LinkedList<T>();
        ListNode<T>* current = first;
        while (current != nullptr) {
            clonedList->add(current->data);
            current = current->next;
        }
        return clonedList;
    }

    ListNode<T>* get_head() const {
        return first;
    }

    LinkedList<T>* operator+(const LinkedList<T>& other) const {
        LinkedList<T>* newList = new LinkedList<T>();

        ListNode<T>* current = first;
        while (current != nullptr) {
            newList->add(current->data);
            current = current->next;
        }

        current = other.first;
        while (current != nullptr) {
            newList->add(current->data);
            current = current->next;
        }

        return newList;
    }

    LinkedList<T>* operator*(const LinkedList<T>& other) const {
        LinkedList<T>* newList = new LinkedList<T>();

        ListNode<T>* curr1 = first;
        while (curr1 != nullptr) {
            bool found = false;
            ListNode<T>* curr2 = other.first;
            while (curr2 != nullptr) {
                if (curr1->data == curr2->data) {
                    found = true;
                    break;
                }
                curr2 = curr2->next;
            }

            if (found) {
                bool alreadyAdded = false;
                ListNode<T>* checkNode = newList->first;
                while (checkNode != nullptr) {
                    if (checkNode->data == curr1->data) {
                        alreadyAdded = true;
                        break;
                    }
                    checkNode = checkNode->next;
                }

                if (!alreadyAdded) {
                    newList->add(curr1->data);
                }
            }

            curr1 = curr1->next;
        }

        return newList;
    }
};

// --- Реалізація методів класу LinkedList ---

template<typename T>
void LinkedList<T>::add(T data) {
    if (last) {
        last->next = new ListNode<T>{ data, last, nullptr };
        last = last->next;
    }
    else {
        first = last = new ListNode<T>{ data, nullptr, nullptr };
    }
    size += 1;
}

template<typename T>
void LinkedList<T>::insertBefore(T data, size_t index) {
    if (index == 0) {
        if (first) {
            first = first->prev = new ListNode<T>{ data, nullptr, first };
            size += 1;
        }
        else {
            add(data);
        }
    }
    else {
        if (index < size) {
            ListNode<T>* node = first;
            for (size_t i = 0; i < index; ++i) {
                node = node->next;
            }
            node->next = new ListNode<T>{ data, node, node->next };
            node->next->next->prev = node->next;
            size += 1;
        }
        else {
            throw std::range_error(
                std::format("LinkedList<T>::insertBefore: Unable to insert element. Max list index {} but got {}", size - 1, index)
            );
        }
    }
}

template<typename T>
void LinkedList<T>::print() {
    ListNode<T>* node = first;
    if (node == nullptr) {
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
        if (index == 0) {
            ListNode<T>* node = first;
            T data = node->data;
            first = first->next;
            if (first) {
                first->prev = nullptr;
            }
            delete node;
            size -= 1;
            if (size == 0) {
                last = nullptr;
            }
            return data;
        }

        if (index == size - 1) {
            ListNode<T>* node = last;
            T data = node->data;
            last = last->prev;
            if (last) {
                last->next = nullptr;
            }
            delete node;
            size -= 1;
            if (size == 0) {
                first = nullptr;
            }
            return data;
        }
        else {
            ListNode<T>* node = first;
            for (size_t i = 0; i < index; ++i) {
                node = node->next;
            }
            node->prev->next = node->next;
            node->next->prev = node->prev;
            T data = node->data;
            delete node;
            size -= 1;
            return data;
        }
    }
    else {
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