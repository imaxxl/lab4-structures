// Тесты стека (GoogleTest).
#include <gtest/gtest.h>

#include <string>

#include "stack.h"

using lab4::Stack;
using lab4::StackEmptyError;

TEST(StackTest, EmptyByDefault) {
    Stack<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

TEST(StackTest, PushPopLifoOrder) {
    Stack<int> s;
    for (int i = 1; i <= 5; ++i) {
        s.push(i);
    }
    EXPECT_EQ(s.size(), 5u);
    for (int i = 5; i >= 1; --i) {
        EXPECT_EQ(s.top(), i);
        s.pop();
    }
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

TEST(StackTest, PopEmptyThrows) {
    Stack<int> s;
    EXPECT_THROW(s.pop(), StackEmptyError);
}

TEST(StackTest, TopEmptyThrows) {
    Stack<int> s;
    EXPECT_THROW(s.top(), StackEmptyError);
}

TEST(StackTest, TopDoesNotRemove) {
    Stack<int> s;
    s.push(42);
    EXPECT_EQ(s.top(), 42);
    EXPECT_EQ(s.top(), 42);
    EXPECT_EQ(s.size(), 1u);
}

TEST(StackTest, PushPopPushInterleaved) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.pop();       // сняли 2
    s.push(3);
    s.pop();       // сняли 3
    EXPECT_EQ(s.top(), 1);
    s.pop();
    EXPECT_TRUE(s.empty());
}

TEST(StackTest, Contains) {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    EXPECT_TRUE(s.contains(20));
    EXPECT_TRUE(s.contains(30));
    EXPECT_FALSE(s.contains(99));
    s.pop();  // сняли 30
    EXPECT_FALSE(s.contains(30));
}

TEST(StackTest, Clear) {
    Stack<int> s;
    for (int i = 0; i < 5; ++i) {
        s.push(i);
    }
    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
    EXPECT_THROW(s.pop(), StackEmptyError);
}

TEST(StackTest, GrowthBeyondInitialCapacity) {
    Stack<int> s(2);  // маленькая начальная ёмкость
    for (int i = 0; i < 10000; ++i) {
        s.push(i);
    }
    EXPECT_EQ(s.size(), 10000u);
    int wrong = 0;
    for (int i = 9999; i >= 0; --i) {
        if (s.top() != i) {
            ++wrong;
        }
        s.pop();
    }
    EXPECT_EQ(wrong, 0);
    EXPECT_TRUE(s.empty());
}

TEST(StackTest, StringsWork) {
    Stack<std::string> s;
    s.push("раз");
    s.push("два");
    EXPECT_EQ(s.top(), "два");
    s.pop();
    EXPECT_EQ(s.top(), "раз");
    EXPECT_TRUE(s.contains("раз"));
}

TEST(StackTest, ToStringEmpty) {
    Stack<int> s;
    EXPECT_EQ(s.to_string(), "[] (вершина справа)");
}

TEST(StackTest, ToStringFilled) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.to_string(), "[1 2 3] (вершина справа)");
}
