#pragma once

#include <deque>
#include <istream>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
using namespace std;

class InvertedIndex {
    // struct Record {
    //     size_t docid;
    //     size_t count;
    // };
   public:
    void Add(const string& document);
    const unordered_map<size_t, size_t>& Lookup(const string_view& word) const;
    size_t Size() const {
        return docs.size();
    }

    // const string& GetDocument(size_t id) const {
    //     return docs[id];
    // }

   private:
    deque<string> docs;
    map<string_view, unordered_map<size_t, size_t>> index;
    size_t size = 0;
    // vector<size_t> blank_vector;
    unordered_map<size_t, size_t> blank;
    // vector<string> docs;
};

class SearchServer {
   public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

   private:
    InvertedIndex index;
};
