#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdexcept>

template<typename T>
class Vector {
public:
    Vector() = default;

    explicit Vector(size_t capacity);

    Vector(size_t size, T const &defaultValue);

    Vector(Vector<T> const &other);

    Vector &operator=(Vector<T> const &other);

    ~Vector() noexcept;

    T &operator [](size_t index);

    T const &operator [](size_t index) const;

    void push_back(T const &value);

    void pop_back();

    void pop_front();

    void insert(size_t index, T const &value);

    void clear();

    bool empty() const;

    size_t size() const;

    size_t capacity() const;

private:
    void resize(size_t newCapacity);

    void copy(Vector<T> const &other);

    void free() noexcept;

    size_t capacity_ = 0;
    size_t size_ = 0;
    T *data_ = nullptr;
};

inline size_t closest_power_of_two(size_t const m_Size) {
    size_t pow = 1;
    while (pow < m_Size) {
        pow <<= 1;
    }
    return pow;
}

template<typename T>
Vector<T>::Vector(size_t capacity) {
    this->data_ = new T[capacity];
    this->capacity_ = capacity;
}

template<typename T>
Vector<T>::Vector(size_t size, T const &defaultValue) {
    this->capacity_ = closest_power_of_two(size);
    this->size_ = size;
    this->data_ = new T[this->capacity_];
    for (size_t i = 0; i < this->size_; i++) {
        this->data_[i] = defaultValue;
    }
}

template<typename T>
Vector<T>::Vector(Vector<T> const &other) {
    this->copy(other);
}

template<typename T>
Vector<T> &Vector<T>::operator =(Vector<T> const &other) {
    if (this == &other) {
        return *this;
    }
    *this = Vector<T>(other);
    return *this;
}

template<typename T>
Vector<T>::~Vector() noexcept {
    this->free();
}

template<typename T>
void Vector<T>::clear() {
    delete[] this->data_;
    this->data_ = nullptr;
    this->size_ = 0;
    this->capacity_ = 0;
}

template<typename T>
T &Vector<T>::operator [](size_t index) {
    if (index >= this->size_) {
        throw std::out_of_range("Index out of range");
    }
    return this->data_[index];
}

template<typename T>
T const &Vector<T>::operator [](size_t index) const {
    if (index >= this->size_) {
        throw std::out_of_range("Index out of range");
    }
    return this->data_[index];
}

template<typename T>
void Vector<T>::push_back(T const &value) {
    if (this->size_ == this->capacity_) {
        this->resize(this->capacity_ *= 2);
    }
    this->data_[this->size_++] = value;
}

template<typename T>
void Vector<T>::pop_back() {
    if (this->empty()) {
        return;
    }
    --this->size_;
    if (this->size_ == this->capacity_ / 4) {
        this->resize(this->capacity_ /= 2);
    }
}

template<typename T>
void Vector<T>::pop_front() {
    if (this->empty()) {
        return;
    }
    for (size_t i = 0; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }
    --this->size_;
    if (this->size_ == this->capacity_ / 4) {
        this->resize(this->capacity_ /= 2);
    }
}

template<typename T>
void Vector<T>::insert(size_t index, T const &value) {
    if (index > this->size_) {
        throw std::out_of_range("Index out of range");
    }
    if (this->size_ == this->capacity_) {
        resize(capacity_ *= 2);
    }

    for (size_t i = this->size_; i > index; --i) {
        this->data_[i] = this->data_[i - 1];
    }
    this->data_[index] = value;
    ++this->size_;
}

template<typename T>
bool Vector<T>::empty() const {
    return this->size_ == 0;
}

template<typename T>
size_t Vector<T>::size() const {
    return this->size_;
}

template<typename T>
size_t Vector<T>::capacity() const {
    return this->capacity_;
}

template<typename T>
void Vector<T>::resize(size_t newCapacity) {
    T *newData = new T[newCapacity];
    for (size_t i = 0; i < this->size_; ++i)
        newData[i] = this->data_[i];

    this->free();

    this->data_ = newData;
    this->capacity_ = newCapacity;
}

template<typename T>
void Vector<T>::copy(Vector<T> const &other) {
    this->data_ = new T[other.capacity_];
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    for (size_t i = 0; i < other.size_; ++i) {
        this->data_[i] = other.data_[i];
    }
}

template<typename T>
void Vector<T>::free() noexcept {
    delete[] this->data_;
}

#endif // VECTOR_HPP
