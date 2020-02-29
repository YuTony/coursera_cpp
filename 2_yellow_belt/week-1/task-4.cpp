#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

// enum class Lang {
//     DE,
//     FR,
//     IT
// };

// struct Region {
//     string std_name;
//     string parent_std_name;
//     map<Lang, string> names;
//     int64_t population;
// };

bool operator<(const Region& x, const Region& y) {
    return tie(x.std_name, x.parent_std_name, x.names, x.population) <
           tie(y.std_name, y.parent_std_name, y.names, y.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
    int result = 0;
    map<Region, int> repetion_count;
    for (const Region& region : regions) {
        result = max(result, ++repetion_count[region]);
    }
    return result;
}

// int main() {
//     cout << FindMaxRepetitionCount({
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Russia",
//                  "Eurasia",
//                  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                  89},
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Russia",
//                  "Eurasia",
//                  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                  89},
//             })
//          << endl;

//     cout << FindMaxRepetitionCount({
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Russia",
//                  "Eurasia",
//                  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                  89},
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Moscow",
//                  "Toulouse",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  89},
//                 {"Moscow",
//                  "Russia",
//                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                  31},
//             })
//          << endl;

//     return 0;
// }