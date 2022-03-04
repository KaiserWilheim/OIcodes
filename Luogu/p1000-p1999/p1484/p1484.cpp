#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[500010];
pair<long long, int> check(int c)
{
    long long yes = a[1] - c, no = 0;
    int ycnt = 1, ncnt = 0;
    for(int i = 2; i <= n; ++i)
    {
        long long yes_g = no + a[i] - c;
        int ycnt_g = ncnt + 1;
        long long no_g = max(yes, no);
        int ncnt_g = (yes >= no ? ycnt : ncnt);
        yes = yes_g, no = no_g, ycnt = ycnt_g, ncnt = ncnt_g;
    }
    return yes >= no ? make_pair(yes, ycnt) : make_pair(no, ncnt);
}
int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }
    int l = 1, r = *max_element(a + 1, a + n + 1);
    long long ans = -1;
    while(l <= r)
    {
        int mid = (l + r) / 2;
        auto p = check(mid);
        long long u = p.first;
        int v = p.second;
        if(v >= k)
        {
            ans = u + ( long long )mid * k;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    if(ans == -1)
    {
        ans = check(0).first;
    }
    printf("%lld\n", ans);
    return 0;
}
