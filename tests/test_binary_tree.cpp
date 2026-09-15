// Тесты двоичного дерева поиска (GoogleTest).
#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <vector>

#include "binary_tree.h"

using lab4::BinarySearchTree;
using lab4::TreeEmptyError;

TEST(TreeTest, EmptyByDefault) {
    BinarySearchTree<int> t;
    EXPECT_TRUE(t.empty());
    EXPECT_EQ(t.size(), 0u);
    EXPECT_EQ(t.height(), 0u);
    EXPECT_EQ(t.to_string(), "[] (инордер)");
}

TEST(TreeTest, InsertAndContains) {
    BinarySearchTree<int> t;
    EXPECT_TRUE(t.insert(5));
    EXPECT_TRUE(t.insert(3));
    EXPECT_TRUE(t.insert(8));
    EXPECT_TRUE(t.contains(5));
    EXPECT_TRUE(t.contains(3));
    EXPECT_TRUE(t.contains(8));
    EXPECT_FALSE(t.contains(6));
    EXPECT_EQ(t.size(), 3u);
}

TEST(TreeTest, DuplicateInsertIgnored) {
    BinarySearchTree<int> t;
    EXPECT_TRUE(t.insert(5));
    EXPECT_FALSE(t.insert(5));
    EXPECT_FALSE(t.insert(5));
    EXPECT_EQ(t.size(), 1u);
}

TEST(TreeTest, InorderSorted) {
    BinarySearchTree<int> t;
    const int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    for (int v : values) {
        t.insert(v);
    }
    std::vector<int> keys;
    t.inorder(keys);
    std::vector<int> sorted(values, values + 11);
    std::sort(sorted.begin(), sorted.end());
    EXPECT_EQ(keys, sorted);
}

TEST(TreeTest, PreorderRootFirst) {
    BinarySearchTree<int> t;
    t.insert(5);
    t.insert(3);
    t.insert(8);
    t.insert(2);
    t.insert(4);
    std::vector<int> keys;
    t.preorder(keys);
    EXPECT_EQ(keys.size(), 5u);
    EXPECT_EQ(keys[0], 5);  // корень всегда первым
    // остальные элементы — это остальные ключи в каком-то порядке
    keys.erase(keys.begin());
    std::sort(keys.begin(), keys.end());
    EXPECT_EQ((std::vector<int>{2, 3, 4, 8}), keys);
}

TEST(TreeTest, MinimumAndMaximum) {
    BinarySearchTree<int> t;
    const int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : values) {
        t.insert(v);
    }
    EXPECT_EQ(t.minimum(), 20);
    EXPECT_EQ(t.maximum(), 80);
}

TEST(TreeTest, MinMaxEmptyThrows) {
    BinarySearchTree<int> t;
    EXPECT_THROW(t.minimum(), TreeEmptyError);
    EXPECT_THROW(t.maximum(), TreeEmptyError);
}

TEST(TreeTest, Height) {
    BinarySearchTree<int> t;
    EXPECT_EQ(t.height(), 0u);
    t.insert(5);
    EXPECT_EQ(t.height(), 1u);
    t.insert(3);
    t.insert(8);
    EXPECT_EQ(t.height(), 2u);
    t.insert(2);
    t.insert(4);
    EXPECT_EQ(t.height(), 3u);
}

TEST(TreeTest, EraseLeaf) {
    BinarySearchTree<int> t;
    t.insert(5);
    t.insert(3);
    EXPECT_TRUE(t.erase(3));
    EXPECT_EQ(t.size(), 1u);
    EXPECT_FALSE(t.contains(3));
    EXPECT_TRUE(t.contains(5));
    std::vector<int> keys;
    t.inorder(keys);
    EXPECT_EQ((std::vector<int>{5}), keys);
}

TEST(TreeTest, EraseNodeWithOneChild) {
    BinarySearchTree<int> t;
    t.insert(5);
    t.insert(3);
    t.insert(2);
    EXPECT_TRUE(t.erase(3));  // 3 имеет только левого потомка (2)
    EXPECT_EQ(t.size(), 2u);
    EXPECT_TRUE(t.contains(2));
    std::vector<int> keys;
    t.inorder(keys);
    EXPECT_EQ((std::vector<int>{2, 5}), keys);
}

TEST(TreeTest, EraseNodeWithTwoChildren) {
    BinarySearchTree<int> t;
    const int values[] = {5, 3, 8, 2, 4, 7, 9};
    for (int v : values) {
        t.insert(v);
    }
    EXPECT_TRUE(t.erase(5));  // корень с двумя потомками
    EXPECT_EQ(t.size(), 6u);
    std::vector<int> keys;
    t.inorder(keys);
    EXPECT_EQ((std::vector<int>{2, 3, 4, 7, 8, 9}), keys);
    EXPECT_EQ(t.minimum(), 2);
    EXPECT_EQ(t.maximum(), 9);
}

TEST(TreeTest, EraseMissingReturnsFalse) {
    BinarySearchTree<int> t;
    t.insert(1);
    t.insert(2);
    EXPECT_FALSE(t.erase(99));
    EXPECT_EQ(t.size(), 2u);
}

TEST(TreeTest, EraseAllLeavesEmpty) {
    BinarySearchTree<int> t;
    for (int i = 1; i <= 5; ++i) {
        t.insert(i);
    }
    for (int i = 1; i <= 5; ++i) {
        EXPECT_TRUE(t.erase(i));
    }
    EXPECT_TRUE(t.empty());
    EXPECT_EQ(t.size(), 0u);
    EXPECT_EQ(t.height(), 0u);
}

TEST(TreeTest, Clear) {
    BinarySearchTree<int> t;
    t.insert(10);
    t.insert(20);
    t.insert(30);
    t.clear();
    EXPECT_TRUE(t.empty());
    EXPECT_EQ(t.size(), 0u);
    // после clear дерево снова usable
    EXPECT_TRUE(t.insert(1));
    EXPECT_EQ(t.size(), 1u);
}

TEST(TreeTest, SingleElementTree) {
    BinarySearchTree<int> t;
    t.insert(42);
    EXPECT_EQ(t.minimum(), 42);
    EXPECT_EQ(t.maximum(), 42);
    EXPECT_EQ(t.height(), 1u);
    EXPECT_TRUE(t.erase(42));
    EXPECT_TRUE(t.empty());
}

TEST(TreeTest, LargeRandomSetStaysSorted) {
    BinarySearchTree<int> t;
    std::vector<int> values(20000);
    std::iota(values.begin(), values.end(), 0);
    std::mt19937 gen(42);
    std::shuffle(values.begin(), values.end(), gen);

    for (int v : values) {
        EXPECT_TRUE(t.insert(v));
    }
    std::vector<int> keys;
    t.inorder(keys);
    EXPECT_EQ(keys.size(), values.size());
    for (std::size_t i = 0; i < keys.size(); ++i) {
        EXPECT_EQ(keys[i], static_cast<int>(i));
    }
}
