#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010;
int n;
struct pupil
{
	int a, b, s;
	bool operator < (const pupil &x)const
	{
		if(s != x.s)return s < x.s;
		if(s <= 0)return a < x.a;
		return b > x.b;
	}
}p[N];
int c[N];
void solve()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> p[i].a >> p[i].b;
		if(p[i].a > p[i].b)p[i].s = 1;
		else if(p[i].a < p[i].b)p[i].s = -1;
		else p[i].s = 0;
	}
	sort(p + 1, p + 1 + n);
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		cnt += p[i].a;
		c[i] = max(c[i - 1], cnt) + p[i].b;
	}
	cout << c[n] << endl;
	return;
}
signed main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--)
	{
		memset(c, 0, sizeof(c));
		solve();
	}
	return 0;
}
