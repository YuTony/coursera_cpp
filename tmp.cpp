#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Date {
   public:
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }

    Date(string& s, bool& flag) {  //try{
        int y, m, d;
        char d1, d2;
        flag = true;
        stringstream stream(s);
        if (stream >> y >> d1 >> m >> d2 >> d && stream.peek() == EOF) {
            if (m > 12 || m < 1) {
                cout << "Month value is invalid: " << m << endl;  //continue;
                flag = false;
                // throw exception();
            } else if (d > 31 || d < 1) {
                cout << "Day value is invalid: " << d << endl;
                flag = false;
                // throw exception();
            } else {
                year = y;
                month = m;
                day = d;
            }
        } else {
            cout << "Wrong date format: " << s << endl;
            flag = false;
            // throw exception();
        }
    }

   private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() < rhs.GetYear()) {
        return true;
    } else if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() < rhs.GetMonth()) {
        return true;
    } else if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() < rhs.GetDay()) {
        return true;
    } else
        return false;
}

class Database {
   public:
    void AddEvent(const Date& date, const string& event) {
        db[date].insert(event);
    }
    void DeleteEvent(const Date& date, const string& event) {  //Почему то она исходно возвращала bool
        if (db[date].find(event) == db[date].end()) {
            cout << "Event not found" << endl;
        } else {
            db[date].erase(event);
            cout << "Deleted successfully" << endl;
        }
    }
    void DeleteDate(const Date& date) {  //Почему то она исходно возвращала инт
        cout << "Deleted " << db[date].size() << " events" << endl;
        db.erase(date);
    }

    void Find(const Date& date) const {
        try {
            for (auto i : db.at(date)) {
                cout << i << endl;
            }
        } catch (exception& out_of_range) {
        }
    }

    void Print() const {
        for (auto i : db) {
            for (auto j : i.second) {
                cout << setfill('0');
                cout << setw(4) << i.first.GetYear()
                     << "-" << setw(2) << i.first.GetMonth() << "-"
                     << setw(2) << i.first.GetDay() << " " << j << endl;
            }
        }
    }

   private:
    map<Date, set<string>> db;
};

int main() {
    Database db;
    string event, date_string;
    string command;
    string line;
    bool flag;
    while (getline(cin, line)) {
        if (!line.empty()) {
            stringstream stream(line);

            stream >> command;
            if (command == "Add") {
                stream >> date_string >> event;
                Date date(date_string, flag);
                db.AddEvent(date, event);
                // cout<< date_string<<event;
            } else if (command == "Del") {
                stream >> date_string;
                if (stream.peek() == EOF) {
                    // try{
                    Date date(date_string, flag);
                    if (flag)
                        db.DeleteDate(date);
                    // }catch(exception&   exception()){}
                } else {
                    stream >> event;
                    Date date(date_string, flag);
                    if (flag)
                        db.DeleteEvent(date, event);
                }

            } else if (command == "Find") {
                stream >> date_string;
                Date date(date_string, flag);
                if (flag)
                    db.Find(date);
            } else if (command == "Print") {
                db.Print();
            } else {
                cout << "Unknown command: " << command;
            }
        }
    }

    return 0;
}
