#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

class Person {
   public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }
    string GetFullName(int year) {
        auto first_name = first_names.upper_bound(year);
        bool no_first_name = first_name == first_names.begin();
        auto last_name = last_names.upper_bound(year);
        bool no_last_name = last_name == last_names.begin();
        stringstream ans;
        if (no_first_name && no_last_name) {
            ans << "Incognito";
        } else if (no_last_name) {
            ans << prev(first_name)->second << " with unknown last name";
        } else if (no_first_name) {
            ans << prev(last_name)->second << "with unknown first name";
        } else {
            ans << prev(first_name)->second << " " << prev(last_name)->second;
        }
        return ans.str();
    }

   private:
    map<int, string> first_names, last_names;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}
