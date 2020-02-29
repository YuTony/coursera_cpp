#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ifstream input("input.txt");
    int n, m, v;
    input >> n >> m;
    if (input) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                input >> v;
                input.ignore(1);
                cout << setw(10) << v;
                if (j != m - 1)
                    cout << ' ';
            }
            if (i != n - 1)
                cout << '\n';
        }
    }
    return 0;
}