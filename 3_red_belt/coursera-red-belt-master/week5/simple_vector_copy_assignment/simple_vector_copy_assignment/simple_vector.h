#pragma once

#include <algorithm>
#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
	SimpleVector() = default;

	explicit SimpleVector(size_t sz)
		: data(new T[sz])
		, size(sz)
		, capacity(sz)
	{
	}

	SimpleVector(const SimpleVector& other) 
		: data(new T[other.capacity])
		, size(other.size)
		, capacity(other.capacity)
	{
		std::copy(other.begin(), other.end(), begin());
	}

	SimpleVector& operator=(const SimpleVector& other) {
		if (other.size <= capacity) {
			std::copy(other.begin(), other.end(), begin());
			size = other.size;
		} else {
			SimpleVector tmp(other);
			std::swap(data, tmp.data);
			std::swap(size, tmp.size);
			std::swap(capacity, tmp.capacity);
		}
		return *this;
	}

	~SimpleVector() {
		delete[] data;
	}

	T& operator[](size_t index) {
		return data[index];
	}

	T* begin() { return data; }
	T* end() { return data + size; }

	const T* begin() const { return data; }
	const T* end() const { return data + size; }

	size_t Size() const { return size; }
	size_t Capacity() const { return capacity; }

	void PushBack(const T& value) {
		if (size == capacity) {
			Reallocate();
		}
		data[size] = value;
		size++;
	}

private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void Reallocate() {
		capacity = (capacity == 0) ? 1 : capacity * 2;
		T* tmp = new T[capacity];
		std::copy(begin(), end(), tmp);
		delete[] data;
		data = tmp;
	}
};
