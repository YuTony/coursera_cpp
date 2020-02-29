#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include "test_runner.h"

using namespace std;

template <typename T>
class PriorityCollection {
    struct Record {
        T value;
        int priority;

        Record(T value) : value(move(value)), priority(0) {}

        bool operator<(const Record& r) {
            return priority < r.priority;
        }
    };

   public:
    using Id = typename set<Record>::iterator;

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        auto tmp = data.insert({move(object)});
        if (tmp.second) return tmp.first;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
        move(range_begin, range_end, ids_begin);
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        // for (auto it = data.begin(); it != data.end(); it++) {
        //     if (it == id) return true;
        // }
        return (id > data.begin()) && (id < data.end());
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const {
        return id->second;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        id->first++;
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const {
        return data.end();
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax() {
        pair<T, int> tmp = move(*(data.end()));
        data.erase(data.end());
        return tmp;
    }

   private:
    vector<pair<int, T>> data;
    void SortData() {
        sort(data.begin(), data.end(), [](const pair<int, T>& l, const pair<int, T>& r) {
            return l.first < r.first;
        });
    }
};

class StringNonCopyable : public string {
   public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
