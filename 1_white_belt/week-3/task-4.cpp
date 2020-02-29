#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

/*class Person {
   public:
    void ChangeFirstName(int year, const string& first_name_t) {
        first_name[year] = first_name_t;
        year_fn.push_back(year);
        sort(begin(year_fn), end(year_fn));
    }
    void ChangeLastName(int year, const string& last_name_t) {
        last_name[year] = last_name_t;
        year_ln.push_back(year);
        sort(begin(year_ln), end(year_ln));
    }
    string GetFullName(int year) {
        // if (first_name.count(year) == 0) {
        //     if (last_name.count(year) == 0) {
        //         return "Incognito";
        //     } else {
        //         return last_name[year] + " with unknown first name";
        //     }
        // } else {
        //     if (last_name.count(year) == 0) {
        //         return first_name[year] + " with unknown last name";
        //     } else {
        //         return first_name[year] + ' ' + last_name[year];
        //     }
        // }
        if (year_fn[0] <= year) {
            if (year_ln[0] <= year) {
                int tmp_year_fn = find_if(begin(year_fn), end(year_fn), [](int x){
                    return 
                })
                return first_name[year] + ' ' + last_name[year];
            } else {
                return first_name[year] + " with unknown last name";
            }
        } else {
            if (year_ln[0] <= year) {
                return last_name[year] + " with unknown first name";
            } else {
                return "Incognito";
            }
        }
    }

   private:
    map<int, string> first_name, last_name;
    vector<int> year_fn, year_ln;
};*/

struct NAME {
    int year;
    string name;
};

class Person {
   public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names.push_back({year, first_name});
    }
    void ChangeLastName(int year, const string& last_name) {
        last_names.push_back({year, last_name});
    }
    string GetFullName(int year) {
        sort(begin(first_names), end(first_names), [](NAME x, NAME y) {
            return (x.year > y.year);
        });
        sort(begin(last_names), end(last_names), [](NAME x, NAME y) {
            return (x.year > y.year);
        });
        if ((first_names.size() > 0) && first_names[end(first_names) - begin(first_names) - 1].year <= year) {
            auto num_fn = find_if(begin(first_names), end(first_names), [&](NAME x) {
                return (x.year <= year);
            });
            if ((last_names.size() > 0) && (last_names[end(last_names) - begin(last_names) - 1].year <= year)) {
                auto num_ln = find_if(begin(last_names), end(last_names), [&](NAME x) {
                    return (x.year <= year);
                });
                return first_names[num_fn - begin(first_names)].name + ' ' + last_names[num_ln - begin(last_names)].name;
            } else {
                return first_names[num_fn - begin(first_names)].name + " with unknown last name";
            }
        } else {
            if ((last_names.size() > 0) && (last_names[end(last_names) - begin(last_names) - 1].year <= year)) {
                auto num_ln = find_if(begin(last_names), end(last_names), [&](NAME x) {
                    return (x.year <= year);
                });
                return last_names[num_ln - begin(last_names)].name + " with unknown first name";
            } else {
                return "Incognito";
            }
        }
    }

   private:
    vector<NAME> first_names, last_names;
};

/*int main() {
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
    
    // int n;
    // cin >> n;
    // for (int i = 0; i < n; i++)
    // {
    //     char com;
    //     cin >> com;
    //     int y;
    //     string na;
    //     cin >> y >> na;
    //     if (com == 'f')
    //         person.ChangeFirstName(y, na);
    //     else 
    //         person.ChangeLastName(y, na);
    // }

    for (int i = 1950; i < 2000; i++) {
        cout << i << "    " << person.GetFullName(i) << endl;
    }
    

    return 0;
}*/