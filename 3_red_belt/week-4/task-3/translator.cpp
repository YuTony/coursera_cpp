#include <algorithm>
#include <deque>
#include <map>
#include <string>
#include <vector>
#include "test_runner.h"

using namespace std;

// class Translator {
//    public:
//     void Add(string_view source, string_view target) {
//         data.push_back("");
//         data.back().reserve(source.size() + target.size() + 1);
//         ((data.back() += source) += " ") += target;
//     }
//     string_view TranslateForward(string_view source) const {
//         auto predict = [&source](string_view sv) {
//             size_t space = sv.find(" ");
//             return sv.substr(0, space) == source;
//         };
//         auto it = find_if(data.rbegin(), data.rend(), predict);
//         string_view sv = "";
//         if (it != data.rend()) {
//             sv = string_view(it->data(), it->size());
//             size_t space = sv.find(" ");
//             sv.remove_prefix(space + 1);
//         }
//         return sv;
//     }
//     string_view TranslateBackward(string_view target) const {
//         auto predict = [&target](string_view sv) {
//             size_t space = sv.find(" ");
//             return sv.substr(space + 1) == target;
//         };
//         auto it = find_if(data.rbegin(), data.rend(), predict);
//         string_view sv = "";
//         if (it != data.rend()) {
//             sv = string_view(it->data(), it->size());
//             size_t space = sv.find(" ");
//             sv.remove_suffix(sv.size() - space);
//         }
//         return sv;
//     }

//    private:
//     vector<string> data;
//     map<string_view, string_view> forward_data, backward_data;
// };

class Translator {
   public:
    void Add(string_view source, string_view target) {
        string s;
        s.reserve(source.size() + target.size());
        (s += source) += target;
        data.push_back(s);
        forward_data[data.back().substr(0, source.size())] = data.back().substr(source.size());
        backward_data[data.back().substr(source.size())] = data.back().substr(0, source.size());
    }
    string_view TranslateForward(string_view source) const {
        return Translate(forward_data, source);
    }
    string_view TranslateBackward(string_view target) const {
        return Translate(backward_data, target);
    }

   private:
    static string_view Translate(const map<string_view, string_view>& dict, string_view s) {
        if (const auto it = dict.find(s); it != dict.end()) {
            return it->second;
        } else {
            return {};
        }
    }

   private:
    deque<string> data;
    map<string_view, string_view> forward_data, backward_data;
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
