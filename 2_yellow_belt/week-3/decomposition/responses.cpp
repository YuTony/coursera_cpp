#include "responses.h"

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