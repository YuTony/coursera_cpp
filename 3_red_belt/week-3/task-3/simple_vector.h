#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
   public:
    SimpleVector() : data(nullptr), size(0), capacity(0) {}
    explicit SimpleVector(size_t size) : data(new T[size]), size(size), capacity(size) {}
    ~SimpleVector() {
        delete[] data;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    T* begin() {
        return data;
    }
    T* end() {
        return data + Size();
    }

    size_t Size() const {
        return size;
    }
    size_t Capacity() const {
        return capacity;
    }
    void PushBack(const T& value) {
        if (capacity == 0) {
            data = new T[1];
            capacity = 1;
        } else if (size == capacity) {
            T* new_data = new T[capacity * 2];
            for (size_t i = 0; i < capacity; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity = Size() * 2;
        }
        data[size] = value;
        size++;
    }

   private:
    T* data;
    size_t size, capacity;
};
