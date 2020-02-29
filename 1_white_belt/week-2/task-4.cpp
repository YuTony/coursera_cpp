#include <string>
#include <iostream>
#include <vector>
using namespace std;

void MoveStrings(vector<string>& source, vector<string>& destination) {
    for (int i = 0; i < source.size(); i++)
    {
        destination.push_back(source[i]);
    }
    source.clear();
}