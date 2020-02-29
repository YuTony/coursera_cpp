#include "test_runner.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Translator {
public:
	void Add(string_view source, string_view target) {
		string source_str = string(source),
			   target_str = string(target);

		string_view source_sv = *(lang1_words.insert(source_str).first);
		string_view target_sv = *(lang2_words.insert(target_str).first);
		lang1_to_lang2[source_sv] = target_sv;
		lang2_to_lang1[target_sv] = source_sv;
	}

	string_view TranslateForward(string_view source) const {
		if (!lang1_to_lang2.count(source)) {
			return "";
		}

		return lang1_to_lang2.at(source);
	}

	string_view TranslateBackward(string_view target) const {
		if (!lang2_to_lang1.count(target)) {
			return "";
		}

		return lang2_to_lang1.at(target);
	}

private:
	set<string> lang1_words, lang2_words;
	map<string_view, string_view> lang1_to_lang2, lang2_to_lang1;
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
