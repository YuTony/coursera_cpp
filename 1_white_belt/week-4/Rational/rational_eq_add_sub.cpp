#include <iostream>
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

Rational operator+(const Rational& x, const Rational& y) {
    return (Rational(x.Numerator() * y.Denominator() + y.Numerator() * x.Denominator(), x.Denominator() * y.Denominator()));
}

Rational operator-(const Rational& x, const Rational& y) {
    return (Rational(x.Numerator() * y.Denominator() - y.Numerator() * x.Denominator(), x.Denominator() * y.Denominator()));
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
