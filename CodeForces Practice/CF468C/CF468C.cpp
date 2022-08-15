#include<bits/stdc++.h>
using namespace std;
long long l, r, N = 1e18, mod;
int main()
{
    scanf("%lld", &mod);
    l = mod - N % mod * 9 % mod * 9 % mod;
    r = l + N - 1;
    printf("%lld %lld\n", l, r);
    return 0;
}
