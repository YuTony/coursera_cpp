#pragma once

#include <ostream>
#include <string>
#include <tuple>
using namespace std;

struct Date {
    int year, month, day;
};

struct Time {
    int hours, minutes;
};

struct AirlineTicket {
    string from;
    string to;
    string airline;
    Date departure_date;
    Time departure_time;
    Date arrival_date;
    Time arrival_time;
    int price;
};

// bool operator<(const Date& x, const Date& y) {
//     return make_tuple(x.year, x.month, x.day) < make_tuple(y.year, y.month, y.day);
// }

// bool operator==(const Date& x, const Date& y) {
//     return (x.day == y.day && x.month == y.month && x.year == y.year);
// }

// ostream& operator<<(ostream& os, const Date& x) {
//     return os << x.year << "-" << x.month << "-" << x.day;
// }

// bool operator<(const Time& x, const Time& y) {
//     return make_tuple(x.hours, x.minutes) < make_tuple(y.hours, y.minutes);
// }