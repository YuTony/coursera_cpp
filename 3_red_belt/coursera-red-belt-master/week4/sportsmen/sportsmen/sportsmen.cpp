#include <algorithm>
#include <functional>
#include <cmath>
#include <limits>
#include <cfloat>
#include <cstdio>
#include <iomanip>
#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

typedef int64_t I64;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef pair<int, int> pi;

#define fr(i,a,b) for (int i = a; i <= b; i++)
#define fr2(i,a,b) for (int i = a; i < b; i++)

int main() {
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;

	const int NUM_MAX = 100000;

	list<int> line;
	vector<list<int>::iterator> pointers(NUM_MAX + 1, line.end());
	fr2(i, 0, n) {
		int x, y;
		cin >> x >> y;
		auto y_pos = pointers[y];
		auto x_pos = line.insert(y_pos, x);
		pointers[x] = x_pos;
	}

	for (int x : line) {
		cout << x << ' ';
	}

	return 0;
}
