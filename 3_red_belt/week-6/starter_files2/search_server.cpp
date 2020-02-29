#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>

vector<string> SplitIntoWords(const string& line) {
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}


void StripLeftWhitespaces(string_view& sv) {
	while (!sv.empty() && isspace(sv.front())) {
		sv.remove_prefix(1);
	}
}

string_view ReadToken(string_view& sv) {
	StripLeftWhitespaces(sv);

	auto pos = sv.find(' ');
	auto result = sv.substr(0, pos);
	sv.remove_prefix(pos != sv.npos ? pos : sv.size());
	return result;
}

vector<string_view> SplitIntoWordsView(string_view line) {
	vector<string_view> result;

	for (string_view word = ReadToken(line); !word.empty(); word = ReadToken(line)) {
		result.push_back(word);
	}

	return result;
}

// vector<string_view> SplitIntoWordsView(const string& s) {
//     string_view str = s;

//     vector<string_view> result;

//     size_t pos = 0;
//     const size_t pos_end = str.npos;

//     while (true) {
//         size_t space = str.find(' ', pos);
//         result.push_back(
//             space == pos_end
//                 ? str.substr(pos)
//                 : str.substr(pos, space - pos));

//         if (space == str.npos) {
//             break;
//         } else {
//             pos = space + 1;
//         }
//     }
//     return result;
// }

SearchServer::SearchServer(istream& document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document);) {
        new_index.Add(move(current_document));
    }

    index = move(new_index);
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
    vector<size_t> docid_count(index.Size()), docids(index.Size());
    for (string current_query; getline(query_input, current_query);) {
        docid_count.assign(docid_count.size(), 0);
        for (const string_view word : SplitIntoWordsView(current_query)) {
            for (const auto& rec : index.Lookup(word)) {
                docid_count[rec.first] += rec.second;
            }
        }

        iota(docids.begin(), docids.end(), 0);
        partial_sort(
            docids.begin(),
            Head(docids, 5).end(),
            docids.end(),
            [&docid_count](int64_t lhs, int64_t rhs) {
                return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
            });

        // vector<pair<size_t, size_t>> search_results(docid_count.begin(), docid_count.end());
        // sort(
        //     begin(search_results),
        //     end(search_results),
        //     [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
        //         int64_t lhs_docid = lhs.first;
        //         auto lhs_hit_count = lhs.second;
        //         int64_t rhs_docid = rhs.first;
        //         auto rhs_hit_count = rhs.second;
        //         return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
        //     });

        search_results_output << current_query << ':';
        for (auto docid : Head(docids, 5)) {
            size_t hitcount = docid_count[docid];
            if (hitcount == 0) break;
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << endl;
    }
}

void InvertedIndex::Add(const string& document) {
    // docs.push_back(document);

    // const size_t docid = size++;
    // for (const auto& word : SplitIntoWords(document)) {
    //     docs.push_back(move(word));
    //     index[docs.back()][docid]++;
    // }

    docs.push_back(move(document));
    for (string_view& word : SplitIntoWordsView(docs.back())) {
        index[word][docs.size() - 1]++;
    }
}

const unordered_map<size_t, size_t>& InvertedIndex::Lookup(const string_view& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return blank;
    }
}
