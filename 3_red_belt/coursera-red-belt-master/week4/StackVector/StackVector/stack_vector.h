#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	typename array<T, N>::iterator begin();
	typename array<T, N>::iterator end();
	typename array<T, N>::const_iterator begin() const;
	typename array<T, N>::const_iterator end() const;

	size_t Size() const;
	size_t Capacity() const;

	void PushBack(const T& value);
	T PopBack();

private:
	array<T, N> _data;
	size_t _size;
};

template <typename T, size_t N>
StackVector<T, N>::StackVector(size_t a_size)
	: _size(a_size)
{
	if (a_size > N) {
		throw invalid_argument("size is greater than capacity");
	}
}

template <typename T, size_t N>
T& StackVector<T, N>::operator[](size_t index) {
	return _data[index];
}

template <typename T, size_t N>
const T& StackVector<T, N>::operator[](size_t index) const {
	return _data[index];
}

template <typename T, size_t N>
typename array<T,N>::iterator StackVector<T, N>::begin() {
	return _data.begin();
}

template <typename T, size_t N>
typename array<T, N>::iterator StackVector<T, N>::end() {
	return _data.begin() + _size;
}

template <typename T, size_t N>
typename array<T, N>::const_iterator StackVector<T, N>::begin() const {
	return _data.begin();
}

template <typename T, size_t N>
typename array<T, N>::const_iterator StackVector<T, N>::end() const {
	return _data.begin() + _size;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Size() const {
	return _size;
}

template <typename T, size_t N>
size_t StackVector<T, N>::Capacity() const {
	return N;
}

template <typename T, size_t N>
void StackVector<T, N>::PushBack(const T& value) {
	if (_size >= N) {
		throw overflow_error("size is out of capacity");
	} else {
		_data[_size++] = value;
	}
}

template <typename T, size_t N>
T StackVector<T, N>::PopBack() {
	if (_size == 0) {
		throw underflow_error("vector is empty");
	} else {
		return _data[--_size];
	}
}
