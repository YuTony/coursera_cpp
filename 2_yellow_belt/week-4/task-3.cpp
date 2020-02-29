#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    auto it1 = s.begin();
    auto it2 = find(s.begin(), s.end(), ' ');
    vector<string> ans;
    while (it2 != s.end()) {
        ans.push_back({it1, it2});
        it1 = it2 + 1;
        it2 = find(it2 + 1, s.end(), ' ');
    }
    ans.push_back({it1, it2});
    return ans;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
