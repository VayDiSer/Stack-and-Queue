#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include <stdexcept>
template<class Type>
class Queue {
private:
    std::vector<Type> data;
    size_t start = 0;
    size_t count = 0;

    size_t tail() const {
        return (start + count) % data.size();
    }

public:
    Queue() : data(8) {}

    void push(const Type& val) {
        if (count == data.size()) {
            std::vector<Type> new_data(data.size() * 2);
            for (size_t i = 0; i < count; ++i) {
                new_data[i] = std::move(data[(start + i) % data.size()]);
            }
            data = std::move(new_data);
            start = 0;
        }
        data[tail()] = val;
        count++;
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Error!");
        }
        start = (start + 1) % data.size();
        count--;
    }

    Type& front() {
        if (empty()) {
            throw std::out_of_range("Error!");
        }
        return data[start];
    }

    const Type& front() const {
        if (empty()) {
            throw std::out_of_range("Error!");
        }
        return data[start];
    }

    Type& back() {
        if (empty()) {
            throw std::out_of_range("Error!");
        }
        return data[(start + count - 1) % data.size()];
    }

    const Type& back() const {
        if (empty()) {
            throw std::out_of_range("Error!");
        }
        return data[(start + count - 1) % data.size()];
    }

    bool empty() const {
        return count == 0;
    }

    size_t size() const {
        return count;
    }

    void clear() {
        start = 0;
        count = 0;
    }
};

#endif 
