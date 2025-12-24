#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>
#include <deque>

template<class Type>
class Stack
{
    std::vector<Type> data;
public:
    Stack() = default;

    void push(const Type& el)
    {
        data.push_back(el);
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Error!");
        }
        data.pop_back();
    }
    Type& top()
    {
        if (empty())
        {
            throw std::out_of_range("Error!");
        }
        return data.back();
    }

    const Type& top() const
    {
        if (empty())
        {
            throw std::out_of_range("Error!");
        }
        return data.back();
    }

    size_t size() const
    {
        return data.size();
    }

    void clear()
    {
        data.clear();
    }

    bool empty() const
    {
        return data.empty();
    }
};

#endif 
