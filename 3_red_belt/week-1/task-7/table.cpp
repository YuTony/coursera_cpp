#include "test_runner.h"

using namespace std;

template <typename T>
class Table {
   public:
    Table(const size_t n, const size_t m) : n(n), m(m) {
        Resize(n, m);
    }

    vector<T> operator[](const int i) const {
        return data.at(i);
    }

    vector<T>& operator[](const int i) {
        return data[i];
    }

    void Resize(size_t n, size_t m) {
        this->n = n;
        this->m = m;
        data.resize(n);
        for (vector<T>& row : data)
            row.resize(m);
    }

    auto Size() const {
        return make_pair(n, m);
    }

   private:
    vector<vector<T>> data;
    size_t n, m;
};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
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
