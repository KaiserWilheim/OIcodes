#include <bits/stdc++.h>
using namespace std;
int fail;
int main()
{
    int n, p;
    cin >> n >> p;
    for(int i = 1; i <= n; i++)
    {
        int m;
        cin >> m;
        if(m < p)fail++;
    }
    cout << fail;
    return 0;
}
