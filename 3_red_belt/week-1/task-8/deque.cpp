#include <stdexcept>
#include <vector>

using namespace std;

template <typename T>
class Deque {
   public:
    Deque() : l(5), n(0), r(5) {
        data = vector<T>(10);
    }

    bool Empty() {
        return n == 0;
    }

    size_t Size() {
        return n;
    }

    T& operator[](size_t i) {
        return data[l + i];
    }

    const T& operator[](size_t i) const {
        return data[l + i];
    }

    T& At(size_t i) {
        if (i >= n) throw out_of_range();
        return data[l + i];
    }

    const T& At(size_t i) const {
        if (i >= n) throw out_of_range();
        return data[l + i];
    }

    T& Front() {
        return data[l];
    }

    const T& Front() const {
        return data[l];
    }

    T& Back() {
        return data[l + n - 1];
    }

    const T& Back() const {
        return data[l + n - 1];
    }

    void PushFront(const T& x) {
        if (l == 0) resize();
        data[l - 1] = x;
        n++;
        l--;
    }

    void PushBack(const T& x) {
        if (r == 0) resize();
        data[l + n] = x;
        n++;
        r--;
    }

   private:
    void resize() {
        size_t N = (l + n + r) * 2;
        int new_l = (N - n) / 2;
        int new_r = (N - n) / 2 + n % 2;
        vector<T> new_data(N);
        for (size_t i = 0; i < Size(); i++) {
            new_data[new_l + i] = data[l + i];
        }
        data = new_data;
        l = new_l;
        r = new_r;
    }

   private:
    vector<T> data;
    size_t l, n, r;
};

int main() {
    Deque<int> d;
    for (int i = 1; i < 10; i++) {
        d.PushBack(i);
    }
    for (int i = -1; i > -10; i--) {
        d.PushFront(i);
    }
    for (int i = 0; i < 20; i++) {
        int t = d[i];
        t++;
    }
}