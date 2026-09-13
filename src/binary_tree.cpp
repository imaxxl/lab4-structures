#include "binary_tree.h"

#include <sstream>

namespace lab4 {

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    freeAll(root_);
    root_ = nullptr;
    count_ = 0;
}

template <typename T>
void BinarySearchTree<T>::freeAll(Node* node) {
    if (node == nullptr) {
        return;
    }
    freeAll(node->left);
    freeAll(node->right);
    delete node;
}

template <typename T>
void BinarySearchTree<T>::insertRecursive(Node*& node, const T& key) {
    if (node == nullptr) {
        node = new Node(key);
        return;
    }
    if (key < node->key) {
        insertRecursive(node->left, key);
    } else if (node->key < key) {
        insertRecursive(node->right, key);
    }
    // key == node->key: дубликат, игнорируем
}

template <typename T>
bool BinarySearchTree<T>::insert(const T& key) {
    if (contains(key)) {
        return false;
    }
    insertRecursive(root_, key);
    ++count_;
    return true;
}

// Удаляет найденный узел, возвращает корень нового поддерева.
// Предустановка: ключ гарантированно существует.
template <typename T>
typename BinarySearchTree<T>::Node*
BinarySearchTree<T>::eraseRecursive(Node* node, const T& key) {
    if (key < node->key) {
        node->left = eraseRecursive(node->left, key);
        return node;
    }
    if (node->key < key) {
        node->right = eraseRecursive(node->right, key);
        return node;
    }

    // Узел найден.
    Node* old = node;
    if (node->left == nullptr || node->right == nullptr) {
        // 0 или 1 потомок: заменяем узел его (единственным) поддеревом.
        node = (node->left != nullptr) ? node->left : node->right;
        delete old;
        return node;
    }

    // Два потомка: копируем ключ инордер-продолжателя
    // (минимальный ключ правого поддерева) и удаляем продолжателя.
    Node* successor = node->right;
    while (successor->left != nullptr) {
        successor = successor->left;
    }
    node->key = successor->key;
    node->right = eraseRecursive(node->right, successor->key);
    return node;
}

template <typename T>
bool BinarySearchTree<T>::erase(const T& key) {
    if (!contains(key)) {
        return false;
    }
    root_ = eraseRecursive(root_, key);
    --count_;
    return true;
}

template <typename T>
const typename BinarySearchTree<T>::Node*
BinarySearchTree<T>::findNode(const Node* node, const T& key) const {
    while (node != nullptr) {
        if (key < node->key) {
            node = node->left;
        } else if (node->key < key) {
            node = node->right;
        } else {
            return node;
        }
    }
    return nullptr;
}

template <typename T>
bool BinarySearchTree<T>::contains(const T& key) const {
    return findNode(root_, key) != nullptr;
}

template <typename T>
T BinarySearchTree<T>::minimum() const {
    if (empty()) {
        throw TreeEmptyError();
    }
    const Node* cur = root_;
    while (cur->left != nullptr) {
        cur = cur->left;
    }
    return cur->key;
}

template <typename T>
T BinarySearchTree<T>::maximum() const {
    if (empty()) {
        throw TreeEmptyError();
    }
    const Node* cur = root_;
    while (cur->right != nullptr) {
        cur = cur->right;
    }
    return cur->key;
}

template <typename T>
typename BinarySearchTree<T>::size_type BinarySearchTree<T>::size() const {
    return count_;
}

template <typename T>
bool BinarySearchTree<T>::empty() const {
    return root_ == nullptr;
}

template <typename T>
typename BinarySearchTree<T>::size_type
BinarySearchTree<T>::heightOf(const Node* node) {
    if (node == nullptr) {
        return 0;
    }
    size_type left = heightOf(node->left);
    size_type right = heightOf(node->right);
    return 1 + (left > right ? left : right);
}

template <typename T>
typename BinarySearchTree<T>::size_type BinarySearchTree<T>::height() const {
    return heightOf(root_);
}

template <typename T>
void BinarySearchTree<T>::clear() {
    freeAll(root_);
    root_ = nullptr;
    count_ = 0;
}

template <typename T>
void BinarySearchTree<T>::inorderRecursive(const Node* node,
                                            std::vector<T>& keys) const {
    if (node == nullptr) {
        return;
    }
    inorderRecursive(node->left, keys);
    keys.push_back(node->key);
    inorderRecursive(node->right, keys);
}

template <typename T>
void BinarySearchTree<T>::inorder(std::vector<T>& keys) const {
    keys.clear();
    inorderRecursive(root_, keys);
}

template <typename T>
void BinarySearchTree<T>::preorderRecursive(const Node* node,
                                             std::vector<T>& keys) const {
    if (node == nullptr) {
        return;
    }
    keys.push_back(node->key);
    preorderRecursive(node->left, keys);
    preorderRecursive(node->right, keys);
}

template <typename T>
void BinarySearchTree<T>::preorder(std::vector<T>& keys) const {
    keys.clear();
    preorderRecursive(root_, keys);
}

template <typename T>
std::string BinarySearchTree<T>::to_string() const {
    std::vector<T> keys;
    inorder(keys);
    std::ostringstream out;
    out << "[";
    for (size_type i = 0; i < keys.size(); ++i) {
        if (i != 0) {
            out << ' ';
        }
        out << keys[i];
    }
    out << "] (инордер)";
    return out.str();
}

template class BinarySearchTree<int>;
template class BinarySearchTree<std::string>;

}  // namespace lab4
