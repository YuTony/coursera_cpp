#include "test_runner.h"

#include <vector>
#include <utility>

using namespace std;

template <typename T>
class Table {
public:
	Table(size_t new_w, size_t new_h);

	vector<T>& operator[](size_t i);
	const vector<T>& operator[](size_t i) const;

	void Resize(size_t new_w, size_t new_h);

	pair<size_t, size_t> Size() const;
private:
	size_t w, h;
	vector<vector<T>> data;
};

template <typename T>
Table<T>::Table(size_t new_w, size_t new_h)
	: w(new_w)
	, h(new_h)
{
	data.assign(w, vector<T>(h));
}

template <typename T>
vector<T>& Table<T>::operator[](size_t i) {
	return data[i];
}

template <typename T>
const vector<T>& Table<T>::operator[](size_t i) const {
	return data[i];
}

template <typename T>
void Table<T>::Resize(size_t new_w, size_t new_h) {
	w = new_w;
	h = new_h;
	data.resize(w);
	for (auto& row : data) {
		row.resize(h);
	}
}

template <typename T>
pair<size_t, size_t> Table<T>::Size() const {
	return { w,h };
}

void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0];
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}
