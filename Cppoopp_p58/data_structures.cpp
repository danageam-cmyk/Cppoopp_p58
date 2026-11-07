#include "data_structures.h"
#include "linked_list.h"
#include "queue.h"
#include <iostream>
#include "array.h"
#include <stdexcept>


void data_structures() {
    LinkedList<int>* intList =
        new LinkedList<int>();
    intList->print();
    LinkedList<int>* intList2 =
        intList->clone();
    intList2->print();
    intList->insertBefore(51, 0);
    intList2->insertBefore(52, 0);
    std::cout << "list1" << std::endl;
    intList->print();
    std::cout << "list2" << std::endl;
    intList2->print();
    std::cout << "-------------------" << std::endl;
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    Queue<int> queue2 = std::move(queue);
    while (!queue2.isEmpty()) {
        std::cout << queue2.dequeue() << std::endl;
    }
}

void data_structures_4() {
    // Демонстрація виняткових ситуацій
    LinkedList<int>* intList = new LinkedList<int>();
    intList->add(10);   // ці команди не мають 
    intList->add(20);   // винятків в середині і не 
    intList->add(30);   // повинні вміщуватись в блок try
    intList->print();
    
    try {
        intList->insertBefore(5, 0);  // у тілі insertBefore є throw
        intList->print();             // але перша команда не створить виняток
        intList->insertBefore(15, 5); // тоді як друга - створить
        intList->print();             // і виконання зупиниться перед даним рядком
    }
    catch (const std::range_error& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
    // intList->insertBefore(15, 5);  виклик без try призводить до 
    // intList->print();              аварійної зупинки програми.
    try {
        intList->remove(10);
    }
    catch (const std::range_error& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    // Вилучення всіх даних з черги
    // Варіант з винятком - не рекомендований
    try { while (true)  std::cout << queue.dequeue() << std::endl; }
    catch (...) {}   // варіант з ігноруванням винятку
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    // варіант без винятків
    while (!queue.isEmpty())  std::cout << queue.dequeue() << std::endl;
}
/*
Д.З. Ввести винятки в методи класу Стек (предмет попередніх ДЗ)
Прикласти скріншоти прикладів їх перевірки.
*/

template<typename T>   // Шаблонними можуть бути функції та типи (класи, структури)
void print(T arg) {    // Шаблон вводить "змінну" для типу, традиційно "Т"
    std::cout << arg   // В самій функції (чи типі) ця "Т" вживається там,
        << std::endl;  // де пізніше має бути реальний тип даних
}                      // Далі компілятор шукає усі вжитки даного шаблону ...

template<typename T>   // Перед кожним оголошенням повторюється template
struct fraction {      // Для типів (наприклад, структур) шаблон "Т"
    T numerator;       // може вживатись для оголошення полів
    T denominator;     // чи методів.
    void print() {     // Якщо метод не залежить від "Т", то
        std::cout      // в його тілі не робимо відповідних позначок
            << numerator   // 
            << '/'         // 
            << denominator;// 
    }                  // Інші методи можуть мати залежність від "Т"
    T get_numerator() {
        return numerator;
    }
    void set_numerator(T n) {
        numerator = n;
    }
};

void data_structures_3() {
    std::cout << "Queue demo" << std::endl;
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    std::cout << queue.dequeue() << std::endl;
    std::cout << queue.dequeue() << std::endl;
    std::cout << queue.dequeue() << std::endl;
}

void data_structures_2() {
    std::cout << "Data structures" << std::endl;
    LinkedList<int>* intList = new LinkedList<int>();
    intList->add(10);
    intList->add(20);
    intList->add(30);
    intList->print();
    intList->insertBefore(5, 0);
    intList->print();
    intList->insertBefore(15, 2);
    intList->print();
    std::cout << "removed: " << intList->remove(2) << std::endl;
    intList->print();
    std::cout << "removed: " << intList->remove(2) << std::endl;
    intList->print();
    std::cout << "removed: " << intList->remove(1) << std::endl;
    intList->print();
    std::cout << "removed: " << intList->remove(0) << std::endl;
    intList->print();
    std::cout << "removed: " << intList->remove(0) << std::endl;
    intList->print();
}

void data_structures_t() {
    std::cout << "Templates" << std::endl;
    print("Template function demo");  // ... і для кожного конкретного вжитку
    print(42);                        // створює копію шаблона під даний "Т"
    print(true);                      // Тобто у підсумку буде кілька (5) різних
    print('A');                       // функцій під кожен тип окремо, за потреби
    print<short>(42);                 // прямо вказати тип додаємо <тип>

    fraction<int> f1{ 1, 2 };         // Для різних конкретних типів також
    fraction<float> f2{ 1.5, 2.5 };   // буде створено різні структури за 
    fraction<short> f3{ 2, 3 };       // єдиним шаблоном
    f1.print(); std::cout << std::endl;
    f2.print(); std::cout << std::endl;
    f3.print(); std::cout << std::endl;
}
//1
void data_structures_queue_demo() {
    std::cout << "=== Template Queue Demo ===" << std::endl;

    Queue<int> int_queue;
    int_queue.enqueue(100);
    int_queue.enqueue(200);
    int_queue.enqueue(300);

    std::cout << "Int queue size: " << int_queue.getLength() << std::endl;
    while (!int_queue.isEmpty()) {
        std::cout << "Deported int: " << int_queue.dequeue() << std::endl;
    }

    Queue<std::string> str_queue;
    str_queue.enqueue("First in line");
    str_queue.enqueue("Second in line");

    std::cout << "\nString queue size: " << str_queue.getLength() << std::endl;
    while (!str_queue.isEmpty()) {
        std::cout << "Deported string: " << str_queue.dequeue() << std::endl;
    }
}
//2
void data_structures_task2() {
    std::cout << "=== Task 2 Demo ===" << std::endl;

    LinkedList<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);

    LinkedList<int> list2;
    list2.add(2);
    list2.add(3);
    list2.add(4);

    std::cout << "List 1: "; list1.print();
    std::cout << "List 2: "; list2.print();

    LinkedList<int>* cloned = list1.clone();
    std::cout << "Cloned List: ";
    cloned->print();

    LinkedList<int>* unionList = list1 + list2;
    std::cout << "Union (List 1 + List 2): ";
    unionList->print();

    LinkedList<int>* intersectionList = list1 * list2;
    std::cout << "Intersection (List 1 * List 2): ";
    intersectionList->print();

    delete cloned;
    delete unionList;
    delete intersectionList;
}
void data_structures_array_demo() {
    std::cout << "=== Array Container Demo ===" << std::endl;

    Array<int> arr;
    arr.add(10);
    arr.add(20);
    arr.add(30);

    arr.print();
    std::cout << "Array Size (GetSize): " << arr.GetSize() << std::endl;
}
/*
Структури даних та шаблонне програмування
1. Структури даних - типові способи організації даних,
   поширені в різних практичних задачах.
- Стек (Stack) - спосіб за якого дані накопичуються
   в одному порядку, а виводяться в іншому (First In Last Out - FILO)
   3 -> 2 -> 1 -> [Stack]
   [Stack] -> 3
   Вживається, зокрема, у механізмі виклику функцій
   a(b(c(x))):   1) c(x), 2) b(res), 3) a(res)
- Черга (Queue) - (First In First Out - FIFO) - прямий
   порядок передачі накопичених даних.
   Може вживатись для буферизації, коли швидкість обробки
   не точно дорівнює швидкості передачі даних
   File -> 1 -> 2 -> 3 -> [Queue] -> 1 -> [Process]
- Списки (Lists) - колекції з можливістю додавання, вставлення,
   вилучення даних. На відміну від стека та черги, доступ можливий
   до довільного елементу списка. Розрізняють зв'язні списки та
   списки-масиви:
   = зв'язні списки (Linked List) зберігають дані та посилання
     на інші "вузли" списку (або тільки на наступний,
     або і на наступний і на попередній)
   = списки-масиви (Array List) "тримають" масив із запасом,
     за потреби більшого розширення масив перекопійовується
     у більший масив
  Порівняння: масиви дозволяють швидко одержати елемент з довільним
   індексом, тоді як зв'язні списки мають "шукати" елементи
   переходячи до сусідних певну кількість разів -- пошук швидший у масивах.
   1 <-> 2 <-> 3 <-> 4 <-> 5
   Недолік масивів полягає в операціях вставки елементів в середину або
   вилучення з середини. В такому разі решта елементів має "посунутись"
   1 2 3 4 5 6 7     тоді як для зв'язних списків необхідно лише
       ^             переставити покажчики на інших сусідів
   1 2 - 4 5 6 7          1 <-> 2 <-> 3 <-> 4 <-> 5
        <-                            ^
   1 2 4 5 6 7            1 <-> 2 <-------> 4 <-> 5

   1 2 4 5 6 7            1 <-> 2 <-------> 4 <-> 5
        10                            10
            ->
   1 2 4 10 5 6 7         1 <-> 2           4 <-> 5
                                 \         /
                                  <-> 10 <->
 Вибір між видами списків робиться з аналізу операцій, що з ними виконуються:
 якщо список будується один раз, а далі тільки одержуються елементи
  (наприклад, зчитати файл і потім працювати з даними), тоді краще масив
 якщо список весь час змінюється (наприклад, ігрові елементи - спавняться,
  збиваються, зникають), тоді краще зв'язний список

- Множина (Set) - набір з унікальними значеннями (що не повторюються)
   зазвичай в множинах реалізується швидкий пошук завдяки організації
   бінарним деревом.

- Бінарне дерево:  Структура схожа з зв'язним списком, але має два
   покажчики - на лівий вузол (з меншим значенням) та правий вузол (з
   більшим значенням)
   Медіана - елемент множини, який ділить її навпіл: як менших, так і більших
   елементів є порівну. Якщо в множини непарна кількість елементів, то
   медіана є середнім елементом. Якщо парна, то середнє від центральних.
   (0 1 2 3 4 5 6 7 8 9 10)
              ^
                          5
                      /       \
               (0 1 2 3 4)  (6 7 8 9 10)
                    ^            ^
                          5                            5
                        /   \                        /    \
                       2     8                      2      8
                      / \   / \                    / \    / \
                     1   4 6   9                  0   3  6   9
                    /   /   \   \                  \   \  \   \
                   0   3     7   10                 1   4  7   10 - 11 - 12 - 13

 2^3 = 8; 2^4 = 16; 2^5 = 32; 2^10 = 1024
 1000 елементів - пошук до 10 разів
 1млн елементів - до 20
 1млрд - до 30

- Асоціативні масиви (Map, Dictionary, Hash-Table) - структури даних,
   в яких індексація може бути не числова. Їх також називають
   "множинами ключ-значення", вживаючи замість терміну "індекс" термін "ключ".
   Вживаються при введенні доменних імен (імен вузлів мережі, які в
   самій мережі адресуються числом)
   hosts = {
      "itstep.org" => 123.3.16.7,
      "google.com" => 8.8.8.8,
      "google.com.ua" => 23.53.6.32,
   }
   hosts["itstep.org"]
*/
/*
Узагальнене (шаблонне) програмування.
Структури даних передбачають огранізацію даних, але нічого не
зазначають про типи даних. Якщо потрібна організація для
даних різного типу, то складається враження, що необхідно
створювати декілька однакових за схемою структур, але з різними
типами даних в середині: список для цілих чисел, список для дробових,
список для рядків тощо.
Узагальнене програмування дозволяє зробити структури даних, що
можуть працювати з різними типами внутрішних даних: описати
шаблон, який буде реалізовуватись для конкретних типів у програмі.
*/
/*
Д.З. Переробити клас "вектор" (предмет попередніх ДЗ)
на шаблонний клас. Описати декілька об'єктів-векторів
з різними типами даних.
*/