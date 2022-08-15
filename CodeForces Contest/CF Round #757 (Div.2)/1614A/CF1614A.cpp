#include<bits/stdc++.h>
using namespace std;
int t, n, l, r, k;
int f[110];
int main()
{
    cin >> t;
    for(int z = 1; z <= t; z++)
    {
        cin >> n >> l >> r >> k;
        memset(f, 0, sizeof(f));
        for(int i = 1; i <= n; i++)
        {
            cin >> f[i];
        }
        sort(f + 1, f + n + 1);
        int tot = 0, ans = 0;
        for(int i = 1; i <= n; i++)
        {
            if(f[i] >= l && f[i] <= r)
            {
                if(tot + f[i] > k)break;
                tot += f[i];
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
