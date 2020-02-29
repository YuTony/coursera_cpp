#include <vector>

// #include "test_runner.h"

using namespace std;

template <typename T>
class Deque {
   public:
    Deque() {}
    bool Empty() const {
        return (l.empty() && r.empty());
    }

    size_t Size() const {
        return l.size() + r.size();
    }

    const T& operator[](size_t i) const {
        if (i < l.size()) {
            return l[l.size() - 1 - i];
        } else {
            return r[i - l.size()];
        }
    }

    T& operator[](size_t i) {
        if (i < l.size()) {
            return l[l.size() - 1 - i];
        } else {
            return r[i - l.size()];
        }
    }

    const T& At(size_t i) const {
        if (i < l.size()) {
            return l.at(l.size() - 1 - i);
        } else {
            return r.at(i - l.size());
        }
    }

    T& At(size_t i) {
        if (i < l.size()) {
            return l.at(l.size() - 1 - i);
        } else {
            return r.at(i - l.size());
        }
    }

    const T& Front() const {
        if (!l.empty()) {
            return l.back();
        } else {
            return r.front();
        }
    }

    T& Front() {
        if (!l.empty()) {
            return l.back();
        } else {
            return r.front();
        }
    }

    const T& Back() const {
        if (!r.empty()) {
            return r.back();
        } else {
            return l.front();
        }
    }

    T& Back() {
        if (!r.empty()) {
            return r.back();
        } else {
            return l.front();
        }
    }

    void PushFront(const T& x) {
        l.push_back(x);
    }

    void PushBack(const T& x) {
        r.push_back(x);
    }

   private:
    vector<T> l, r;
};

// void test() {
//     Deque<int> d;
//     for (int i = 0; i < 10; i++) {
//         d.PushBack(i);
//     }
//     for (int i = 0; i > -10; i--) {
//         d.PushFront(i);
//     }
//     ASSERT_EQUAL(d.Front(), -9);
//     ASSERT_EQUAL(d.Back(), 9);
//     d[19] = 10;
//     ASSERT_EQUAL(d.Back(), 10);
//     d[0] = -10;
//     ASSERT_EQUAL(d.Front(), -10);

//     ASSERT_EQUAL(d.At(1), -8);
//     ASSERT_EQUAL(d.At(18), 8);
// }

// int main() {
//     TestRunner tr;
//     RUN_TEST(tr, test);
// }