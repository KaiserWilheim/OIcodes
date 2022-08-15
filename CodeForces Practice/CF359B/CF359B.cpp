#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n, k;
    cin >> n >> k;
    n *= 2;
    if(k == 0)
    {
        for(int i = 1; i <= n; i++)cout << i << " ";
    }
    else
    {
        cout << k + 1 << " ";
        for(int i = 1; i <= n; i++)
        {
            if(i == k + 1)continue;
            cout << i << " ";
        }
    }
    return 0;
}
