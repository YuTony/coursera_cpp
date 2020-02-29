#include <vector>
using namespace std;

vector<int> Reversed(const vector<int>& v) {
    vector<int> ans(v.size());
    int j = v.size() - 1;
    for (int i : v) {
        ans[j] = i;
        j--;
    }
    return ans;
}