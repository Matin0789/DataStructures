#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdexcept>
#include <iostream>

namespace mine
{
    class Queue
    {
    public:
        explicit Queue(long int);
        ~Queue();
        long int front();
        long int back();
        void push_front(long int);
        void push_back(long int);
        long int pop_front();
        long int pop_back();
        bool is_empty();
        size_t data_size();
        size_t capacity();
    private:
        size_t first;
        size_t size;
        size_t max_size;
        long int *data;
    };

    Queue::Queue(long int max_size) : first(0), size(0), max_size(max_size), data(new long int[max_size])
    {
        
    }

    Queue::~Queue()
    {
        delete[] data;
    }

    long int Queue::front() {
        if (size <= 0) {
            throw std::runtime_error("The Queue is empty!");
        }
        return data[first];
    }

    long int Queue::back() {
        if (size <= 0) {
            throw std::runtime_error("The Queue is empty!");
        }
        return data[(first + (size - 1)) % max_size];
    }

    void Queue::push_front(long int value) {
        if (size >= max_size) {
            throw std::overflow_error("Queue overflow");
        }
        size++;
        first = first > 0 ?  (first - 1) : max_size - 1;
        data[first] = value;
    }

    void Queue::push_back(long int value) {
        if (size >= max_size) {
            throw std::overflow_error("Queue overflow");
        }
        data[(first + size) % max_size] = value;
        size++;
    }

    long int Queue::pop_front() {
        if (size <= 0) {
            throw std::overflow_error("Queue underflow");
        }
        long int value = data[first];
        first = (first + 1) % max_size;
        size--;
        return value;
    }

    long int Queue::pop_back() {
        if (size <= 0) {
            throw std::overflow_error("Queue underflow");
        }
        long int value = data[(first + size) % max_size];
        size--;
        return value;
    }

    bool Queue::is_empty() {
        return size == 0;
    }

    size_t Queue::capacity() {
        return this->max_size;
    }

    size_t Queue::data_size() {
        return this->size;
    }
}

#endif