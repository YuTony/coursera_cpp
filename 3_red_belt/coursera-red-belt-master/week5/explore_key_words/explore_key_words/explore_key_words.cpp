#include "test_runner.h"
#include "profile.h"

#include <functional>
#include <future>
#include <map>
#include <set>
#include <string>
#include <iterator>
using namespace std;

struct Stats {
	map<string, int> word_frequences;

	void operator += (const Stats& other) {
		for (auto& [word, count] : other.word_frequences) {
			word_frequences[word] += count;
		}
	}
};

vector<string> Split(const string& line) {
	istringstream is(line);
	return { istream_iterator<string>(is), istream_iterator<string>() };
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats result;
	for (const string& word : Split(line)) {
		if (key_words.count(word)) {
			++result.word_frequences[word];
		}
	}
	return result;
}

Stats ExploreKeyWordsSingleThread(
	const set<string>& key_words, vector<string> page
) {
	Stats result;
	for (const string& line : page) {
		result += ExploreLine(key_words, line);
	}
	return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	const size_t page_size = 1000;
	vector<string> lines;
	lines.reserve(page_size);
	vector<future<Stats>> futures;
	for (string line; getline(input, line); ) {
		lines.push_back(move(line));
		if (lines.size() >= page_size) {
			futures.push_back(
				async(ExploreKeyWordsSingleThread, ref(key_words), move(lines))
			);
			lines.reserve(page_size);
		}
	}

	if (!lines.empty()) {
		futures.push_back(
			async(ExploreKeyWordsSingleThread, ref(key_words), move(lines))
		);
	}

	Stats result;
	for (auto& future : futures) {
		result += future.get();
	}
	return result;
}

void TestBasic() {
	const set<string> key_words = { "yangle", "rocks", "sucks", "all" };

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
	  {"sucks", 1}
	};
	ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
}
