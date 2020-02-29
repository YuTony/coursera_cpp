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
            throw invalid_argument("Invalid argument");
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

ostream& operator<<(ostream& stream, const Rational& x) {
    stream << x.Numerator() << "/" << x.Denominator();
    return stream;
}

istream& operator>>(istream& stream, Rational& x) {
    int p, q;
    char c;
    stream >> p >> c >> q;
    if (c != '/') {
        throw invalid_argument("Invalid argument");
    }
    if (stream)
        x = Rational(p, q);
    return stream;
}

bool operator==(const Rational& x, const Rational& y) {
    return (x.Numerator() == y.Numerator() && x.Denominator() == y.Denominator());
}

Rational operator+(const Rational& x, const Rational& y) {
    return (Rational(x.Numerator() * y.Denominator() + y.Numerator() * x.Denominator(),
                     x.Denominator() * y.Denominator()));
}

Rational operator-(const Rational& x, const Rational& y) {
    return (Rational(x.Numerator() * y.Denominator() - y.Numerator() * x.Denominator(),
                     x.Denominator() * y.Denominator()));
}

Rational operator*(const Rational& x, const Rational& y) {
    return (Rational(x.Numerator() * y.Numerator(), x.Denominator() * y.Denominator()));
}

Rational operator/(const Rational& x, const Rational& y) {
    if (y.Numerator() == 0) {
        throw domain_error("Division by zero");
    }
    return (Rational(x.Numerator() * y.Denominator(), x.Denominator() * y.Numerator()));
}

int main() {
    Rational x, y;
    char com;
    try {
        cin >> x >> com >> y;
        switch (com) {
            case '+':
                cout << x + y << endl;
                break;
            case '-':
                cout << x - y << endl;
                break;
            case '*':
                cout << x * y << endl;
                break;
            case '/':
                cout << x / y << endl;
                break;

            default:
                break;
        }
    } catch (exception& e) {
        cout << e.what() << endl;
    }
}