#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>

class Date {
public:
    Date(int day = 0, int month = 0, int year = 0) : day_(day), month_(month), year_(year) {}

    int GetYear() const;

    int GetMonth() const;

    int GetDay() const;

private:
    int day_;
    int month_;
    int year_;
};

Date ParseDate(std::istream &is);

std::ostream &operator<<(std::ostream &st, const Date &date);

bool operator<(const Date &x, const Date &y);

bool operator<=(const Date &x, const Date &y);

bool operator>(const Date &x, const Date &y);

bool operator>=(const Date &x, const Date &y);

bool operator==(const Date &x, const Date &y);

bool operator!=(const Date &x, const Date &y);