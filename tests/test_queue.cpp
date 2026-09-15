// Тесты очереди (GoogleTest).
#include <gtest/gtest.h>

#include <string>

#include "queue.h"

using lab4::Queue;
using lab4::QueueEmptyError;

TEST(QueueTest, EmptyByDefault) {
    Queue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
}

TEST(QueueTest, FifoOrder) {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    EXPECT_EQ(q.size(), 3u);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 3);
    EXPECT_EQ(q.dequeue(), 1);
    EXPECT_EQ(q.dequeue(), 2);
    EXPECT_EQ(q.dequeue(), 3);
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, DequeueEmptyThrows) {
    Queue<int> q;
    EXPECT_THROW(q.dequeue(), QueueEmptyError);
}

TEST(QueueTest, FrontEmptyThrows) {
    Queue<int> q;
    EXPECT_THROW(q.front(), QueueEmptyError);
}

TEST(QueueTest, BackEmptyThrows) {
    Queue<int> q;
    EXPECT_THROW(q.back(), QueueEmptyError);
}

TEST(QueueTest, FrontBackDoNotRemove) {
    Queue<int> q;
    q.enqueue(7);
    q.enqueue(8);
    EXPECT_EQ(q.front(), 7);
    EXPECT_EQ(q.back(), 8);
    EXPECT_EQ(q.size(), 2u);
}

TEST(QueueTest, Contains) {
    Queue<int> q;
    q.enqueue(100);
    q.enqueue(200);
    EXPECT_TRUE(q.contains(100));
    EXPECT_TRUE(q.contains(200));
    EXPECT_FALSE(q.contains(500));
    q.dequeue();
    EXPECT_FALSE(q.contains(100));
}

TEST(QueueTest, Clear) {
    Queue<int> q;
    for (int i = 0; i < 4; ++i) {
        q.enqueue(i);
    }
    q.clear();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
    q.enqueue(1);  // после clear всё ещё работает
    EXPECT_EQ(q.dequeue(), 1);
}

TEST(QueueTest, WrapAroundAndGrowth) {
    Queue<int> q(3);
    for (int i = 1; i <= 5; ++i) {
        q.enqueue(i);  // переполнение буфера, расширение
    }
    for (int i = 1; i <= 3; ++i) {
        q.dequeue();  // сдвиг "головы"
    }
    for (int i = 6; i <= 8; ++i) {
        q.enqueue(i);
    }
    // Ожидаемый порядок: 4 5 6 7 8
    for (int i = 4; i <= 8; ++i) {
        EXPECT_EQ(q.dequeue(), i);
    }
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, LargeThroughput) {
    Queue<int> q;
    const int n = 10000;
    for (int i = 0; i < n; ++i) {
        q.enqueue(i);
    }
    int wrong = 0;
    for (int i = 0; i < n; ++i) {
        if (q.dequeue() != i) {
            ++wrong;
        }
    }
    EXPECT_EQ(wrong, 0);
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, StringsWork) {
    Queue<std::string> q;
    q.enqueue("первая");
    q.enqueue("вторая");
    EXPECT_EQ(q.front(), "первая");
    EXPECT_EQ(q.back(), "вторая");
    q.dequeue();
    EXPECT_EQ(q.front(), "вторая");
}

TEST(QueueTest, ToStringEmpty) {
    Queue<int> q;
    EXPECT_EQ(q.to_string(), "[] (слева — голова)");
}

TEST(QueueTest, ToStringFilled) {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    EXPECT_EQ(q.to_string(), "[1 2 3] (слева — голова)");
}
