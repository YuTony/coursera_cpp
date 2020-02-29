#pragma once

#include "synchronized.h"

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

struct Record {
    size_t docid;
    size_t count;
};
class InvertedIndex {
   public:
    InvertedIndex() = default;
    explicit InvertedIndex(istream& document_input);
    void Add(const string& document);
    const vector<Record>& Lookup(const string_view& word) const;
    size_t Size() const {
        return docs.size();
    }

    // const string& GetDocument(size_t id) const {
    //     return docs[id];
    // }

   private:
    deque<string> docs;
    map<string_view, vector<Record>> index;
    size_t size = 0;
    // vector<size_t> blank_vector;
    vector<Record> blank;
    // vector<string> docs;
};

class SearchServer {
   public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input) : index(InvertedIndex(document_input)) {}
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

   private:
    // void UpdateDocumentBaseAsync(istream& document_input);
    // void AddQueriesStreamAsync(istream& query_input, ostream& search_results_output);
    Synchronized<InvertedIndex> index;
    vector<future<void>> futures;
};
