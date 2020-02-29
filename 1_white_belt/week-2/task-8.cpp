#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector<vector<string>> month(31);
    vector<int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int m = 0;

    int n;
    cin >> n;
    int k;
    string com;
    for (int i = 0; i < n; i++) {
        cin >> com;
        if (com == "ADD") {
            string s;
            cin >> k >> s;
            k--;
            month[k].push_back(s);
        } else if (com == "NEXT") {
            // int next = (m != 11) ? m + 1 : 0;
            // int difference = days[next] - days[m];
            if (m == 11) {
                m = 0;
            } else {
                int difference = days[m + 1] - days[m];
                if (difference >= 0) {
                    month.resize(days[m + 1]);
                } else {
                    for (int j = days[m] + difference; j < days[m]; j++) {
                        month[days[m + 1] - 1].insert(month[days[m + 1] - 1].end(), month[j].begin(), month[j].end());
                    }
                    month.resize(days[m + 1]);
                }
                m++;
            }
        } else if (com == "DUMP") {
            cin >> k;
            k--;
            cout << month[k].size() << ' ';
            for (int j = 0; j < month[k].size(); j++) {
                cout << month[k][j] << ' ';
            }
            cout << endl;
        }
    }
}