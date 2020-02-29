#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class ReversibleString {
   public:
    ReversibleString() {}
    ReversibleString(const string& x) {
        s = x;
    }
    void Reverse() {
        string tmp;
        for (int i = s.size() - 1; i >= 0; i--) {
            tmp += s[i];
        }
        s = tmp;
    }
    string ToString() const {
        return s;
    }

   private:
    string s;
};

/*int main() {
    ReversibleString s("live");
    s.Reverse();
    cout << s.ToString() << endl;

    s.Reverse();
    const ReversibleString& s_ref = s;
    string tmp = s_ref.ToString();
    cout << tmp << endl;

    ReversibleString empty;
    cout << '"' << empty.ToString() << '"' << endl;

    return 0;
}*/