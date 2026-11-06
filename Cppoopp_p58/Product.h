#pragma once
#include <string>

// інша традиція іменування - CamelCase
// імена змінних, полів та методів - lowerCamelCase -
//  перша літера маленька, далі у поєднанні - великі
// імена класів - CapitalCamelCase - перша літера велика

class Product {
private:
	std::string name;
	double      price;
public:
	std::string getName() const;
	Product* setName(std::string);
	double      getPrice() const;
	Product* setPrice(double);

	virtual std::string toString() const = 0;  // pure virtual OR abstract method
};
/*
Абстрактні (чисто віртуальні) методи - ті, які реалізуються у дочірніх класах.
Їх присутність необхідна для того, щоб мати змогу викликати ці методи,
коли об'єкти адресуються через батьківьскі типи.

Д.З. Описати класи, що реалізують результати попереднього ДЗ (абстрагування)
Створити масив з різними об'єктами через їх батьківський тип.
За допомогою циклу вивести об'єкти на екран.
*/