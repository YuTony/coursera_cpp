#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main() {
    map<string, vector<string>> buses, stops;
    // map<string, string> stops;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string com;
        cin >> com;
        if (com == "NEW_BUS") {
            int stop_count;
            string bus;
            cin >> bus >> stop_count;
            for (int j = 0; j < stop_count; j++) {
                string stop;
                cin >> stop;
                buses[bus].push_back(stop);
                stops[stop].push_back(bus);
            }
        } else if (com == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;
            if (stops.count(stop) == 0) {
                cout << "No stop" << endl;
            } else {
                for (const string& bus : stops[stop]) {
                    cout << bus << ' ';
                }
                cout << endl;
            }
        } else if (com == "STOPS_FOR_BUS") {
            string bus;
            cin >> bus;
            if (buses.count(bus) == 0) {
                cout << "No bus" << endl;
            } else {
                for (const string& stop : buses[bus]) {
                    cout << "Stop " << stop << ": ";
                    if (stops[stop].size() == 1) {
                        cout << "no interchange" << endl;
                    } else {
                        for (const string& bus2 : stops[stop]) {
                            if (bus != bus2) {
                                cout << bus2 << ' ';
                            }
                        }
                        cout << endl;
                    }
                }
            }
        } else if (com == "ALL_BUSES") {
            if (buses.size() == 0) {
                cout << "No buses" << endl;
            } else {
                for (const auto& [bus, stopsForBus] : buses) {
                    cout << "Bus " << bus << ": ";
                    for (const string& stop : stopsForBus) {
                        cout << stop << ' ';
                    }
                    cout << endl;
                }
            }
        }
    }
    return 0;
}