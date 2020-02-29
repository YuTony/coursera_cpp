#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

template <class elem>
vector<elem> operator*(vector<elem> &x, vector<elem> &y);

template <typename elem1, typename elem2>
pair<elem1, elem2> operator*(pair<elem1, elem2> &x, pair<elem1, elem2> &y);

template <class elem1, class elem2>
map<elem1, elem2> operator*(map<elem1, elem2> &x, map<elem1, elem2> &y);

template <class elem>
vector<elem> operator*(vector<elem> &x, vector<elem> &y) {
    int si = x.size();
    vector<elem> ans;
    for (int i = 0; i < si; i++) {
        ans.push_back(x[i] * y[i]);
    }
    return ans;
}

template <typename elem1, typename elem2>
pair<elem1, elem2> operator*(pair<elem1, elem2> &x, pair<elem1, elem2> &y) {
    return make_pair(x.first * y.first, x.second * y.second);
}

template <class elem1, class elem2>
map<elem1, elem2> operator*(map<elem1, elem2> &x, map<elem1, elem2> &y) {
    map<elem1, elem2> ans;
    for (auto &t : x) {
        ans[t.first] = x[t.first] * y[t.first];
    }
    return ans;
}

template <typename sq>
sq Sqr(sq &x) {
    return x * x;
}

int main() {
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}};
    cout << "map of pairs:" << endl;
    for (const auto &x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}