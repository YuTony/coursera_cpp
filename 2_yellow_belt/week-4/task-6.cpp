#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
    int age;           // возраст
    Gender gender;     // пол
    bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
        begin(range_copy), middle, end(range_copy),
        [](const Person &lhs, const Person &rhs) {
            return lhs.age < rhs.age;
        });
    return middle->age;
}

void PrintStats(vector<Person> persons) {
    auto male_end = partition(persons.begin(), persons.end(), [](const Person &p) {
        return p.gender == Gender::MALE;
    });
    auto emp_male_end = partition(persons.begin(), male_end, [](const Person &p) {
        return p.is_employed;
    });
    auto emp_female_end = partition(male_end, persons.end(), [](const Person &p) {
        return p.is_employed;
    });
    cout << "Median age = "
         << ComputeMedianAge(begin(persons), end(persons)) << endl;
    cout << "Median age for females = "
         << ComputeMedianAge(male_end, persons.end()) << endl;
    cout << "Median age for males = "
         << ComputeMedianAge(persons.begin(), male_end) << endl;
    cout << "Median age for employed females = "
         << ComputeMedianAge(male_end, emp_female_end) << endl;
    cout << "Median age for unemployed females = "
         << ComputeMedianAge(emp_female_end, persons.end()) << endl;
    cout << "Median age for employed males = "
         << ComputeMedianAge(persons.begin(), emp_male_end) << endl;
    cout << "Median age for unemployed males = "
         << ComputeMedianAge(emp_male_end, male_end) << endl;
}

int main() {
    vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}