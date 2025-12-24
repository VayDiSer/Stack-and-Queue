#include <gtest/gtest.h>
#include "stack.h"
#include "queue.h"
#include "minstack.h"

// Stack
TEST(StackTest, IsEmptyOnCreation) {
    Stack<int> stack;
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, PushAndTop) {
    Stack<int> stack;
    stack.push(42);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 42);
}

TEST(StackTest, MultiplePush) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), 3);
}

TEST(StackTest, Pop) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    stack.pop();
    EXPECT_EQ(stack.top(), 1);
    EXPECT_EQ(stack.size(), 1);

    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST(StackTest, PopEmptyThrows) {
    Stack<int> stack;
    EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(StackTest, TopEmptyThrows) {
    Stack<int> stack;
    EXPECT_THROW(stack.top(), std::out_of_range);
}

TEST(StackTest, Clear) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.clear();
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

// Queue
TEST(QueueTest, IsEmptyOnCreation) {
    Queue<int> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTest, PushAndFront) {
    Queue<int> queue;
    queue.push(42);
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 42);
}

TEST(QueueTest, MultiplePush) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 3);
}

TEST(QueueTest, Pop) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    queue.pop();
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.size(), 2);

    queue.pop();
    EXPECT_EQ(queue.front(), 3);
    EXPECT_EQ(queue.size(), 1);

    queue.pop();
    EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, PopEmptyThrows) {
    Queue<int> queue;
    EXPECT_THROW(queue.pop(), std::out_of_range);
}

TEST(QueueTest, FrontEmptyThrows) {
    Queue<int> queue;
    EXPECT_THROW(queue.front(), std::out_of_range);
}

TEST(QueueTest, BackEmptyThrows) {
    Queue<int> queue;
    EXPECT_THROW(queue.back(), std::out_of_range);
}

TEST(QueueTest, Clear) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    queue.clear();
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

// MinStack
TEST(MinStackTest, BasicMin) {
    MinStack<int> ms;
    ms.push(3);
    EXPECT_EQ(ms.getMin(), 3);

    ms.push(5);
    EXPECT_EQ(ms.getMin(), 3);

    ms.push(2);
    EXPECT_EQ(ms.getMin(), 2);

    ms.push(1);
    EXPECT_EQ(ms.getMin(), 1);

    ms.pop();
    EXPECT_EQ(ms.getMin(), 2);

    ms.pop();
    EXPECT_EQ(ms.getMin(), 3);
}

TEST(MinStackTest, DuplicateMins) {
    MinStack<int> ms;
    ms.push(2);
    ms.push(2);
    ms.push(3);

    EXPECT_EQ(ms.getMin(), 2);

    ms.pop();
    EXPECT_EQ(ms.getMin(), 2);

    ms.pop();
    EXPECT_EQ(ms.getMin(), 2);

    ms.pop();
    EXPECT_THROW(ms.getMin(), std::out_of_range);
}

TEST(MinStackTest, EmptyMinThrows) {
    MinStack<int> ms;
    EXPECT_THROW(ms.getMin(), std::out_of_range);
}

// Stress Tests 

#ifndef STRESS_N
#define STRESS_N 1000000 
#endif

TEST(Stack_Stress, LargePushPop) {
    Stack<int> s;
    const int N = STRESS_N;


    for (int i = 0; i < N; ++i) {
        s.push(i);
        EXPECT_EQ(s.top(), i);
        EXPECT_EQ(s.size(), static_cast<size_t>(i + 1));
    }

    EXPECT_EQ(s.size(), static_cast<size_t>(N));


    for (int i = N - 1; i >= 0; --i) {
        EXPECT_EQ(s.top(), i);
        s.pop();
    }

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

TEST(Stack_Stress, RepeatedPushPopCycles) {
    Stack<int> s;
    const int cycles = 100;
    const int per_cycle = 10000;

    for (int c = 0; c < cycles; ++c) {
        for (int i = 0; i < per_cycle; ++i) {
            s.push(i + c * per_cycle);
        }

        EXPECT_EQ(s.size(), static_cast<size_t>(per_cycle));

        for (int i = 0; i < per_cycle; ++i) {
            s.pop();
        }

        EXPECT_TRUE(s.empty());
        EXPECT_EQ(s.size(), 0u);
    }
}

TEST(Queue_Stress, LargePushPop) {
    Queue<int> q;
    const int N = STRESS_N;

    for (int i = 0; i < N; ++i) {
        q.push(i);
        EXPECT_EQ(q.back(), i);
        EXPECT_EQ(q.size(), static_cast<size_t>(i + 1));
    }

    EXPECT_EQ(q.size(), static_cast<size_t>(N));
    EXPECT_EQ(q.front(), 0);

    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(q.front(), i);
        q.pop();
    }

    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
}

TEST(Queue_Stress, RepeatedPushPopCycles) {
    Queue<int> q;
    const int cycles = 100;
    const int per_cycle = 10000;

    for (int c = 0; c < cycles; ++c) {
        for (int i = 0; i < per_cycle; ++i) {
            q.push(i + c * per_cycle);
        }

        EXPECT_EQ(q.size(), static_cast<size_t>(per_cycle));
        EXPECT_EQ(q.front(), c * per_cycle);

        for (int i = 0; i < per_cycle; ++i) {
            EXPECT_EQ(q.front(), i + c * per_cycle);
            q.pop();
        }

        EXPECT_TRUE(q.empty());
        EXPECT_EQ(q.size(), 0u);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}