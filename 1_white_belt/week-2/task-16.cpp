#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    map<set<string>, int> routes;
    string stop;
    int n, bus_count = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int stop_count;
        cin >> stop_count;
        set<string> route;
        for (int j = 0; j < stop_count; j++) {
            cin >> stop;
            route.insert(stop);
        }
        if (routes.count(route) == 1) {
            cout << "Already exists for " << routes[route] << endl;
        } else {
            bus_count++;
            routes[route] = bus_count;
            cout << "New bus " << bus_count << endl;
        }
    }
    return 0;
}