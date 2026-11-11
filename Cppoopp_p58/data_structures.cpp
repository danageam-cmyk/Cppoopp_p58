#include "data_structures.h"
#include "linked_list.h"
#include "queue.h"
#include "array.h"
#include "brackets_checker.h"
#include <iostream>
#include <stdexcept>

void data_structures() {
    LinkedList<int>* intList = new LinkedList<int>();
    intList->print();

    LinkedList<int>* intList2 = intList->clone();
    intList2->print();

    intList->insertBefore(51, 0);
    intList2->insertBefore(52, 0);

    std::cout << "list1:" << std::endl;
    intList->print();
    std::cout << "list2:" << std::endl;
    intList2->print();
    std::cout << "--------------" << std::endl;

    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    Queue<int> queue2 = std::move(queue);
    while (!queue2.isEmpty()) {
        std::cout << queue2.dequeue() << std::endl;
    }

    delete intList;
    delete intList2;
}

void data_structures_task2_demo() {
    std::cout << "\n=== Demo Task 2 (+ and * operators) ===" << std::endl;
    LinkedList<int> l1;
    l1.add(1); l1.add(2); l1.add(3);

    LinkedList<int> l2;
    l2.add(2); l2.add(3); l2.add(4);

    std::cout << "L1: "; l1.print();
    std::cout << "L2: "; l2.print();

    LinkedList<int>* unionResult = l1 + l2;
    std::cout << "L1 + L2 (Union): "; unionResult->print();

    LinkedList<int>* intersectResult = l1 * l2;
    std::cout << "L1 * L2 (Intersection): "; intersectResult->print();

    delete unionResult;
    delete intersectResult;
}

void data_structures_array_demo() {
    std::cout << "\n=== Demo Task 3 (Array Container) ===" << std::endl;
    Array<double> arr;
    arr.add(1.1);
    arr.add(2.2);
    arr.add(3.3);
    arr.print();
    std::cout << "Array GetSize(): " << arr.GetSize() << std::endl;
}

void data_structures_brackets_demo() {
    std::cout << "\n=== Demo Brackets Checker ===" << std::endl;
    std::string validStr = "({x-y-z} * [x + 2y] - (z + 4x));";
    std::string invalidStr = "([x-y-z} * [x + 2y) - {z + 4x)].;";

    std::cout << "Check 1:\n";
    checkBracketsWithReport(validStr);

    std::cout << "\nCheck 2:\n";
    checkBracketsWithReport(invalidStr);
}

void data_structures_4() {
    LinkedList<int>* intList = new LinkedList<int>();
    intList->add(10);
    intList->add(20);
    intList->add(30);
    intList->print();

    try {
        intList->insertBefore(5, 0);
        intList->print();
        intList->insertBefore(15, 5);
        intList->print();
    }
    catch (const std::range_error& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

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

    try { while (true) std::cout << queue.dequeue() << std::endl; }
    catch (...) {}

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    while (!queue.isEmpty()) std::cout << queue.dequeue() << std::endl;

    std::cout << "\n--- Stack Exceptions Demo ---" << std::endl;
    Stack<int> myStack;
    try {
        myStack.pop();
    }
    catch (const std::length_error& ex) {
        std::cerr << "Stack Exception caught: " << ex.what() << std::endl;
    }

    delete intList;
}

template<typename T>
void print(T arg) {
    std::cout << arg << std::endl;
}

template<typename T>
struct fraction {
    T numerator;
    T denominator;
    void print() {
        std::cout << numerator << '/' << denominator;
    }
    T get_numerator() { return numerator; }
    void set_numerator(T n) { numerator = n; }
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

    delete intList;
}

void data_structures_t() {
    std::cout << "Templates" << std::endl;
    print("Template function demo");
    print(42);
    print(true);
    print('A');
    print<short>(42);

    fraction<int> f1{ 1, 2 };
    fraction<float> f2{ 1.5, 2.5 };
    fraction<short> f3{ 2, 3 };
    f1.print(); std::cout << std::endl;
    f2.print(); std::cout << std::endl;
    f3.print(); std::cout << std::endl;
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
         ^           переставити покажчики на інших сусідів
   1 2 - 4 5 6 7         1 <-> 2 <-> 3 <-> 4 <-> 5
         <-                        ^
   1 2 4 5 6 7            1 <-> 2 <-------> 4 <-> 5

   1 2 4 5 6 7            1 <-> 2 <-------> 4 <-> 5
         10                        10
             ->
   1 2 4 10 5 6 7         1 <-> 2          4 <-> 5
                             \       /
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
                            5                                    5
                          /   \                                /   \
                         2     8                              2     8
                        / \   / \                            / \   / \
                       1   4 6   9                          0   3 6   9
                      /   /   \   \                        \   \   \   \
                     0   3     7   10                       1   4   7   10 - 11 - 12 - 13

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