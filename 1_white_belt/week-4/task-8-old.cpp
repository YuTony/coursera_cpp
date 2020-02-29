#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Student {
    string name;
    string fam;
    string d;
    string m;
    string y;
    Student(string val1, string val2, string t1, string t2, string t3) {
        name = val1;
        fam = val2;
        d = t1;
        m = t2;
        y = t3;
    }
};

class Students {
   public:
    void add(const Student& s) {
        list.push_back(s);
    }
    string name(int n) {
        return list[n - 1].name + " " + list[n - 1].fam;
    }
    string date(int n) {
        return list[n - 1].d + "." + list[n - 1].m + "." + list[n - 1].y;
    }

   private:
    vector<Student> list;
};

int main() {
    Students list;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s1, s2, d, m, y;
        cin >> s1 >> s2 >> d >> m >> y;
        list.add({s1, s2, d, m, y});
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string com;
        cin >> com >> n;
        if (com == "name") {
            cout << list.name(n) << endl;
        } else if (com == "date") {
            cout << list.date(n) << endl;
        } else {
            cout << "bad request" << endl;
        }
    }
}