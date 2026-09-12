#include "queue.h"

#include <sstream>
#include <utility>

namespace lab4 {

template <typename T>
void Queue<T>::grow() {
    size_type cap = buffer_.size() * 2;
    if (cap == 0) {
        cap = 4;
    }
    std::vector<T> next(cap);
    for (size_type i = 0; i < size_; ++i) {
        next[i] = std::move(buffer_[(head_ + i) % buffer_.size()]);
    }
    buffer_ = std::move(next);
    head_ = 0;
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
    if (size_ == buffer_.size()) {
        grow();
    }
    buffer_[(head_ + size_) % buffer_.size()] = value;
    ++size_;
}

template <typename T>
T Queue<T>::dequeue() {
    if (size_ == 0) {
        throw QueueEmptyError();
    }
    T value = std::move(buffer_[head_]);
    buffer_[head_] = T{};  // обнуляем ссылку, чтобы не висела в буфере
    head_ = (head_ + 1) % buffer_.size();
    --size_;
    return value;
}

template <typename T>
const T& Queue<T>::front() const {
    if (size_ == 0) {
        throw QueueEmptyError();
    }
    return buffer_[head_];
}

template <typename T>
const T& Queue<T>::back() const {
    if (size_ == 0) {
        throw QueueEmptyError();
    }
    return buffer_[(head_ + size_ - 1) % buffer_.size()];
}

template <typename T>
bool Queue<T>::contains(const T& value) const {
    for (size_type i = 0; i < size_; ++i) {
        if (buffer_[(head_ + i) % buffer_.size()] == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
typename Queue<T>::size_type Queue<T>::size() const {
    return size_;
}

template <typename T>
bool Queue<T>::empty() const {
    return size_ == 0;
}

template <typename T>
void Queue<T>::clear() {
    buffer_.clear();
    head_ = 0;
    size_ = 0;
}

template <typename T>
std::string Queue<T>::to_string() const {
    std::ostringstream out;
    out << "[";
    for (size_type i = 0; i < size_; ++i) {
        if (i != 0) {
            out << ' ';
        }
        out << buffer_[(head_ + i) % buffer_.size()];
    }
    out << "] (слева — голова)";
    return out.str();
}

template class Queue<int>;
template class Queue<double>;
template class Queue<std::string>;

}  // namespace lab4
