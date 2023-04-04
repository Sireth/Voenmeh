#ifndef TERM_2_VECTOR_HPP
#define TERM_2_VECTOR_HPP


#include <cstddef>
#include <algorithm>
#include <stdexcept>

template<typename T>
class Vector {
private:
    T *m_data;
    size_t m_size;
    size_t m_capacity;

public:
    Vector() {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    Vector(const Vector &other) {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = new T[m_capacity];
        std::copy(other.m_data, other.m_data + m_size, m_data);
    }

    Vector(Vector &&other) noexcept {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = other.m_data;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Vector &operator=(const Vector &other) {
        if (this != &other) {
            if (m_capacity >= other.m_size) {
                m_size = other.m_size;
                std::copy(other.m_data, other.m_data + m_size, m_data);
            } else {
                Vector temp(other);
                std::swap(m_size, temp.m_size);
                std::swap(m_capacity, temp.m_capacity);
                std::swap(m_data, temp.m_data);
            }
        }
        return *this;
    }

    Vector &operator=(Vector &&other) noexcept {
        if (this != &other) {
            std::swap(m_size, other.m_size);
            std::swap(m_capacity, other.m_capacity);
            std::swap(m_data, other.m_data);
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    ~Vector() {
        delete[] m_data;
    }

    [[nodiscard]] size_t size() const {
        return m_size;
    }

    [[nodiscard]] bool empty() const {
        return m_size == 0;
    }

    T &operator[](size_t index) {
        return m_data[index];
    }

    const T &operator[](size_t index) const {
        return m_data[index];
    }

    void push_back(const T &value) {
        if (m_size == m_capacity) {
            reserve(m_capacity == 0 ? 1 : 2 * m_capacity);
        }
        m_data[m_size] = value;
        ++m_size;
    }

    void pop_back() {
        if (!empty()) {
            --m_size;
        }
    }

    void clear() {
        m_size = 0;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > m_capacity) {
            T *new_data = new T[new_capacity];
            std::copy(m_data, m_data + m_size, new_data);
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
    }

    void resize(size_t new_size) {
        if (new_size > m_size) {
            reserve(new_size);
            std::fill(m_data + m_size, m_data + new_size, T());
        }
        m_size = new_size;
    }

    void shrink_to_fit() {
        if (m_size < m_capacity) {
            T *new_data = new T[m_size];
            std::copy(m_data, m_data + m_size, new_data);
            delete[] m_data;
            m_data = new_data;
            m_capacity = m_size;
        }
    }

    T& at(std::size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Vector::at() index out of range");
        }
        return m_data[index];
    }

    const T& at(std::size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("Vector::at() index out of range");
        }
        return m_data[index];
    }

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        explicit iterator(pointer ptr) : ptr_(ptr) {}

        reference operator*() const {
            return *ptr_;
        }

        pointer operator->() const {
            return ptr_;
        }

        iterator &operator++() {
            ++ptr_;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++ptr_;
            return temp;
        }

        iterator &operator--() {
            --ptr_;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --ptr_;
            return temp;
        }

        iterator operator+(difference_type n) const {
            return iterator(ptr_ + n);
        }

        iterator operator-(difference_type n) const {
            return iterator(ptr_ - n);
        }

        difference_type operator-(const iterator &other) const {
            return ptr_ - other.ptr_;
        }

        iterator &operator+=(difference_type n) {
            ptr_ += n;
            return *this;
        }

        iterator &operator-=(difference_type n) {
            ptr_ -= n;
            return *this;
        }

        reference operator[](difference_type n) const {
            return *(ptr_ + n);
        }

        bool operator==(const iterator &other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const iterator &other) const {
            return ptr_ != other.ptr_;
        }

        bool operator<(const iterator &other) const {
            return ptr_ < other.ptr_;
        }

        bool operator<=(const iterator &other) const {
            return ptr_ <= other.ptr_;
        }

        bool operator>(const iterator &other) const {
            return ptr_ > other.ptr_;
        }

        bool operator>=(const iterator &other) const {
            return ptr_ >= other.ptr_;
        }

    private:
        pointer ptr_;
    };

    iterator begin() {
        return iterator(m_data);
    }

    iterator end() {
        return iterator(m_data + m_size);
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (m_size == m_capacity) {
            reserve(m_capacity == 0 ? 1 : 2 * m_capacity);
        }
        new (m_data + m_size) T(std::forward<Args>(args)...);
        ++m_size;
    }
};


#endif //TERM_2_VECTOR_HPP
