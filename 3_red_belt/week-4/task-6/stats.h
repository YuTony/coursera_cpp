#pragma once

#include "http_request.h"

#include <array>
#include <map>
#include <set>
#include <string>
#include <string_view>
using namespace std;

class Stats {
   public:
    Stats();
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int>& GetMethodStats() const;
    const map<string_view, int>& GetUriStats() const;

   private:
    map<string_view, int> method_stats, uri_stats;
    const set<string> methods, uris;
};

// class Stats {
//    public:
//     Stats() : methods_allow({"GET", "POST", "PUT", "DELETE"}),
//               uri_allow({"/", "/order", "/product", "/basket", "/help"}) {}
//     void AddMethod(string_view method) {
//         string s;
//         s += method;
//         data.push_back(s);
//         method_stats[data.back()]++;
//     }
//     void AddUri(string_view uri) {
//         string s;
//         s += uri;
//         data.push_back(s);
//         uri_stats[data.back()]++;
//     }
//     const map<string_view, int>& GetMethodStats() const {
//         return method_stats;
//     }
//     const map<string_view, int>& GetUriStats() const {
//         return uri_stats;
//     }

//    private:
//     struct Stat {
//         string field;
//         size_t num;
//     };

//    private:
//     array<Stat, 5> method_stats;
//     array<Stat, 6> uri_stats;
// };

//string_view method, uri, protocol;
HttpRequest ParseRequest(string_view line);