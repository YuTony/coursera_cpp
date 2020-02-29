#include "phone_number.h"

#include <sstream>

PhoneNumber::PhoneNumber(const string &international_number) {
    stringstream ss(international_number);
    char t1, t2, t3;
    if (!(ss >> t1 && getline(ss, country_code_, '-') && ss.unget() &&
          ss >> t2 && getline(ss, city_code_, '-') && ss.unget() &&
          ss >> t3 && ss >> local_number_ &&
          t1 == '+' && t2 == '-' && t3 == '-'))
        throw invalid_argument("");
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}
string PhoneNumber::GetCityCode() const {
    return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}