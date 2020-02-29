#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <tuple>

using namespace std;

bool operator<(const Date& x, const Date& y) {
    return make_tuple(x.year, x.month, x.day) < make_tuple(y.year, y.month, y.day);
}

bool operator==(const Date& x, const Date& y) {
    return (x.day == y.day && x.month == y.month && x.year == y.year);
}

ostream& operator<<(ostream& os, const Date& x) {
    return os << x.year << "-" << x.month << "-" << x.day;
}

istream& operator>>(istream& is, Date& x) {
    is >> x.year;
    is.ignore();
    is >> x.month;
    is.ignore();
    is >> x.day;
    return is;
}

bool operator<(const Time& x, const Time& y) {
    return make_tuple(x.hours, x.minutes) < make_tuple(y.hours, y.minutes);
}

bool operator==(const Time& x, const Time& y) {
    return make_tuple(x.hours, x.minutes) == make_tuple(y.hours, y.minutes);
}

ostream& operator<<(ostream& os, const Time& x) {
    return os << x.hours << ":" << x.minutes;
}

istream& operator>>(istream& is, Time& x) {
    is >> x.hours;
    is.ignore();
    is >> x.minutes;
    return is;
}

#define UPDATE_FIELD(ticket, field, values) \
    {                                       \
        auto it = values.find(#field);      \
        if (it != values.end()) {           \
            stringstream ss(it->second);    \
            ss >> ticket.field;             \
        }                                   \
    }

void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
        {"departure_date", "2018-2-28"},
        {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
        {"price", "12550"},
        {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
