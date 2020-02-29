#include "test_runner.h"

#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
public:
	Deque() {}

	bool Empty() const {
		return head.empty() && tail.empty();
	}

	size_t Size() const {
		return head.size() + tail.size();
	}

	T& operator[](size_t i) {
		return (i < head.size()) ? head[head.size() - i - 1] : tail[i - head.size()];
	}

	const T& operator[](size_t i) const {
		return (i < head.size()) ? head[head.size() - i - 1] : tail[i - head.size()];
	}

	T& At(size_t i) {
		CheckIndex(i);
		return (*this)[i];
	}

	const T& At(size_t i) const {
		CheckIndex(i);
		return (*this)[i];
	}

	T& Front() {
		return head.empty() ? tail.front() : head.back();
	}

	const T& Front() const {
		return head.empty() ? tail.front() : head.back();
	}

	T& Back() {
		return tail.empty() ? head.front() : tail.back();
	}

	const T& Back() const {
		return tail.empty() ? head.front() : tail.back();
	}

	void PushFront(const T& val) {
		head.push_back(val);
	}

	void PushBack(const T& val) {
		tail.push_back(val);
	}
private:
	vector<T> head;
	vector<T> tail;

	void CheckIndex(size_t i) {
		if (i >= Size()) {
			throw out_of_range("index out of range");
		}
	}
};

void TestDeque() {
	Deque<int> t;
	ASSERT_EQUAL(t.Size(), 0);
	t.PushFront(2);
	t[0];
	t[0] = 2;
	ASSERT_EQUAL(t[0], 2);
	t.PushBack(3);
	t.PushFront(1);
	ASSERT_EQUAL(t.Size(), 3);
	ASSERT_EQUAL(t[0], 1);
	ASSERT_EQUAL(t[1], 2);
	ASSERT_EQUAL(t[2], 3);
	t.Front() = 4;
	t.Back() = 6;
	ASSERT_EQUAL(t[0], 4);
	ASSERT_EQUAL(t[1], 2);
	ASSERT_EQUAL(t[2], 6);
	ASSERT_EQUAL(t.Front(), 4);
	ASSERT_EQUAL(t.Back(), 6);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestDeque);
	return 0;
}
