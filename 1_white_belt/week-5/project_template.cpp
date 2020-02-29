#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
   public:
    Date() {}
    Date(int day_v, int month_v, int year_v) {
        if (month_v < 1 || month_v > 12) {
            stringstream ss;
            ss << "Month value is invalid: " << month_v;
            throw invalid_argument(ss.str());
        }
        if (day_v < 1 || day_v > 31) {
            stringstream ss;
            ss << "Day value is invalid: " << day_v;
            throw invalid_argument(ss.str());
        }
        day = day_v;
        month = month_v;
        year = year_v;
    }
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }

   private:
    int day;
    int month;
    int year;
};

ostream& operator<<(ostream& st, const Date& date) {
    st << setfill('0');
    st << setw(4) << date.GetYear() << "-"
       << setw(2) << date.GetMonth() << "-"
       << setw(2) << date.GetDay();
    return st;
}

/*int IsValid(stringstream& ss) {
    char t = ss.get();
    if (t > 47 && t < 58) {
        // return t - 48;
        ss.unget();
        return true;
    } else if (t == 43 || t == 45) {
        char t1 = ss.peek();
        if (t1 > 47 && t < 58) {
            // return t == 45 ? -(t1 - 48) : (t1 - 48);
            ss.unget();
            return true;
        } else {
            return false;
        }
    } else
        return false;
}*/

istream& operator>>(istream& st, Date& date) {
    string temp;
    st >> temp;
    stringstream ss(temp);
    int day, month, year;
    char c1, c2;
    /*char c1, c2, c3 = '\0';
    bool fl1 = true, fl2 = true;
    ss >> year >> c1;
    fl1 = IsValid(ss);
    ss >> month >> c2;
    fl2 = IsValid(ss);
    ss >> day >> c3;
    if (c1 == '-' && c2 == '-' && (c3 == '\0' || c3 == '\n') && fl1 && fl2) {
        date = {day, month, year};
    } else {
        throw invalid_argument("Wrong date format: " + temp);
    }*/
    if (ss >> year >> c1 >> month >> c2 >> day && ss.peek() == EOF) {
        date = {day, month, year};
    } else {
        throw invalid_argument("Wrong date format: " + temp);
    }
    return st;
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() < rhs.GetYear()) {
        return true;
    } else if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() < rhs.GetMonth()) {
            return true;
        } else if (lhs.GetMonth() == rhs.GetMonth()) {
            return (lhs.GetDay() < rhs.GetDay());
        } else {
            return false;
        }
    } else {
        return false;
    }
}

class Database {
   public:
    void AddEvent(const Date& date, const string& event) {
        data[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event) {
        if (data.count(date) == 1 && data[date].count(event) == 1) {
            if (data[date].size() == 1) {
                data.erase(date);
            } else {
                data[date].erase(event);
            }
            return true;
        }
        return false;
    }
    int DeleteDate(const Date& date) {
        int n = data[date].size();
        if (n != 0)
            data.erase(date);
        return n;
    }

    void Find(const Date& date, ostream& ss) const {
        if (data.count(date) != 0) {
            for (const string& v : data.at(date)) {
                ss << v << endl;
            }
        }
    }

    void Print(ostream& ss) const {
        for (auto it = data.begin(); it != data.end(); it++) {
            for (const string& v : it->second) {
                ss << it->first << " " << v << endl;
            }
        }
    }

   private:
    map<Date, set<string>> data;
};

int main() {
    Database db;
    string command;
    while (getline(cin, command)) {
        if (command.size() == 0)
            continue;
        stringstream ss(command);
        string com;
        ss >> com;
        try {
            if (com == "Add") {
                Date date;
                string event;
                ss >> date;
                if (ss >> event)
                    db.AddEvent(date, event);
            } else if (com == "Del") {
                Date date;
                string event;
                ss >> date;
                if (ss >> event) {
                    if (db.DeleteEvent(date, event)) {
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }
                } else {
                    cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
                }
            } else if (com == "Find") {
                Date date;
                ss >> date;
                db.Find(date, cout);
            } else if (com == "Print") {
                db.Print(cout);
            } else {
                cout << "Unknown command: " << com << endl;
            }
        } catch (invalid_argument& e) {
            cout << e.what() << endl;
        } catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}