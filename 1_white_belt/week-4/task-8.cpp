#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    string date;
};

int main() {
    int n;
    cin >> n;

    string s1, s2, d, m, y;
    vector<Student> students;
    for (size_t i = 0; i < n; ++i) {
        cin >> s1 >> s2 >> d >> m >> y;
        students.push_back(Student{s1 + " " + s2, d + "." + m + "." + y});
    }

    int n2;
    cin >> n2;
    string com;
    int num;

    for (int i = 0; i < n2; ++i) {
        cin >> com >> num;
        --num;
        if (com == "name" && num >= 0 && num < n) {
            cout << students[num].name << endl;
        } else if (com == "date" && num >= 0 && num < n) {
            cout << students[num].date << endl;
        } else {
            cout << "bad request" << endl;
        }
    }

    return 0;
}