#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 2007;
ll n;
ll ans;
int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        cin >> n;
        ans = 4 * n;
        for(int i = 1; i <= n - 1; i++)
            ans *= 5, ans %= mod;
        printf("%lld\n", ans);
    }
    return 0;
}
