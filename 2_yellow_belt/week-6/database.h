#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "date.h"

using namespace std;

typedef vector<pair<Date, string>> Records;
typedef pair<Date, string> Record;

class Database {
   public:
    void Add(const Date& date, const string& event);
    void Print(ostream& ss) const;
    pair<Date, string> Last(const Date& date) const;

    template <class Func>
    int RemoveIf(Func predicate) {
        // int counter = 0;

        // for (auto& rec : db) {
        //     auto func = [&]() {
        //         return find_if(rec.second.begin(), rec.second.end(), [&](const string& event) {
        //             return predicate(rec.first, event);
        //         });
        //     };
        //     auto event_it = func();
        //     // for (auto event_it = rec_it->second.begin(); event_it != rec_it->second.end(); event_it++) {
        //     //     if (predicate(rec_it->first, *event_it)) {
        //     //         if (rec_it->second.size() == 1) {
        //     //             auto tmp_it1 = rec_it++;
        //     //             db.erase(tmp_it1);
        //     //         } else {
        //     //             auto tmp_it2 = event_it++;
        //     //             rec_it->second.erase(tmp_it2);
        //     //         }
        //     //         counter++;
        //     //     }
        //     // }
        //     while (event_it != rec.second.end()) {
        //         if (rec.second.size() == 1) {
        //             db.erase(rec.first);
        //         } else {
        //             rec.second.erase(event_it);
        //         }
        //         event_it = func();
        //         counter++;
        //     }
        // }

        // auto db_it = db.begin();
        // while (db_it != db.end()) {
        //     bool deleted = false;
        //     auto event_it = db_it->second.begin();
        //     while (event_it != db_it->second.end()) {
        //         if (predicate(db_it->first, *event_it)) {
        //             counter++;
        //             if (db_it->second.size() == 1) {
        //                 db_it = db.erase(db_it);
        //                 deleted = true;
        //                 break;
        //             } else {
        //                 event_it = db_it->second.erase(event_it);
        //                 continue;
        //             }
        //         }
        //         event_it++;
        //     }
        //     if (!deleted) {
        //         db_it++;
        //     }
        // }
        // return counter;

        int counter = 0;
        auto db_it = db.begin();
        while (db_it != db.end()) {
            auto event = stable_partition(db_it->second.begin(), db_it->second.end(), [&](const string str) {
                return !predicate(db_it->first, str);
            });
            if (event != db_it->second.end()) {
                counter += distance(event, db_it->second.end());
                db_it->second.erase(event, db_it->second.end());

                db_unique[db_it->first].clear();
                db_unique[db_it->first].insert(db_it->second.begin(), db_it->second.end());
            };
            if (db_it->second.empty()) {
                db_unique.erase(db_it->first);
                db_it = db.erase(db_it);
            } else {
                ++db_it;
            }
        }
        return counter;
    }

    /* template <class Func>
    string FindIf(Func predicate) const {
        int counter = 0;
        stringstream ss;
        for (auto rec_it = db.begin(); rec_it != db.end(); rec_it++) {
            for (auto event_it = rec_it->second.begin(); event_it != rec_it->second.end(); event_it++) {
                if (predicate(rec_it->first, *event_it)) {
                    counter++;
                    ss << rec_it->first << " " << *event_it << endl;
                }
            }
        }
        ss << "Found " << counter << " entries";
        return ss.str();
    } */

    template <class Func>
    Records FindIf(Func predicate) const {
        Records ans;
        for (auto db_it = db.begin(); db_it != db.end(); db_it++) {
            for (auto event_it = db_it->second.begin(); event_it != db_it->second.end(); event_it++) {
                if (predicate(db_it->first, *event_it)) {
                    ans.push_back(make_pair(db_it->first, *event_it));
                }
            }
        }
        return ans;
    }

   private:
    map<Date, vector<string>> db;
    map<Date, set<string>> db_unique;
};

ostream& operator<<(ostream& os, const Record& rec) {
    os << rec.first << " " << rec.second;
    return os;
}