#include <string>
#include <iostream>
#include <vector>
using namespace std;

bool IsPalindrom(std::string s) {
    const int len = s.size();
    for (int i = 0; i < len/2; i++) {
        if (s[i] != s[len - i - 1]) {
            return false;
        }
    }
    return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength ) {
    vector<string> ans;
    for (string i : words) {
        if (IsPalindrom(i) && i.size() >= minLength) {
            ans.push_back(i);
        }
    }
    return ans;
}

int main() {
    vector<string> a =  PalindromFilter({"abacaba", "aba"}, 5);
    return 0;
}