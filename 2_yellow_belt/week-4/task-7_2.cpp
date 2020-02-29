#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) return;
    vector<typename RandomIt::value_type> v(range_begin, range_end);
    auto point1 = v.begin() + v.size() / 3;
    auto point2 = point1 + v.size() / 3;
    MergeSort(v.begin(), point1);
    MergeSort(point1, point2);
    MergeSort(point2, v.end());
    vector<typename RandomIt::value_type> tmp;
    merge(v.begin(), point1, point1, point2, back_inserter(tmp));
    merge(tmp.begin(), tmp.end(), point2, v.end(), range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}