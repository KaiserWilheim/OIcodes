#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
long long a[N],c[N];
int main()
{
    int n;
    long long tot = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        tot += a[i];
    }
    long long avg = tot / n;
    for(int i = 1; i <= n; i++)
        c[i] = c[i - 1] + avg - a[i - 1];
    sort(c + 1, c + n + 1);
    int mid = c[(n + 1) / 2];
    long long ans = 0;
    for(int i = 1; i <= n; i++)
        ans += abs(c[i] - mid);
    printf("%lld\n", ans);
    return 0;
}
