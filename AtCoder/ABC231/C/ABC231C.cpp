#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
struct comp
{
    int v, rank;
    bool operator < (comp const &a)const
    {
        return v < a.v;
    }
};
set<comp>q;
int f[N];
int main()
{
    int n, m;
    int maxn = 0;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        cin >> f[i];
        maxn = max(maxn, f[i]);
    }
    sort(f + 1, f + n + 1);
    for(int i = 1; i <= n; i++)
    {
        comp t = { f[i],i };
        q.insert(t);
    }
    for(int i = 1; i <= m; i++)
    {
        int r;
        cin >> r;
        if(r > maxn)
        {
            cout << 0 << endl;
            continue;
        }
        comp t = { r,0 };
        cout << n - (*q.lower_bound(t)).rank + 1 << endl;
    }
    return 0;
}
