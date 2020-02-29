#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class SortedStrings {
   public:
    void AddString(const string& s) {
        v_str.push_back(s);
        sort(v_str.begin(), v_str.end());
    }
    vector<string> GetSortedStrings() {
        return v_str;
    }

   private:
    vector<string> v_str;
};
