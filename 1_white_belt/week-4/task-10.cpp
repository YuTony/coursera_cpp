#include <iostream>
using namespace std;

class Rational {
   public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        if (denominator == 0) {
            throw invalid_argument("denominator = 0");
        }
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
    if (y.Numerator() == 0) {
        throw domain_error("y = 0");
    }
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

    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
