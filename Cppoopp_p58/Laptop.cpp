#include "Laptop.h"
#include <format>
#include <iostream>

std::string Laptop::getHardware() const {
	return hardware;
}

Laptop* Laptop::setHardware(std::string hardware) {
	this->hardware = hardware;
	return this;  // "fluent interface" - каскадне встановлення властивостей
}

std::string Laptop::toString() const {
	return std::format("{} {} hrn, {} ({} W)",
		getName(),
		getPrice(),
		hardware,
		getPower()
	);
}

std::ostream& operator <<(std::ostream& out, const Laptop& obj) {
	out << obj.toString();
	return out;
}

std::ostream& operator <<(std::ostream& out, const Laptop* obj) {
	out << *obj;  // розіменування покажчика (Dereferencing)
	return out;
}
/*
Type obj;  -- об'єкт статичного типу, розміщується у стеку,
	створюється оголошенням (окремої команди не треба)
obj.method();  -- виклик методу об'єкта
знищується (запускається деструктор) при завершенні функції
	(при руйнуванні стеку), окремої команди не треба

Type *ptr;  -- покажчик, що може зберігати адресу об'єкта типу Type
	на момент оголошення самого об'єкту немає, а значення ptr випадкове.
ptr = new Type;  -- створення об'єкту у "купі" та одержання його адреси
ptr->method();   -- виклик методу об'єкта через покажчик на нього
при завершенні функції звільняється місце для ptr, але  не сам об'єкт
необхідна окрема команда:
delete ptr;  -- звільнити пам'ять, що виділена під об'єкт (+ запуск деструктора)

int func2(int &x) {
	x = 20;
	int y = 10;
	return y;
}

func(int x) {
	Type *ptr;
	x = 20;
	ptr = new Type; ---> <Type>   2.1. Виділення пам'яті у купі (поза стеком)
	delete ptr; ----Х---/   |     2.2. Звільнення виділеної пам'яті
	return; -\              | 3. Завершення функції вилучає зі стеку запис про її роботу
}			  X				|    але ніяк не впливає на купу
main() {       \ stack		|
	func(1); -->[x,ptr]<----|     1. Запуск функції додає до стеку "запис" з усіма
				 {...}            змінними, що потрібні для роботи функції

	int y = 10;            аргумент передається по копії,
	func(y);-->[x,ptr]     параметр "х" та змінна "у" не зв'язуються

	func2(y);-->[&x,ptr,y]   передача за посиланням (псевдонимом), зміна "х" в середині
							 функції вплине на значення "у"
}
Витік пам'яті (memory leakage) - ефект збільшення пам'яті, виділеної для
програми, у процесі її роботи через неправильне (забуте) звільнення
попередньо виділених ділянок пам'яті
*/