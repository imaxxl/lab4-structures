#ifndef LAB4_QUEUE_H
#define LAB4_QUEUE_H

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace lab4 {

// Ошибка: dequeue/front/back из пустой очереди
class QueueEmptyError : public std::runtime_error {
public:
    QueueEmptyError() : std::runtime_error("очередь пуста: операция невозможна") {}
};

// Очередь (FIFO) на кольцевом буфере.
// Элементы добавляются в конец и снимаются с начала;
// при переполнении буфер автоматически расширяется.
template <typename T>
class Queue {
public:
    using size_type = std::size_t;

    Queue() = default;
    explicit Queue(size_type capacity) : buffer_(capacity) {}

    void enqueue(const T& value);    // положить элемент в конец
    T dequeue();                     // снять элемент с начала
    const T& front() const;          // "голова" без удаления
    const T& back() const;           // "хвост" без удаления
    bool contains(const T& value) const;
    size_type size() const;
    bool empty() const;
    void clear();
    std::string to_string() const;

private:
    void grow();  // удвоение кольцевого буфера
    std::vector<T> buffer_;
    size_type head_ = 0;  // позиция первого элемента
    size_type size_ = 0;
};

}  // namespace lab4

#endif  // LAB4_QUEUE_H
