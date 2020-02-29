#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Learner {
   private:
    set<string> dict;

   public:
    int Learn(const vector<string>& words) {
        int old_size = dict.size();
        for (const auto& word : words) {
            dict.insert(word);
        }
        return dict.size() - old_size;
    }

    vector<string> KnownWords() {
        return {dict.begin(), dict.end()};
    }
};
