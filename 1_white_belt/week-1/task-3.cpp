#include <cmath>
#include <iostream>
using namespace std;

int main() {
  double a, b, c;
  cin >> a >> b >> c;
  if (a == 0) {
    if (b != 0) {
      cout << -c / b;
    }
  } else {
    int d = b * b - 4 * a * c;
    if (d > 0) {
      cout << (-b + sqrt(d)) / (2 * a) << ' ' << (-b - sqrt(d)) / (2 * a);
    } else if (d == 0) {
      cout << (-b + sqrt(d)) / (2 * a);
    }
  }
  return 0;
}