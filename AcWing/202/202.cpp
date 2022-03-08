#include<bits/stdc++.h>
using namespace std;
#define ll long long
int gcd(ll a, int b)
{
    return b ? gcd(b, a % b) : a;
}

ll get_euler(ll c)
{
    ll res = c;
    for(int i = 2; i <= c / i; ++i)
    {
        if(c % i == 0)
        {
            int s = 0;
            while(c % i == 0) ++s, c /= i;
            res = res / i * (i - 1);
        }
    }
    if(c > 1) res = res / c * (c - 1);
    return res;
}

ll qmul(ll a, ll b, ll c)
{
    ll res = 0;
    while(b)
    {
        if(b & 1) res = (res + a) % c;
        a = (a + a) % c;
        b >>= 1;
    }
    return res;
}

ll qmi(ll a, ll b, ll c)
{
    ll res = 1;
    while(b)
    {
        if(b & 1) res = qmul(res, a, c);
        a = qmul(a, a, c);
        b >>= 1;
    }
    return res;
}
int main()
{
    int T = 1;
    ll L;
    while(cin >> L, L)
    {
        int d = gcd(L, 8);
        ll c = 9 * L / d;
        ll phi = get_euler(c);
        ll res = 1e18;
        if(c % 2 == 0 || c % 5 == 0) res = 0;
        else
        {
            for(ll i = 1; i <= phi / i; ++i)
            {
                if(phi % i == 0)
                {
                    if(qmi(10, i, c) == 1) res = min(res, i);
                    if(qmi(10, phi / i, c) == 1) res = min(res, phi / i);
                }
            }
        }
        printf("Case %d: %lld\n", T++, res);
    }
    return 0;
}
