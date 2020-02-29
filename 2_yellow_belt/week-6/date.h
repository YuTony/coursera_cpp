#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class Date {
   public:
    Date(int year = 0, int month = 0, int day = 0) : day_(day), month_(month), year_(year) {}
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

   private:
    int day_;
    int month_;
    int year_;
};

Date ParseDate(istream& is);

ostream& operator<<(ostream& st, const Date& date);

const bool operator<(const Date& x, const Date& y);
const bool operator<=(const Date& x, const Date& y);
const bool operator>(const Date& x, const Date& y);
const bool operator>=(const Date& x, const Date& y);
const bool operator==(const Date& x, const Date& y);
const bool operator!=(const Date& x, const Date& y);