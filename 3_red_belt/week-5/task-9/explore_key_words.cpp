#include "profile.h"
#include "test_runner.h"

#include <functional>
#include <future>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats& other) {
        for (const auto& [key, val] : other.word_frequences) {
            word_frequences[key] += val;
        }
    }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats ans;
    size_t pos1 = 0;
    while (true) {
        auto pos2 = line.find(' ', pos1);
        auto word = line.substr(pos1, pos2 - pos1);
        if (key_words.count(word)) {
            ++ans.word_frequences[word];
        }
        if (pos2 == string::npos) {
            break;
        } else {
            pos1 = pos2 + 1;
        }
    }
    return ans;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input) {
    Stats result;
    for (string line; getline(input, line);) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

// Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
//     vector<future<Stats>> threads;
//     list<stringstream> sss;
//     Stats ans;

//     const int thread_lines = 1;
//     while (input) {
//         stringstream ss;
//         bool fl = false;
//         for (int i = 0; i < thread_lines; i++) {
//             string line;
//             if (!getline(input, line)) {
//                 fl = true;
//                 break;
//             }
//             ss << move(line) << "\n";
//         }
//         sss.push_back(move(ss));
//         threads.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(sss.back())));
//         if (fl) break;
//     }
//     for (auto& f : threads) {
//         ans += f.get();
//     }
//     return ans;
// }

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<future<Stats>> threads;
    list<stringstream> sss;
    Stats ans;

    const int thread_lines = 10000;
    while (input) {
        stringstream ss;
        bool fl = false;
        for (int i = 0; i < thread_lines; i++) {
            string line;
            if (!getline(input, line)) {
                fl = true;
                break;
            }
            ss << move(line) << "\n";
        }
        sss.push_back(move(ss));
        threads.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(sss.back())));
        if (fl) break;
    }
    for (auto& f : threads) {
        ans += f.get();
    }
    return ans;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}};
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
