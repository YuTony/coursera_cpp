#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class Operator {
    add,
    sub,
    mul,
    div
};

struct Action {
    Operator op;
    int num;
};

istream &operator>>(istream &is, Action &act) {
    char c;
    is >> c >> act.num;
    if (c == '+') {
        act.op = Operator::add;
    } else if (c == '-') {
        act.op = Operator::sub;
    } else if (c == '*') {
        act.op = Operator::mul;
    } else if (c == '/') {
        act.op = Operator::div;
    } else {
        throw runtime_error("Error input");
    }
    return is;
}

int main() {
    int x, n;
    cin >> x >> n;
    deque<string> ans = {to_string(x)};
    bool fl = false;
    for (int i = 0; i < n; i++) {
        Action com;
        cin >> com;
        switch (com.op) {
            case Operator::add:
                ans.push_back(" + ");
                ans.push_back(to_string(com.num));
                fl = true;
                break;
            case Operator::sub:
                ans.push_back(" - ");
                ans.push_back(to_string(com.num));
                fl = true;
                break;
            case Operator::mul:
                if (fl) {
                    ans.push_front("(");
                    ans.push_back(")");
                }
                ans.push_back(" * ");
                ans.push_back(to_string(com.num));
                fl = false;
                break;
            case Operator::div:
                if (fl) {
                    ans.push_front("(");
                    ans.push_back(")");
                }
                ans.push_back(" / ");
                ans.push_back(to_string(com.num));
                fl = false;
                break;
        }
    }
    for (string &s : ans) {
        cout << s;
    }
}