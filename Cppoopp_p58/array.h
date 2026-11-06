#pragma once
#include "linked_list.h"

template<typename T>
class Array {
private:
    LinkedList<T>* list;

public:
    Array() {
        list = new LinkedList<T>();
    }

    ~Array() {
        if (list != nullptr) {
            delete list;
        }
    }

    size_t GetSize() const {
        return list->getSize();
    }

    void add(T data) {
        list->add(data);
    }

    void print() const {
        list->print();
    }

};