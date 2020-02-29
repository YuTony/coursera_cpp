#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>
#include "test_runner.h"

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    // Напишите реализацию функции,
    // не копируя сортируемые элементы
    if (range_end - range_begin < 2) {
        return;
    }
    vector<typename RandomIt::value_type> tmp(make_move_iterator(range_begin), make_move_iterator(range_end));
    RandomIt it1 = tmp.begin() + tmp.size() / 3;
    RandomIt it2 = it1 + tmp.size() / 3;

    MergeSort(tmp.begin(), it1);
    MergeSort(it1, it2);
    MergeSort(it2, tmp.end());

    vector<typename RandomIt::value_type> tmp2;
    merge(make_move_iterator(tmp.begin()), make_move_iterator(it1), make_move_iterator(it1), make_move_iterator(it2), back_inserter(tmp2));
    merge(make_move_iterator(tmp2.begin()), make_move_iterator(tmp2.end()), make_move_iterator(it2), make_move_iterator(tmp.end()), range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
