#pragma once
#include "date.h"
#include <vector>

using namespace std;

int Date::GetYear() const {
    return year_;
}
int Date::GetMonth() const {
    return month_;
}
int Date::GetDay() const {
    return day_;
}

Date ParseDate(istream& is) {
    int day, month, year;
    is >> year;
    is.ignore();
    is >> month;
    is.ignore();
    is >> day;
    return {year, month, day};
}

ostream& operator<<(ostream& st, const Date& date) {
    st << setfill('0');
    st << setw(4) << date.GetYear() << "-"
       << setw(2) << date.GetMonth() << "-"
       << setw(2) << date.GetDay();
    return st;
}

const bool operator<(const Date& x, const Date& y) {
    return make_tuple(x.GetYear(), x.GetMonth(), x.GetDay()) <
           make_tuple(y.GetYear(), y.GetMonth(), y.GetDay());
}

const bool operator<=(const Date& x, const Date& y) {
    return make_tuple(x.GetYear(), x.GetMonth(), x.GetDay()) <=
           make_tuple(y.GetYear(), y.GetMonth(), y.GetDay());
}

const bool operator>(const Date& x, const Date& y) {
    return make_tuple(x.GetYear(), x.GetMonth(), x.GetDay()) >
           make_tuple(y.GetYear(), y.GetMonth(), y.GetDay());
}

const bool operator>=(const Date& x, const Date& y) {
    return make_tuple(x.GetYear(), x.GetMonth(), x.GetDay()) >=
           make_tuple(y.GetYear(), y.GetMonth(), y.GetDay());
}

const bool operator==(const Date& x, const Date& y) {
    return (x.GetDay() == y.GetDay() && x.GetMonth() == y.GetMonth() && x.GetYear() == y.GetYear());
}

const bool operator!=(const Date& x, const Date& y) {
    return !(x.GetDay() == y.GetDay() && x.GetMonth() == y.GetMonth() && x.GetYear() == y.GetYear());
}