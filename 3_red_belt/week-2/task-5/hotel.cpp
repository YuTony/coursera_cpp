#include "test_runner.h"

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Record {
    int64_t time;
    string hotel_name;
    int64_t client_id;
    int64_t room_count;
    Record(int64_t time, string hotel_name, int64_t client_id, int64_t room_count) : time(time),
                                                                                      hotel_name(hotel_name),
                                                                                      client_id(client_id),
                                                                                      room_count(room_count) {}
};

class HotelManager {
   public:
    HotelManager() : current_time(0) {}
    void Book(int64_t time, const string& hotel_name, const int64_t client_id, const int64_t room_count) {
        db.push({time, hotel_name, client_id, room_count});
        current_time = time;
        // if (client_count_.count(hotel_name) == 0) {
        //     client_count_[hotel_name] = 0;
        //     room_count_[hotel_name] = 0;
        // }
        users[hotel_name][client_id]++;
        if (users[hotel_name][client_id] == 1)
            client_count_[hotel_name]++;
        room_count_[hotel_name] += room_count;
    }
    uint64_t Clients(const string& hotel_name) {
        Remove();
        return client_count_.count(hotel_name) ? client_count_.at(hotel_name) : 0;
    }
    uint64_t Rooms(const string& hotel_name) {
        Remove();
        return room_count_.count(hotel_name) ? room_count_.at(hotel_name) : 0;
    }

   private:
    void Remove() {
        while (!db.empty() && current_time - db.front().time >= 86400) {
            Record& tmp = db.front();
            users[tmp.hotel_name][tmp.client_id]--;
            if (users[tmp.hotel_name][tmp.client_id] == 0)
                client_count_[tmp.hotel_name]--;
            room_count_[tmp.hotel_name] -= tmp.room_count;
            db.pop();
        }
    }

   private:
    queue<Record> db;                     //Очередь из записей
    map<string, uint64_t> client_count_;  //Колличество клиентоа для каждого отеля
    map<string, uint64_t> room_count_;    //Колличество занятых комнат
    map<string, map<int, int>> users;     //Колличество повторений пользователей
    int64_t current_time;                 //Текущее время
};

void test_forum() {
    HotelManager manager;

    // Test empty bookings
    ASSERT_EQUAL(manager.Clients("mariott"), 0);
    ASSERT_EQUAL(manager.Rooms("mariott"), 0);

    manager.Book(0, "mariott", 1, 10);
    manager.Book(0, "mariott", 1, 1);
    manager.Book(0, "mariott", 3, 1);
    manager.Book(0, "mariott", 4, 1);
    manager.Book(0, "hilton", 1, 1);
    manager.Book(0, "hilton", 1, 100);
    manager.Book(1, "hilton", 2, 5);

    // Test correctness
    ASSERT_EQUAL(manager.Clients("mariott"), 3);
    ASSERT_EQUAL(manager.Rooms("mariott"), 13);
    ASSERT_EQUAL(manager.Clients("hilton"), 2);
    ASSERT_EQUAL(manager.Rooms("hilton"), 106);

    manager.Book(86399, "mariott", 1, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 3);
    ASSERT_EQUAL(manager.Rooms("mariott"), 14);
    ASSERT_EQUAL(manager.Clients("hilton"), 2);
    ASSERT_EQUAL(manager.Rooms("hilton"), 106);

    // Test event past 1 day resets statics
    manager.Book(86400, "mariott", 1, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 1);
    ASSERT_EQUAL(manager.Rooms("mariott"), 2);
    ASSERT_EQUAL(manager.Clients("hilton"), 1);
    ASSERT_EQUAL(manager.Rooms("hilton"), 5);

    // Test no clients and room for the last day
    manager.Book(86401, "mariott", 5, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 2);
    ASSERT_EQUAL(manager.Rooms("mariott"), 3);
    ASSERT_EQUAL(manager.Clients("hilton"), 0);
    ASSERT_EQUAL(manager.Rooms("hilton"), 0);
}

void test_of() {
    HotelManager manager;
    ASSERT_EQUAL(manager.Clients("Marriott"), 0);
    ASSERT_EQUAL(manager.Rooms("Marriott"), 0);

    manager.Book(10, "FourSeasons", 1, 2);
    manager.Book(10, "Marriott", 1, 1);
    manager.Book(86409, "FourSeasons", 2, 1);

    ASSERT_EQUAL(manager.Clients("FourSeasons"), 2);
    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 3);
    ASSERT_EQUAL(manager.Clients("Marriott"), 1);

    manager.Book(86410, "Marriott", 2, 10);

    ASSERT_EQUAL(manager.Rooms("FourSeasons"), 1);
    ASSERT_EQUAL(manager.Rooms("Marriott"), 10);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    HotelManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            string hotel_name;
            int64_t client_id;
            int64_t room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        } else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Clients(hotel_name) << "\n";
        } else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Rooms(hotel_name) << "\n";
        }
    }
}

// int main() {
//     TestRunner tr;
//     RUN_TEST(tr, test_forum);
//     RUN_TEST(tr, test_of);
// }