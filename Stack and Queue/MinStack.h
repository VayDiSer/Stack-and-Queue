#ifndef MINSTACK_H
#define MINSTACK_H

#include "Stack.h"
#include <stdexcept>

template <typename Type>
class MinStack : public Stack<Type> {
    Stack<Type> mins;

public:
    void push(const Type& el) {
        Stack<Type>::push(el);
        if (mins.empty() || el <= mins.top())
            mins.push(el);
    }

    Type pop() {
        if (this->empty())
            throw std::out_of_range("Error!");

        Type val = this->top();
        Stack<Type>::pop();

        if (!mins.empty() && val == mins.top())
            mins.pop();

        return val;
    }

    const Type& getMin() const {
        if (mins.empty())
            throw std::out_of_range("Error!");
        return mins.top();
    }
};

#endif 
