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
   public:
    using Id = int;
    using Prio = int;
    using It = set<pair<Prio, Id>>::iterator;

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        auto p = data_set.insert({0, data.size()});
        data.push_back({move(object), p.first});
        return data.size() - 1;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
        for (auto it = make_move_iterator(range_begin); it != make_move_iterator(range_end); it++) {
            *(ids_begin++) = Add(*it);
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        return (id >= 0) && (id <= data.size()) && data[id].second != data_set.end();
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const {
        return data[id].first;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        It it_old = data[id].second;
        data[id].second = data_set.insert({it_old->first + 1, it_old->second}).first;
        data_set.erase(it_old);
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const {
        // prev(data_set.end())->second->first
        // return {prev(data_set.end())->second->first, (data_set.end())->first};
        int index = prev(data_set.end())->second;
        return {data[index].first, prev(data_set.end())->first};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax() {
        auto it = prev(data_set.end());
        int index = it->second;
        Prio prio = it->first;
        data_set.erase(it);
        data[index].second = data_set.end();
        return {move(data[index].first), prio};
    }

   private:
    vector<pair<T, It>> data;
    set<pair<Prio, Id>> data_set;
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
