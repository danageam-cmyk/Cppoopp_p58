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
    void add(T data);
    void insertBefore(T data, size_t index);
    T remove(size_t index);
    size_t getSize() const { return size; }

    void print() const;

    ListNode<T>* get_head() const {
        return first;
    }

    void clear() {
        ListNode<T>* node = first;
        while (node) {
            first = first->next;
            delete node;
            node = first;
        }
        first = last = nullptr;
        size = 0;
    }

    LinkedList<T>* clone() const {
        LinkedList<T>* res = new LinkedList<T>();
        ListNode<T>* node = this->first;
        while (node) {
            res->add(node->data);
            node = node->next;
        }
        return res;
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

    LinkedList() : first{ nullptr }, last{ nullptr }, size{ 0 } {}

    LinkedList(const LinkedList<T>& other) {
        ListNode<T>* node = other.first;
        while (node) {
            this->add(node->data);
            node = node->next;
        }
    }

    LinkedList(LinkedList<T>&& other) noexcept :
        first{ other.first }, last{ other.last }, size{ other.size }
    {
        other.first = other.last = nullptr;
        other.size = 0;
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            this->clear();
            ListNode<T>* node = other.first;
            while (node) {
                this->add(node->data);
                node = node->next;
            }
        }
        return *this;
    }

    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
        if (this != &other) {
            this->clear();
            this->first = other.first;
            this->last = other.last;
            this->size = other.size;

            other.first = other.last = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~LinkedList() {
        clear();
    }
};

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
            for (size_t i = 0; i < index - 1; ++i) {
                node = node->next;
            }
            node->next = new ListNode<T>{ data, node, node->next };
            if (node->next->next) {
                node->next->next->prev = node->next;
            }
            size += 1;
        }
        else {
            throw std::range_error(
                std::format("LinkedList<T>::insertBefore: Unable to insert element. Max list index {} but got {}", size > 0 ? size - 1 : 0, index)
            );
        }
    }
}

template<typename T>
void LinkedList<T>::print() const {
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
            std::format("LinkedList<T>::remove: Unable to remove element. Max list index {} but got {}", size > 0 ? size - 1 : 0, index)
        );
    }
}