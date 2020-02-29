#include <query.h>

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
