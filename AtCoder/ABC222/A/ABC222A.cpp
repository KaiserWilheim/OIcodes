#include <bits/stdc++.h>
using namespace std;
int num[5];
int main()
{
    int n;
    cin >> n;
    for(int i = 1; n > 0; i++)
    {
        num[i] = n % 10;
        n /= 10;
    }
    for(int i = 4; i >= 1; i--)
    {
        cout << num[i];
    }
    return 0;
}
