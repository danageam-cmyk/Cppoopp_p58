#define _CRT_SECURE_NO_WARNINGS
#include "fraction.h"
#include <format>
#include <iostream>

fraction_t::fraction_t() {  // конструктор без параметрів - констуктор за замовчанням
	numerator = 0;          // f = new fraction_t  або  f = new fraction_t()
	denominator = 1;
	name = NULL;
}

fraction_t::fraction_t(int n) {  // конструктор з параметрами, його слід зазначати
	numerator = n;               // прямо (не за замовчанням) f = new fraction_t(10)
	denominator = 1;             // Присвоювання значень
	name = NULL;
}

fraction_t::fraction_t(int numerator, int denominator) : // ініціалізація полів
	numerator{ numerator }, denominator{ denominator }   // на відміну від присвоювання
{                                                        // дозволяє задавати значення
	name = NULL;                                         // незмінним полям (константам)
}                                                        // і комбінується з присвоєнням

fraction_t::fraction_t(int numerator, int denominator, char* name) :
	numerator{ numerator }, denominator{ denominator }, name{ name } {
}

fraction_t::fraction_t(fraction_t& other) {
	// конструктор копіювання (copy constructor), який будує новий об'єкт
	// за зразком іншого об'єкту.
	// Проблема: просте присвоєння полів об'єкта-зразка правильно працює для
	// полів зі значеннями, але неправильно - для покажчиків. Присвоювання 
	// this->name = other.name - створить другий покажчик на одне і те саме ім'я
	// деструктор одного об'єкта видаляє ресурс, а деструктор другого об'єкту 
	// призведе до помилки. Також другий об'єкт продовжить працювати з видаленною
	// памяттю. Копіювання - це утворення копій усіх ресурсів-покажчиків.
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	// для референсного ресурсу створюємо копію
	if (other.name != NULL) {
		size_t len = strlen(other.name) + 1;
		this->name = new char[len];
		strcpy(this->name, other.name);
		std::cout << "Copy constructor: copy from " << (void*)other.name << " to "
			<< (void*)(this->name) << std::endl;
	}
	else {
		this->name = NULL;
	}

	//   0x123("Half\0")               0x567("Half\0")
	// A[1/2"Half"] - A[1,2,0x123]     |
	// B = copy A   - B[1,2,0x123] - strcpy - B[1,2,0x567]
	// delete A - звільнення 0x123 --> В посилається на видалений ресурс

	/*        A              B               0x123
	------[1,2,0x123]----[1,2,0x123]--------"Half\0"--------------------------------

	A.name = "1/2"
			  A              B               0x123
	------[1,2,0x123]----[1,2,0x123]--------"1/2\0"---------------------------------
	B.name - ? "1/2"  -- неправильно

			  A              B               0x123          0x567
	------[1,2,0x123]----[1,2,0x567]--------"Half\0"--------"Half\0"----------------

	Аналогічна ситуація виникає при присвоюванні: А = В - так само необхідно
	створювати копії полів-покажчиків.
	Поєднання конструктора копіювання та відповідного оператора "="
	 називають "семантикою копіювання"
	*/
}

fraction_t::fraction_t(fraction_t&& other) noexcept {
	/* Конструктор перенесення (move constructor) викликається тоді, коли
	*  інший об'єкт (other) підлягає знищенню, наприклад, коли він передається
	*  як результат роботи функції.
	*
	* Конструктор перенесення може "забрати" ресурс іншого об'єкта
	* замість того, щоб створювати копію. Але, щоб знищення не запустилось
	* автоматично, слід підмінити ресурс іншого об'єкту на NULL
	*/
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	this->name = other.name;
	other.name = NULL;
	std::cout << "Move constructor: take from " << (void*)this->name << std::endl;
}



char* fraction_t::get_name() const {
	return name;
}

void fraction_t::set_name(char* name) {
	this->name = name;
}

int fraction_t::get_numerator() const {
	return numerator;
}

int fraction_t::get_denominator() const {
	return denominator;
}

void fraction_t::set_numerator(int numerator) {
	this->numerator = numerator;
	/* this - покажчик на об'єкт, неявний параметр, що передається у
	   нестатичні методи класу. */
}

void fraction_t::set_denominator(int denominator) {
	this->denominator = denominator;
}

std::string fraction_t::to_string() const {
	// форматування рядків - заповнення "формату" - рядка з плейсхолдерами
	//                    v   v - placeholders
	return std::format("({0}/{1}{2})", numerator, denominator, (name == NULL ? "" : name));
	//                                  ^           ^
	//               дані, які будуть підставлені на міце плейсхолдерів
}

fraction_t::~fraction_t() {
	// задача деструктора - звільнити ресурси об'єкту
	if (name != NULL) {
		delete[] name;
	}
}

fraction_t fraction_t::operator +(const fraction_t& other) {
	char* new_name = NULL;
	if (this->name != NULL && other.name != NULL) {
		// якщо в обох дробах є імена, то поєднаємо їх через "+"
		size_t len1 = strlen(this->name);
		size_t len = len1 + strlen(other.name) + 2;
		new_name = new char[len];                 // [__________]
		strcpy(new_name, this->name);             // [Half______]
		strcpy(new_name + len1, "+");             // [Half+_____]
		strcpy(new_name + len1 + 1, other.name);  // [Half+Decil]
	}
	return fraction_t(
		this->numerator * other.denominator + this->denominator * other.numerator,
		this->denominator * other.denominator,
		new_name);
	// a/b + c/d = (ad+bc)/bd
}

fraction_t& fraction_t::operator =(const fraction_t& other) {
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	if (other.name != NULL) {
		size_t len = strlen(other.name) + 1;
		this->name = new char[len];
		strcpy(this->name, other.name);
		std::cout << "Copy assignment: copy from " << (void*)other.name << " to "
			<< (void*)(this->name) << std::endl;
	}
	else {
		this->name = NULL;
	}
	return *this;
}

fraction_t& fraction_t::operator =(fraction_t&& other) noexcept {
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	this->name = other.name;
	other.name = NULL;
	std::cout << "Move assignment: take from " << (void*)this->name << std::endl;
	return *this;
}

fraction_t operator *(const fraction_t& f1, const fraction_t& f2) {
	return fraction_t(
		f1.numerator * f2.numerator,     // дружні функції мають доступ
		f1.denominator * f2.denominator  // до приватних полів об'єкту
	);
}

fraction_t operator /(const fraction_t& f1, const fraction_t& f2) {
	return fraction_t(
		f1.get_numerator() * f2.get_denominator(),  // функції, що не є дружніми
		f1.get_denominator() * f2.get_numerator()   // мають доступ лише до аксессорів
	);
}

std::ostream& operator <<(std::ostream& out, const fraction_t& f) {
	out << f.to_string();
	return out;
}

fraction_t operator -(const fraction_t& f) {
	return fraction_t(
		-f.get_numerator(),
		f.get_denominator()
	);
}

void fraction_t::operator += (const fraction_t& other) {
	this->numerator = this->numerator * other.denominator + this->denominator * other.numerator;
	this->denominator = this->denominator * other.denominator;
	reduce();
}
void fraction_t::operator += (int n) {
	this->numerator += n * this->denominator;
	reduce();
}
int fraction_t::gcd(int a, int b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (b > a) return gcd(b, a);
	if (b == 0) return a;
	return gcd(b, a % b);
}
void fraction_t::reduce() {
	int g = gcd(numerator, denominator);
	if (g != 1) {
		numerator /= g;
		denominator /= g;
	}
}
/*
Правило опису класів (The Rule Of Six):
При описі класів необхідно обов'язково включити до опису
- конструктор за замовчанням
- конструктор копіювання
- конструктор перенесення
- оператор = копіювання
- оператор = перенесення
- деструктор
~ інколи додають параметризований конструктор
*/

/*
Д.З. Описати клас, що задає вектор на площині (vector_2 / vector2_t)
склад: 2 поля-координати х та у (дробові)
+ аксессори для них
Розділити оголошення типу та реалізацію його методів на різні файли.

Д.З. Реалізувати для класу, що задає вектор на площині (попереднє ДЗ)
додати поле для імені вектора (char*), аксесори для нього
конструктори (без параметрів, з різними параметрами, конструктор копіювання)
метод рядкового представлення (to_string), що включає ім'я (якщо воно є)
деструктор
Створити декілька об'єктів - векторів, у т.ч. за допомогою копіювання,
вивести дані на екран. Додати скріншот і посилання  на репозиторій.
*/