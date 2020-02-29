#include "test_runner.h"
#include <vector>
#include <future>
#include <numeric>
using namespace std;

template <typename Iterator>
class Page {
public:
	Page(Iterator begin, Iterator end)
		: first(begin)
		, last(end)
	{
	}

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

template <typename Iterator>
class Paginator {
public:
	Paginator(Iterator begin, Iterator end, size_t page_size)
	{
		Iterator page_start = begin;
		while (page_start != end) {
			size_t left = distance(page_start, end);
			Iterator page_end = next(page_start, min(left, page_size));
			pages.push_back(Page{ page_start, page_end });
			page_start = page_end;
		}
	}

	auto begin() const {
		return pages.begin();
	}

	auto end() const {
		return pages.end();
	}

	size_t size() const {
		return pages.size();
	}
private:
	vector<Page<Iterator>> pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator{ c.begin(), c.end(), page_size };
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
	const size_t page_size = matrix.size() > 4 ? matrix.size() / 4 : 4;
	vector<future<int64_t>> futures;
	for (auto page : Paginate(matrix, page_size)) {
		futures.push_back(
			async([=] {
				int64_t cur_sum = 0;
				for (const auto& row : page) {
					cur_sum += accumulate(row.begin(), row.end(), 0);
				}
				return cur_sum;
			})
		);
	}

	int64_t sum = 0;
	for (auto& future : futures) {
		sum += future.get();
	}

	return sum;
}

void TestCalculateMatrixSum() {
	const vector<vector<int>> matrix = {
	  {1, 2, 3, 4},
	  {5, 6, 7, 8},
	  {9, 10, 11, 12},
	  {13, 14, 15, 16}
	};
	ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestCalculateMatrixSum);
}
