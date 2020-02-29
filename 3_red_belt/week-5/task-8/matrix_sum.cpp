#include <future>
#include <numeric>
#include <vector>
#include "test_runner.h"
using namespace std;

template <typename Iterator>
class IteratorRange {
   public:
    IteratorRange(Iterator f, Iterator s) : first(f), last(s) {}

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

    size_t size() const {
        return last - first;
    }

   private:
    Iterator first, last;
};

// Реализуйте шаблон класса Paginator

template <typename Iterator>
class Paginator {
   public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        // vector<IteratorRange<Iterator>> result;
        auto point2 = begin;
        while (point2 != end) {
            auto point1 = point2;
            point2 = next(point2, min(page_size, static_cast<size_t>(distance(point2, end))));
            data.push_back({point1, point2});
        }
    }

    auto begin() const {
        return data.begin();
    }

    auto end() const {
        return data.end();
    }

    size_t size() const {
        return data.size();
    }

   private:
    vector<IteratorRange<Iterator>> data;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    vector<future<int64_t>> futures;
    for (auto p : Paginate(matrix, 2000)) {
        futures.push_back(async([=]() {
            int64_t ans = 0;
            for (const auto& t : p) {
                for (auto i : t) {
                    ans += i;
                }
            }
            return ans;
        }));
    }
    int64_t ans = 0;
    for (auto& f : futures) {
        ans += f.get();
    }
    return ans;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
