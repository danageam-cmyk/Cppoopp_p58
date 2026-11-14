#include "Laptop.h"
#include <format>

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

std::ostream& operator << (std::ostream& out, const Laptop& obj) {
	out << obj.toString();
	return out;
}
std::ostream& operator << (std::ostream& out, const Laptop* obj) {
	out << *obj;
	return out;
}

/*
Type obj; -- об'єкт статич типу розміщується у стеку 
створюється оголошенням(окремої команди не треба)
obj.method(); -- виклик методу об'єкта
знищується (запуск деструкт) при завершенні функції (при  руйнувані стеку)окромої команди не треба

Type *ptr;  -- покажчик що може зберігати адресу обєкта типу 
Type на момент оголошення самого об'єкту немає а значення obj випадкове 
ptr = new Type; -- створення об'єкту у "купі" та одержання його адреси 
ptr.method; -- виклик методу об'єкта через покажчик на нього при 
завершенні фкнкції звільняється місце для ptr  але не  сам об'єкт
необхідна окрема команда:
deleate -ptr; -- звільнити пам'ять що виділенна під об'єкт (+ запуск деструктора)


*/