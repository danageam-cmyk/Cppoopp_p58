#pragma once
#include "linked_list.h"
#include <stdexcept>

template<typename T>
class Queue {
private:
    LinkedList<T>* queue;

public:
    void enqueue(T data) {
        queue->add(data);
    }

    T dequeue() {
        if (!isEmpty()) {
            return queue->remove(0);
        }
        else {
            throw std::length_error("Queue<T>::dequeue(): Dequeue requested for empty queue");
        }
    }

    T peek() {
        if (!isEmpty()) {
         
            T val = queue->remove(0);
            queue->insertBefore(val, 0);
            return val;
        }
        else {
            throw std::length_error("Queue<T>::peek(): Peek requested for empty queue");
        }
    }

    size_t getLength() const {
        return queue->getSize();
    }

    bool isEmpty() const {
        return getLength() == 0;
    }

    Queue() {
        queue = new LinkedList<T>();
    }

    Queue(const Queue<T>& other) {
        queue = new LinkedList<T>();
    }

    Queue(Queue<T>&& other) noexcept {
        this->queue = other.queue;
        other.queue = nullptr;
    }

    Queue<T>& operator=(const Queue<T>& other) {
        if (this != &other) {
            delete queue;
            queue = new LinkedList<T>();
        }
        return *this;
    }

    Queue<T>& operator=(Queue<T>&& other) noexcept {
        if (this != &other) {
            delete queue;
            queue = other.queue;
            other.queue = nullptr;
        }
        return *this;
    }

    ~Queue() {
        if (queue != nullptr) {
            delete queue;
        }
    }
};