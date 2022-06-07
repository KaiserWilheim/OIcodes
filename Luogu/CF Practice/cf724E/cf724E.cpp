#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 50010;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -f; c = getchar(); }
	while(isdigit(c)) x = x * 10 + c - 48, c = getchar();
	return x * f;
}
ll n, c, ans, s, res;
ll p[N], a[N];
int main()
{
    n = read(), c = read();
    for(int i = 1; i <= n; i++)
    {
        p[i] = read();
        ans += p[i];
    }
    for(int i = 1; i <= n; i++)
    {
        s = read();
        a[i] = c * (n - i) - p[i] + s;
    }
    res = ans;
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++)
        res = min(res, ans += a[i] - c * (i - 1));
    cout << res;
    return 0;
}
