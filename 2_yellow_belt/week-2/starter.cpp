#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    string com;
    is >> com;
    if (com == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int n;
        is >> n;
        q.stops.resize(n);
        for (int i = 0; i < n; i++) {
            is >> q.stops[i];
        }
    } else if (com == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (com == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (com == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    if (!r.buses.size()) {
        os << "No stop";
    } else {
        for (auto& t : r.buses) {
            os << t << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<pair<string, vector<string>>> stops;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    if (!r.stops.size()) {
        os << "No bus";
    } else {
        for (const auto& stop : r.stops) {
            os << "Stop " << stop.first << ":";
            if (stop.second.size() == 1) {
                os << " no interchange";
            } else {
                for (const string& bus1 : stop.second) {
                    if (bus1 != r.bus) {
                        os << " " << bus1;
                    }
                }
            }
            os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> data;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    if (r.data.empty()) {
        os << "No buses";
    } else {
        for (const auto& bus_and_stops : r.data) {
            os << "Bus " << bus_and_stops.first << ":";
            for (const auto& stop : bus_and_stops.second) {
                os << " " << stop;
            }
            os << endl;
        }
    }
    return os;
}

class BusManager {
   public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const string& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (stops_to_buses.count(stop) == 0)
            return BusesForStopResponse{vector<string>()};
        return BusesForStopResponse{stops_to_buses.at(stop)};
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        vector<pair<string, vector<string>>> result;

        if (buses_to_stops.count(bus) > 0) {
            for (const auto& stop : buses_to_stops.at(bus)) {
                result.push_back(make_pair(stop, stops_to_buses.at(stop)));
            }
        }
        return StopsForBusResponse{bus, result};
    }

    AllBusesResponse GetAllBuses() const {
        return AllBusesResponse{buses_to_stops};
    }

   private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
