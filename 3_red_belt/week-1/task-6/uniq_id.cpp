#include <string>
#include <vector>
using namespace std;

#define LINE2(line) _id##line

#define LINE1(line) LINE2(line)

#define UNIQ_ID LINE1(__LINE__)

int main() {
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}