#include "test_runner.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int len = range_end - range_begin;
	if (len < 2) {
		return;
	}

	vector<typename RandomIt::value_type> v(make_move_iterator(range_begin), make_move_iterator(range_end));
	MergeSort(begin(v), begin(v) + len / 3);
	MergeSort(begin(v) + len / 3, begin(v) + 2 * len / 3);
	MergeSort(begin(v) + 2 * len / 3, end(v));

	vector<typename RandomIt::value_type> tmp;
	merge(
		make_move_iterator(begin(v)),
		make_move_iterator(begin(v) + len / 3),
		make_move_iterator(begin(v) + len / 3),
		make_move_iterator(begin(v) + 2 * len / 3),
		back_inserter(tmp));
	merge(
		make_move_iterator(begin(tmp)),
		make_move_iterator(end(tmp)),
		make_move_iterator(begin(v) + 2 * len / 3),
		make_move_iterator(end(v)),
		range_begin);
}

void TestIntVector() {
	vector<int> numbers = { 6, 1, 3, 9, 1, 9, 8, 12, 1 };
	MergeSort(begin(numbers), end(numbers));
	ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	return 0;
}
