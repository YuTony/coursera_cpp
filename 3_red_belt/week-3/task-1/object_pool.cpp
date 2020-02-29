#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
using namespace std;

template <class T>
class ObjectPool {
   public:
    T* Allocate() {
        T* tmp;
        if (!freeds.empty()) {
            tmp = freeds.front();
            freeds.pop();
        } else {
            tmp = new T;
        }
        selected.insert(tmp);
        return tmp;
    }
    T* TryAllocate() {
        T* tmp = nullptr;
        if (!freeds.empty()) {
            tmp = freeds.front();
            selected.insert(tmp);
            freeds.pop();
        }
        return tmp;
    }

    void Deallocate(T* object) {
        if (selected.count(object) == 0) {
            throw invalid_argument("");
        } else {
            selected.erase(object);
            freeds.push(object);
        }
    }

    ~ObjectPool() {
        while (!freeds.empty()) {
            delete freeds.front();
            freeds.pop();
        }
        for (auto& tmp : selected) {
            delete tmp;
        }
    }

   private:
    queue<T*> freeds;
    set<T*> selected;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
