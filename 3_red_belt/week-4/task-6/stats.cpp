#include "stats.h"

using namespace std;

Stats::Stats() : methods({"GET", "POST", "PUT", "DELETE", "UNKNOWN"}),
                 uris({"/", "/order", "/product", "/basket", "/help", "unknown"}) {
    if (method_stats.size() != 5) {
        for (auto& t : methods) {
            if (method_stats.count(t) == 0)
                method_stats[t] = 0;
        }
    }
    if (uri_stats.size() == 0) {
        for (auto& t : uris) {
            uri_stats[t] = 0;
        }
    }
}

void Stats::AddMethod(string_view method) {
    auto it = methods.find(string(method.data(), method.size()));
    if (it == methods.end()) {
        method_stats[methods.find("UNKNOWN")->data()]++;
    } else {
        method_stats[it->data()]++;
    }
}

void Stats::AddUri(string_view uri) {
    auto it = uris.find(string(uri.data(), uri.size()));
    if (it == uris.end()) {
        uri_stats[uris.find("unknown")->data()]++;
    } else {
        uri_stats[it->data()]++;
    }
}

const map<string_view, int>& Stats::GetMethodStats() const {
    return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const {
    return uri_stats;
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest hr;
    size_t no_space = line.find_first_not_of(" ");
    size_t space1 = line.find(" ", no_space);
    hr.method = line.substr(no_space, space1 - no_space);
    size_t space2 = line.find(" ", space1 + 1);
    hr.uri = line.substr(space1 + 1, space2 - space1 - 1);
    hr.protocol = line.substr(space2 + 1);
    return hr;
}