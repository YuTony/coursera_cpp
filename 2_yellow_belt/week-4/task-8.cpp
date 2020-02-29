#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    auto lower = numbers.lower_bound(border);
    if (lower == numbers.begin()) return lower;
    auto prev_lower = prev(lower);
    if (lower == numbers.end()) return prev_lower;
    if (border - *prev_lower <= *lower - border) {
        return prev_lower;
    } else {
        return lower;
    }
}
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел

int main() {
    set<int> numbers = {1, 4, 6};
    cout << *FindNearestElement(numbers, 0) << " "
         << *FindNearestElement(numbers, 3) << " "
         << *FindNearestElement(numbers, 5) << " "
         << *FindNearestElement(numbers, 6) << " "
         << *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}