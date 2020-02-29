#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;

    int k = -2;

    int i = 0;
    while (k == -2 && i <= s.length())
    {
        if (s[i] == 'f')
        {
            k = -1;
        }
        i++;
    }
    if (k == -1)
    {
        while (k == -1 && i <= s.length())
        {
            if (s[i] == 'f')
            {
                k = i;
            }
            i++;
        }
    }
    cout << k << endl;
    return 0;
}