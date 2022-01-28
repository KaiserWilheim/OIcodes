#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
int s[N];
int sa[N], x[N], y[N], c[N], rk[N], height[N];
int u[N], d[N];
ll ans[N];
int get(int x)
{
    static unordered_map<int, int> hash;
    if (hash.count(x) == 0) hash[x] = ++ m;
    return hash[x];
}
void get_sa()
{
    for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ;
    for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
    for (int i = n; i; i -- ) sa[c[x[i]] -- ] = i;
    for (int k = 1; k <= n; k <<= 1)
    {
        int num = 0;
        for (int i = n - k + 1; i <= n; i ++ ) y[ ++ num] = i;
        for (int i = 1; i <= n; i ++ )
            if (sa[i] > k)
                y[ ++ num] = sa[i] - k;
        for (int i = 1; i <= m; i ++ ) c[i] = 0;
        for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
        for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
        for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0;
        swap(x, y);
        x[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i ++ )
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
        if (num == n) break;
        m = num;
    }
}
void get_height()
{
    for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i ++ )
    {
        if (rk[i] == 1) continue;
        if (k) k -- ;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++ ;
        height[rk[i]] = k;
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = n; i; i -- ) scanf("%d", &s[i]), s[i] = get(s[i]);
    get_sa();
    get_height();
    ll res = 0;
    for (int i = 1; i <= n; i ++ )
    {
        res += n - sa[i] + 1 - height[i];
        u[i] = i - 1, d[i] = i + 1;
    }
    d[0] = 1, u[n + 1] = n;
    for (int i = 1; i <= n; i ++ )
    {
        ans[i] = res;
        int k = rk[i], j = d[k];
        res -= n - sa[k] + 1 - height[k];
        res -= n - sa[j] + 1 - height[j];
        height[j] = min(height[j], height[k]);
        res += n - sa[j] + 1 - height[j];
        d[u[k]] = d[k], u[d[k]] = u[k];
    }
    for (int i = n; i; i -- ) printf("%lld\n", ans[i]);
    return 0;
}
