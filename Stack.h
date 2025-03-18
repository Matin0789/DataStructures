#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <iomanip>
#include <stddef.h>
#include <stdexcept>

namespace mine
{
    class Stack
    {
    public:
        explicit Stack(long int);
        ~Stack();
        void push(long int);
        long int pop();
        bool is_empty();
        size_t size();
        size_t capacity();

    private:
        size_t top;
        size_t max_size;
        long int *data;
    };

    Stack::Stack(long int max_size) : top(0), max_size(max_size), data(new long int[max_size])
    {
    }

    Stack::~Stack()
    {
        delete[] data;
    }

    void Stack::push(long int value)
    {
        if(top >= max_size) {
            throw std::overflow_error("stack overflow");
        }
        data[top] = value;
        top++;
    }

    long int Stack::pop()
    {
        if(top <= 0) {
            throw std::underflow_error("stack is empty");
        }
        long int item = data[top - 1];
        top--;
        return item;
    }

    bool Stack::is_empty()
    {
        return (top <= 0);
    }

    size_t Stack::size()
    {
        return this->top;
    }

    size_t Stack::capacity()
    {
        return max_size;
    }
}

#endif