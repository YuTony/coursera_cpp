#pragma once

#include <algorithm>
#include <cstdlib>
#include <utility>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
   public:
    SimpleVector() : data(nullptr), size(0), capacity(0){};
    SimpleVector(const SimpleVector& sv) : data(new T[sv.capacity()]), size(sv.Size()), capacity(sv.Capacity()) {
        copy(sv.begin(), sv.end(), begin());
    }
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

    const T* begin() const {
        return data;
    }
    const T* end() const {
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

    void operator=(const SimpleVector& rhs) {
        if (rhs.size <= capacity) {
            // У нас достаточно памяти - просто копируем элементы
            copy(rhs.begin(), rhs.end(), begin());
            size = rhs.size;
        } else {
            // Это так называемая идиома copy-and-swap.
            // Мы создаём временный вектор с помощью
            // конструктора копирования, а затем обмениваем его поля со своими.
            // Так мы достигаем двух целей:
            //  - избегаем дублирования кода в конструкторе копирования
            //    и операторе присваивания
            //  - обеспечиваем согласованное поведение конструктора копирования
            //    и оператора присваивания
            SimpleVector<T> tmp(rhs);
            swap(tmp.data, data);
            swap(tmp.size, size);
            swap(tmp.capacity, capacity);
        }
    }

   private:
    T* data;
    size_t size, capacity;
};
