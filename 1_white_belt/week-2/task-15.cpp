#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    map<string, set<string>> synonyms;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string com;
        cin >> com;
        if (com == "ADD") {
            string word1, word2;
            cin >> word1 >> word2;
            synonyms[word1].insert(word2);
            synonyms[word2].insert(word1);
        } else if (com == "COUNT") {
            string word;
            cin >> word;
            cout << synonyms[word].size() << endl;
        } else if (com == "CHECK") {
            string word1, word2;
            cin >> word1 >> word2;
            cout << ((synonyms[word1].count(word2) != 0) ? "YES" : "NO") << endl;
        }
    }
    return 0;
}