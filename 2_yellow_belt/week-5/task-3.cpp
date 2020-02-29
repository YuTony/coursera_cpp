#include <math.h>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Figure {
   public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure {
   public:
    Triangle(const int a, const int b, const int c) : name("TRIANGLE"),
                                                      perimeter(a + b + c),
                                                      area([a, b, c] {
                                                          double p = (a + b + c) / (float)2;
                                                          return sqrt(p * (p - a) * (p - b) * (p - c));
                                                      }()) {}
    virtual string Name() const {
        return name;
    }
    virtual double Perimeter() const {
        return perimeter;
    }
    virtual double Area() const {
        return area;
    }

   private:
    const string name;
    const double perimeter, area;
};

class Rect : public Figure {
   public:
    Rect(const int a, const int b) : name("RECT"),
                                     perimeter(2 * (a + b)),
                                     area(a * b) {}
    virtual string Name() const {
        return name;
    }
    virtual double Perimeter() const {
        return perimeter;
    }
    virtual double Area() const {
        return area;
    }

   private:
    const string name;
    const double perimeter, area;
};

class Circle : public Figure {
   public:
    Circle(const int r) : name("CIRCLE"),
                          perimeter(2 * 3.14 * r),
                          area(3.14 * r * r) {}
    virtual string Name() const {
        return name;
    }
    virtual double Perimeter() const {
        return perimeter;
    }
    virtual double Area() const {
        return area;
    }

   private:
    const string name;
    const double perimeter, area;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
    string fig;
    is >> fig;
    if (fig == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else if (fig == "RECT") {
        int a, b;
        is >> a >> b;
        return make_shared<Rect>(a, b);
    } else if (fig == "CIRCLE") {
        int r;
        is >> r;
        return make_shared<Circle>(r);
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}