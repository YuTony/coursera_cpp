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

Date ParseDate(std::istream &is) {
    int day, month, year;
    char c1, c2;
    is >> year >> c1 >> month >> c2 >> day;
    return {day, month, year};
}

ostream &operator<<(ostream &st, const Date &date) {
    st << setfill('0');
    st << setw(4) << date.GetYear() << "-"
       << setw(2) << date.GetMonth() << "-"
       << setw(2) << date.GetDay();
    return st;
}

bool operator<(const Date &x, const Date &y) {
    return vector<int>{x.GetYear(), x.GetMonth(), x.GetDay()} <
           vector<int>{y.GetYear(), y.GetMonth(), y.GetDay()};
}

bool operator<=(const Date &x, const Date &y) {
    return vector<int>{x.GetYear(), x.GetMonth(), x.GetDay()} <=
           vector<int>{y.GetYear(), y.GetMonth(), y.GetDay()};
}

bool operator>(const Date &x, const Date &y) {
    return vector<int>{x.GetYear(), x.GetMonth(), x.GetDay()} >
           vector<int>{y.GetYear(), y.GetMonth(), y.GetDay()};
}

bool operator>=(const Date &x, const Date &y) {
    return vector<int>{x.GetYear(), x.GetMonth(), x.GetDay()} >=
           vector<int>{y.GetYear(), y.GetMonth(), y.GetDay()};
}

bool operator==(const Date &x, const Date &y) {
    return (x.GetDay() == y.GetDay() && x.GetMonth() == y.GetMonth() && x.GetYear() == y.GetYear());
}

bool operator!=(const Date &x, const Date &y) {
    return !(x.GetDay() == y.GetDay() && x.GetMonth() == y.GetMonth() && x.GetYear() == y.GetYear());
}