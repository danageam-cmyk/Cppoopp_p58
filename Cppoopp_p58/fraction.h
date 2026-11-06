#pragma once
#include <string>
#include <iostream>

class fraction_t {               // клас - це тип даних, тому є традиції додавати "_t"
private:                         // склад класу поділяється за "видимістю" на декілька категорій
	int numerator;               // поле - "змінна" в середині класу
	int denominator;             // набір полів називають "характеристиками" класу
	char* name;
	int gcd(int a, int b);       // приватний метод (НСД - найбільший спільний дільник) 
	void reduce();               // скорочення дробу
public:                          // За рекомендаціями ООП поля мають бути приватними, 
	int get_numerator() const;   // а для доступу до них створюють методи ("функції"), що називають
	int get_denominator() const; // аксесорами (які поділяють на геттери та сеттери)
	void set_numerator(int);     // набір методів класу також називають "поведінкою"
	void set_denominator(int);
	char* get_name() const;
	void set_name(char*);
	std::string to_string() const;

	fraction_t();                // конструктори - спец. методи, які автоматично запускаються
	fraction_t(int);             // коли створюються об'єкти даного класу. Вони не мають 
	fraction_t(int, int);        // типу повернення і збігаються за назвою з іменем класу
	fraction_t(int, int, char*); // Конструкторів може бути декілька за правилами перевантаження
	fraction_t(fraction_t&);     // Окремий тип конструкторів: конструктор копіювання
	fraction_t(fraction_t&&) noexcept;  // конструктор переносу (move constructor)

	~fraction_t();               // деструктор - викликається при знищенні об'єкта

	static fraction_t decil() {  // статичні методи - методи класів (не об'єктів)
		fraction_t d(1, 10, new char[] {"Decil"});
		return d;
	}

	// оператори: С++ надає можливість перевантажувати оператори з автоматичним
	// включенням наших об'єктів до арифметичних та інших виразів, на кшталт А + В.
	// Перевантаження - через ключове слово "operator", для пришвидшення роботи
	// другий аргумент (other) передається за посиланням (&) і для унеможливлення
	// його змін додається const
	fraction_t operator +(const fraction_t& other);
	// Особливу роль грають оператори присвоювання (=)
	// Вони також поділяються на оператори копіювання та перенесення
	fraction_t& operator =(const fraction_t& other);      // copy
	fraction_t& operator =(fraction_t&& other) noexcept;  // move  

	void operator += (const fraction_t& other);  // f += f2
	void operator += (int n);   // f += 2

	// "дружні" методи - зовнішні функції, яким дозволено доступ до 
	// приватних членів об'єктів
	friend fraction_t operator *(const fraction_t& f1, const fraction_t& f2);
};

// оператори можуть бути оголошені поза класом
// традиція: зовні описуються оператори, що не змінюють об'єкти (*, / тощо)
// в середині класу - ті, що змінюють (+=, = тощо)
fraction_t operator *(const fraction_t& f1, const fraction_t& f2);  // friend
fraction_t operator /(const fraction_t& f1, const fraction_t& f2);  // non-friend
// унарні оператори - приймають один параметр (або жодного, якщо описуються у класі)
fraction_t operator -(const fraction_t& f);  // унарний мінус (A = -B)

// також поза класом описуються деякі оператори, що в якості 
// першого параметра отримують не даний об'єкт
std::ostream& operator <<(std::ostream& out, const fraction_t& f);