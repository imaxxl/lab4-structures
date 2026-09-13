#ifndef LAB4_TREE_H
#define LAB4_TREE_H

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace lab4 {

// Ошибка обращения к пустому дереву (minimum / maximum).
class TreeEmptyError : public std::runtime_error {
public:
    TreeEmptyError() : std::runtime_error("дерево пусто: операция невозможна") {}
};

// Двоичное дерево поиска
// Ключи уникальные, дубликаты пропускаются
template <typename T>
class BinarySearchTree {
public:
    using size_type = std::size_t;

    BinarySearchTree() = default;
    ~BinarySearchTree();

    // Дерево владеет узлами по указателям — копируемость запрещена.
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    bool insert(const T& key);      // false, если ключ уже есть
    bool erase(const T& key);       // false, если ключ не найден
    bool contains(const T& key) const;
    T minimum() const;              // TreeEmptyError, если дерево пусто
    T maximum() const;
    size_type size() const;
    bool empty() const;
    size_type height() const;       // пустое дерево имеет высоту 0
    void clear();
    void inorder(std::vector<T>& keys) const;   // по возрастанию
    void preorder(std::vector<T>& keys) const;  // корень, лево, право
    std::string to_string() const;  // инордер-порядок

private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        explicit Node(const T& k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root_ = nullptr;
    size_type count_ = 0;

    void insertRecursive(Node*& node, const T& key);
    Node* eraseRecursive(Node* node, const T& key);
    const Node* findNode(const Node* node, const T& key) const;
    void inorderRecursive(const Node* node, std::vector<T>& keys) const;
    void preorderRecursive(const Node* node, std::vector<T>& keys) const;
    static size_type heightOf(const Node* node);
    static void freeAll(Node* node);
};

}  // namespace lab4

#endif  // LAB4_TREE_H
