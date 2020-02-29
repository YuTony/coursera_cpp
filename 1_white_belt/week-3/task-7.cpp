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
    Person(const string& first_name, const string& last_name, int date) {
        birthday = date;
        first_names.push_back({date, first_name});
        last_names.push_back({date, last_name});
    }
    void ChangeFirstName(int year, const string& first_name) {
        if (year > birthday)
            first_names.push_back({year, first_name});
        sort(begin(first_names), end(first_names), [](NAME x, NAME y) {
                return (x.year > y.year);
            });
    }
    void ChangeLastName(int year, const string& last_name) {
        if (year > birthday)
            last_names.push_back({year, last_name});
        sort(begin(last_names), end(last_names), [](NAME x, NAME y) {
                return (x.year > y.year);
            });
    }
    string GetFullName(int year) const {
        if (year >= birthday) {
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
        } else
            return "No person";
    }
    string GetFullNameWithHistory(int year) const {
        if (year >= birthday) {
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
        } else
            return "No person";
    }

   private:
    vector<NAME>
        first_names,
        last_names;
    int birthday;
};

int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}