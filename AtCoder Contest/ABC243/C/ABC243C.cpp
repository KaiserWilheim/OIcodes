#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
int n;
int a[N], b[N], c[N];
map<int, int> dic;
signed main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i];
        dic[b[i]] = 1e9 + 10;
    }
    for(int i = 1; i <= n; i++)
    {
        char op;
        cin >> op;
        if(op == 'R')
            dic[b[i]] = min(dic[b[i]], a[i]), c[i] = 1;
    }
    for(int i = 1; i <= n; i++)
    {
        if(!c[i])
        {
            if(dic[b[i]] <= a[i])
            {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
    return 0;
}
