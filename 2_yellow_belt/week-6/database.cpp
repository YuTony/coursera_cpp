#pragma once

#include "database.h"
#include <algorithm>
#include <sstream>

void Database::Add(const Date& date, const string& event) {
    // if (!binary_search(db[date].begin(), db[date].end(), event))
    //     db[date].push_back(event);
    // if (find(db[date].begin(), db[date].end(), event) == db[date].end())
    //     db[date].push_back(event);
    if (!db_unique[date].count(event)) {
        db[date].push_back(event);
        db_unique[date].insert(event);
    }
}

void Database::Print(ostream& os) const {
    // for (auto it = db.begin(); it != db.end(); it++) {
    //     for (const string& v : it->second) {
    //         os << it->first << " " << v << endl;
    //     }
    // }
    for (const auto& rec : db) {
        for (const string& event : rec.second) {
            os << rec.first << " " << event << endl;
        }
    }
}

/* template <class Func>
int Database::RemoveIf(Func predicate) {
    int counter = 0;
    for (auto& record : db) {
        Date& date = record.first;
        for (string& event : record.second) {
            if (predicate(date, event)) {
                if (db[date].size == 1) {
                    db.erase(date);
                } else {
                    db[date].erase(event);
                }
                counter++;
            }
        }
    }
    return counter;
}

template <class Func>
string Database::FindIf(Func predicate) const {
    stringstream ss;
    for (auto& record : db) {
        Date& date = record.first;
        for (string& event : record.second) {
            if (predicate(date, event)) {
                ss << date << " " << event << endl;
            }
        }
    }
    return ss.str();
} */

pair<Date, string> Database::Last(const Date& date) const {
    auto it = db.upper_bound(date);
    if (it == db.begin()) {
        throw invalid_argument("");
    } else {
        it--;
        return make_pair(it->first, it->second.back());
    }
}