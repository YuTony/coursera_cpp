#pragma once

#include <deque>
#include <istream>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

class InvertedIndex {
    struct Record {
        size_t count;
        size_t docid;
    };
    InvertedIndex() = default;
    explicit InvertedIndex(istream& document_input);
    const vector<Record>& Lookup(string_view word) const;

    const deque<string>& GetDocument(size_t id) const {
        return docs;
    }

   private:
    map<string_view, vector<Record>> index;
    deque<string> docs;
};

class SearchServer {
   public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input) : index(InvertedIndex(document_input)) {}
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

   private:
    InvertedIndex index;
};
