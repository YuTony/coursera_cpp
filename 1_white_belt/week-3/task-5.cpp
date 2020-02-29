#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

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
    string GetFullNameWithHistory(int year) {
        sort(begin(first_names), end(first_names), [](NAME x, NAME y) {
            return (x.year > y.year);
        });
        sort(begin(last_names), end(last_names), [](NAME x, NAME y) {
            return (x.year > y.year);
        });
        string ans;
        if ((first_names.size() > 0) && first_names[end(first_names) - begin(first_names) - 1].year <= year) {
            auto num_fn = find_if(begin(first_names), end(first_names), [&](NAME x) {
                return (x.year <= year);
            });
            ans += (*num_fn).name + " ";
            string tmp_ans;
            if (num_fn + 1 != end(first_names)) {
                tmp_ans += "(";
                while (++num_fn != end(first_names)) {
                    if ((*(num_fn - 1)).name != (*num_fn).name)
                        tmp_ans += (*num_fn).name;
                    else
                        continue;
                    if (num_fn + 1 != end(first_names)) {
                        tmp_ans += ", ";
                    }
                }
                tmp_ans += ") ";
                if (tmp_ans != "() ")
                    ans += tmp_ans;
            }
            if ((last_names.size() > 0) && (last_names[end(last_names) - begin(last_names) - 1].year <= year)) {
                auto num_ln = find_if(begin(last_names), end(last_names), [&](NAME x) {
                    return (x.year <= year);
                });
                // return first_names[num_fn - begin(first_names)].name + ' ' + last_names[num_ln - begin(last_names)].name;
                ans += (*num_ln).name;
                string tmp_ans;
                if (num_ln + 1 != end(last_names)) {
                    tmp_ans += " (";
                    while (++num_ln != end(last_names)) {
                        if ((*(num_ln - 1)).name != (*num_ln).name)
                            tmp_ans += (*num_ln).name;
                        else
                            continue;
                        if (num_ln + 1 != end(last_names)) {
                            tmp_ans += ", ";
                        }
                    }
                    tmp_ans += ")";
                    if (tmp_ans != " ()")
                        ans += tmp_ans;
                }
            } else {
                ans += "with unknown last name";
            }
        } else {
            if ((last_names.size() > 0) && (last_names[end(last_names) - begin(last_names) - 1].year <= year)) {
                auto num_ln = find_if(begin(last_names), end(last_names), [&](NAME x) {
                    return (x.year <= year);
                });
                ans += (*num_ln).name + " ";
                string tmp_ans;
                if (num_ln + 1 != end(last_names)) {
                    tmp_ans += "(";
                    while (++num_ln != end(last_names)) {
                        if ((*(num_ln - 1)).name != (*num_ln).name)
                            tmp_ans += (*num_ln).name;
                        else
                            continue;
                        if (num_ln + 1 != end(last_names)) {
                            tmp_ans += ", ";
                        }
                    }
                    tmp_ans += ") ";
                    if (tmp_ans != "() ")
                        ans += tmp_ans;
                }
                ans += "with unknown first name";
            } else {
                ans += "Incognito";
            }
        }
        return ans;
    }

   private:
    vector<NAME> first_names, last_names;
};

/*int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;
  
  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;
  
  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;
  
  return 0;
}*/

/*int main() {
    Person person;

    person.ChangeFirstName(1900, "Eugene");
    person.ChangeLastName(1900, "Sokolov");
    person.ChangeLastName(1910, "Sokolov");
    person.ChangeFirstName(1920, "Evgeny");
    person.ChangeLastName(1930, "Sokolov");
    cout << person.GetFullNameWithHistory(1940) << endl;

    return 0;
}*/