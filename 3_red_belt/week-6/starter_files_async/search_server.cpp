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

InvertedIndex::InvertedIndex(istream& document_input) {
    for (string current_document; getline(document_input, current_document);) {
        this->Add(current_document);
    }
}

void UpdateDocumentBaseAsync(istream& document_input, Synchronized<InvertedIndex>& index) {
    InvertedIndex new_index(document_input);

    // for (string current_document; getline(document_input, current_document);) {
    //     new_index.Add(move(current_document));
    // }

    swap(index.GetAccess().ref_to_value, new_index);
}

// SearchServer::SearchServer(istream& document_input) {
//     // InvertedIndex new_index;
//     // for (string current_document; getline(document_input, current_document);) {
//     //     new_index.Add(move(current_document));
//     // }
//     // swap(index.GetAccess().ref_to_value, new_index);
//     UpdateDocumentBaseAsync(document_input, index);
// }

void AddQueriesStreamAsync(istream& query_input, ostream& search_results_output, Synchronized<InvertedIndex>& index) {
    vector<size_t> docid_count, docids;
    for (string current_query; getline(query_input, current_query);) {
        {
            auto access = index.GetAccess();
            docid_count.assign(access.ref_to_value.Size(), 0);
            docids.resize(access.ref_to_value.Size());
            for (const string_view word : SplitIntoWordsView(current_query)) {
                for (const auto& rec : access.ref_to_value.Lookup(word)) {
                    docid_count[rec.docid] += rec.count;
                }
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

void SearchServer::UpdateDocumentBase(istream& document_input) {
    futures.push_back(async(UpdateDocumentBaseAsync, ref(document_input), ref(index)));
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
    futures.push_back(async(AddQueriesStreamAsync, ref(query_input), ref(search_results_output), ref(index)));
}

void InvertedIndex::Add(const string& document) {
    // docs.push_back(document);

    // const size_t docid = size++;
    // for (const auto& word : SplitIntoWords(document)) {
    //     docs.push_back(move(word));
    //     index[docs.back()][docid]++;
    // }

    const size_t docid = docs.size();
    docs.push_back(move(document));
    for (string_view& word : SplitIntoWordsView(docs.back())) {
        auto& word_info = index[word];
        if (word_info.empty() || word_info.back().docid != docid) {
            word_info.push_back({docid, 1});
        } else {
            word_info.back().count++;
        }
    }
}

const vector<Record>& InvertedIndex::Lookup(const string_view& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return blank;
    }
}
