#include "stack.h"

#include <sstream>

namespace lab4 {

template <typename T>
void Stack<T>::push(const T& value) {
    data_.push_back(value);
}

template <typename T>
void Stack<T>::pop() {
    if (data_.empty()) {
        throw StackEmptyError();
    }
    data_.pop_back();
}

template <typename T>
const T& Stack<T>::top() const {
    if (data_.empty()) {
        throw StackEmptyError();
    }
    return data_.back();
}

template <typename T>
bool Stack<T>::contains(const T& value) const {
    for (const auto& item : data_) {
        if (item == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() const {
    return data_.size();
}

template <typename T>
bool Stack<T>::empty() const {
    return data_.empty();
}

template <typename T>
void Stack<T>::clear() {
    data_.clear();
}

template <typename T>
std::string Stack<T>::to_string() const {
    std::ostringstream out;
    out << "[";
    for (size_type i = 0; i < data_.size(); ++i) {
        if (i != 0) {
            out << ' ';
        }
        out << data_[i];
    }
    out << "] (вершина справа)";
    return out.str();
}

// Явная инстанциация: для типов, которые используются в приложении и тестах
template class Stack<int>;
template class Stack<double>;
template class Stack<std::string>;

}  // namespace lab4
