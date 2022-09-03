#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 400010;
int n, m;
struct Cow
{
	int h, s, w;
	Cow() {}
	bool operator < (const Cow &a)const
	{
		return s + w < a.s + a.w;
	}
};
Cow a[30];
signed main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	cin >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i].h >> a[i].w >> a[i].s;
	sort(a + 1, a + 1 + n);
	int ans = -1;
	for(int S = 1; S < (1ll << n); S++)
	{
		int h = 0, w = 0;
		int tmp = 1e15;
		bool flag = true;
		for(int i = 1; i <= n; i++)
		{
			if((S >> (i - 1)) & 1)
			{
				if(w > a[i].s)
				{
					flag = false;
					break;
				}
				tmp = min(tmp, a[i].s - w);
				h += a[i].h, w += a[i].w;
			}
		}
		if(!flag)continue;
		if(h >= m)ans = max(ans, tmp);
	}
	if(ans == -1)puts("Mark is too tall");
	else cout << ans << endl;
	return 0;
}