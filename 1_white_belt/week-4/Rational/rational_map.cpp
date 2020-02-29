#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
   public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        int t = abs(gcd(numerator, denominator));
        if (denominator < 0) {
            t = -t;
        }
        p = numerator / t;
        q = denominator / t;
    }

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

   private:
    int gcd(int x, int y) const {
        while (x) {
            y %= x;
            swap(y, x);
        }
        return y;
    }
    int p, q;
};

bool operator==(const Rational& x, const Rational& y) {
    return (x.Numerator() == y.Numerator() && x.Denominator() == y.Denominator());
}

bool operator>(const Rational& x, const Rational& y) {
    return (x.Numerator() * y.Denominator() > y.Numerator() * x.Denominator());
}

bool operator<(const Rational& x, const Rational& y) {
    return (x.Numerator() * y.Denominator() < y.Numerator() * x.Denominator());
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
