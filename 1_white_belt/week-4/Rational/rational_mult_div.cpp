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

Rational operator*(const Rational& x, const Rational& y) {
    return (Rational(x.Numerator() * y.Numerator(), x.Denominator() * y.Denominator()));
}

Rational operator/(const Rational& x, const Rational& y) {
    return (Rational(x.Numerator() * y.Denominator(), x.Denominator() * y.Numerator()));
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
