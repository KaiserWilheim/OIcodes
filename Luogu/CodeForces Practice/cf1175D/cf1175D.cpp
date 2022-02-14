#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
int n, k, ans, a[N], b[N];
signed main()
{
    scanf("%lld%lld", &n, &k);
    for(int i = 1; i <= n; i++)scanf("%lld", &a[i]);
    for(int i = n; i; i--)b[i] = b[i + 1] + a[i];
    b[1] += 1e15;
    sort(b + 1, b + n + 1);
    for(int i = n; i >= n - k + 1; i--)ans += b[i];
    int x = 1e15;
    printf("%lld", ans - x);
    return 0;
}
