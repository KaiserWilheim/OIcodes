#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 500010;
map<int, bool>dic;
int kpd(int a, int b)
{
    return b ? kpd(b, a % b) : a;
}
signed main()
{
    int l, r, k;
    cin >> l >> r >> k;
    if(k == 1) cout << r - l + 1 << '\n';
    else
    {
        int ans;
        if(r - l + 1 <= 5000)
        {
            ans = 0;
            for(int i = l; i <= r; i++)
                for(int j = i; j <= r; j++)
                    if(!dic[kpd(i, j)]) ans++, dic[kpd(i, j)] = 1;
        }
        else ans = r;
        cout << ans << '\n';
    }
    return 0;
}