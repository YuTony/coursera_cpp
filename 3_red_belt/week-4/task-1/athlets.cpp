#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Athlets {
   public:
    Athlets() : athlete_pos(100'000 + 1, l.end()) {}
    void add(int num, int pos) {
        athlete_pos[num] = l.insert(athlete_pos[pos], num);
    }
    auto begin() const {
        return l.begin();
    }

    auto end() const {
        return l.end();
    }

   private:
    list<int> l;
    vector<list<int>::iterator> athlete_pos;
};

ostream& operator<<(ostream& os, const Athlets& a) {
    for (const int t : a) {
        os << t << " ";
    }
    return os;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Athlets a;

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int num, pos;
        cin >> num >> pos;
        a.add(num, pos);
    }
    cout << a << endl;
}