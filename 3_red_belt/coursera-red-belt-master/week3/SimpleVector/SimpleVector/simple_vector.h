#pragma once

#include <algorithm>
#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
	SimpleVector() = default;

	explicit SimpleVector(size_t size)
		: data_(new T[size])
		, size_(size)
		, capacity_(size)
	{
	}

	~SimpleVector() {
		delete[] data_;
	}

	T& operator[](size_t index) {
		return data_[index];
	}

	T* begin() { return data_; }
	T* end() { return data_ + size_; }

	const T* begin() const { return data_; }
	const T* end() const { return data_ + size_; }

	size_t Size() const { return size_; }
	size_t Capacity() const { return capacity_; }

	void PushBack(const T& value) {
		if (size_ == capacity_) {
			Reallocate();
		}
		data_[size_] = value;
		size_++;
	}

private:
	T* data_ = nullptr;
	size_t size_ = 0;
	size_t capacity_ = 0;

	void Reallocate() {
		capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
		T* tmp = new T[capacity_];
		std::copy(begin(), end(), tmp);
		delete[] data_;
		data_ = tmp;
	}
};
