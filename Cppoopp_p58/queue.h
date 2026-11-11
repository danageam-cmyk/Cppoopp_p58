#pragma once
#include "linked_list.h"
#include <stdexcept>
#include <iostream>

template<typename T>
class Stack {
private:
    LinkedList<T>* stackList = nullptr;
public:
    void push(T data) {
        stackList->add(data);
    }

    T pop() {
        if (!isEmpty()) {
            return stackList->remove(stackList->getSize() - 1);
        }
        else {
            throw std::length_error("Stack<T>::pop(): Pop requested for empty stack");
        }
    }

    T peek() const {
        if (!isEmpty()) {
            T val = stackList->remove(stackList->getSize() - 1);
            stackList->add(val);
            return val;
        }
        else {
            throw std::length_error("Stack<T>::peek(): Peek requested for empty stack");
        }
    }

    size_t getLength() const {
        return stackList->getSize();
    }

    bool isEmpty() const {
        return getLength() == 0;
    }

    Stack() {
        stackList = new LinkedList<T>();
    }

    Stack(const Stack<T>& other) {
        stackList = other.stackList->clone();
    }

    Stack(Stack<T>&& other) noexcept {
        stackList = other.stackList;
        other.stackList = nullptr;
    }

    ~Stack() {
        if (stackList) delete stackList;
    }
};

template<typename T>
class Queue {
private:
    LinkedList<T>* queue = nullptr;
public:
    void enqueue(T data) {
        queue->add(data);
    }

    T dequeue() {
        if (getLength() > 0) {
            return queue->remove(0);
        }
        else {
            throw std::length_error("Queue<T>::dequeue(): Dequeue requested for empty queue");
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
        this->queue = other.queue->clone();
        std::cout << "Queue copied" << std::endl;
    }
    Queue(Queue<T>&& other) noexcept {
        this->queue = other.queue;
        other.queue = nullptr;
        std::cout << "Queue moved" << std::endl;
    }
    ~Queue() {
        if (queue) delete queue;
    }
};