#pragma once
#include <iostream>
#include <string>
#include "queue.h"

inline void checkBracketsWithReport(const std::string& input) {
    Stack<char> s;
    Stack<size_t> indices;

    size_t length = input.length();
    bool hasSemicolon = false;
    size_t semicolonPos = length;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] == ';') {
            hasSemicolon = true;
            semicolonPos = i;
            break;
        }
    }

    size_t workLength = hasSemicolon ? semicolonPos : length;

    for (size_t i = 0; i < workLength; ++i) {
        char ch = input[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
            indices.push(i);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.isEmpty()) {
                std::cout << "Помилка: зайва закриваюча дужка '" << ch << "' на позиції " << i << ".\n";
                std::cout << "Рядок до місця помилки: \"" << input.substr(0, i + 1) << "\"\n";
                return;
            }

            char topChar = s.pop();
            indices.pop();

            if ((ch == ')' && topChar != '(') ||
                (ch == '}' && topChar != '{') ||
                (ch == ']' && topChar != '[')) {

                std::cout << "Помилка: невідповідність дужок. Очікувалась пара для '" << topChar
                    << "', але зустрілась '" << ch << "' на позиції " << i << ".\n";
                std::cout << "Рядок до місця помилки: \"" << input.substr(0, i + 1) << "\"\n";
                return;
            }
        }
    }

    if (!s.isEmpty()) {
        size_t errorIndex = indices.peek();
        std::cout << "Помилка: незакрита відкриваюча дужка '" << s.peek() << "' на позиції " << errorIndex << ".\n";
        std::cout << "Рядок до місця помилки: \"" << input.substr(0, errorIndex + 1) << "\"\n";
        return;
    }

    std::cout << "Рядок є коректним! Усі дужки розставлені правильно.\n";
}