#ifndef LAB4_STACK_H
#define LAB4_STACK_H

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace lab4 {

// Ошибка обращения к пустому стеку (pop / top).
class StackEmptyError : public std::runtime_error {
public:
    StackEmptyError() : std::runtime_error("стек пуст: операция невозможна") {}
};

// Стек (LIFO) на vector
// Снимается всегда последний добавленный элемент
template <typename T>
class Stack {
public:
    using size_type = std::size_t;

    Stack() = default;
    explicit Stack(size_type reserve) { data_.reserve(reserve); }

    void push(const T& value);      // положить элемент на вершину
    void pop();                     // снять вершину
    const T& top() const;           // вершина без удаления
    bool contains(const T& value) const;  // есть ли элемент в стеке
    size_type size() const;         // количество элементов
    bool empty() const;             // пуст ли стек
    void clear();                   // удалить все элементы
    std::string to_string() const;  // человекочитаемый вид

private:
    std::vector<T> data_;
};

}  // namespace lab4

#endif  // LAB4_STACK_H
