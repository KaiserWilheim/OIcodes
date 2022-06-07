#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 7010;
template <typename T>
inline T read()
{
	T x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -f; c = getchar(); }
	while(isdigit(c)) x = x * 10 + c - 48, c = getchar();
	return x * f;
}
int n;
ll a[N];
ll f[N][N];
deque<int>q;
void solve()
{
	n = read<int>();
	for(int i = 1; i <= n; i++)
		a[i] = read<ll>();
	for(int r = 2; r <= n; r++)
	{
		q.clear();
		q.push_back(r - 1);
		f[r][r - 1] = a[r - 1];
		for(int l = r - 2, k = r; l; l--)
		{
			while(f[k - 1][l] > f[r][k] && l < k)k--;
			f[r][l] = f[k][l] + a[k];
			while(q.size() && k <= q.front())q.pop_front();
			if(!q.empty())f[r][l] = min(f[r][l], f[r][q.front() + 1] + a[q.front()]);
			while(!q.empty() && f[r][q.back() + 1] + a[q.back()] >= f[r][l + 1] + a[l])q.pop_back();
			q.push_back(l);
		}
	}
	printf("%lld\n", f[n][1]);
	return;
}
int main()
{
	int T = read<int>();
	while(T--)
	{
		solve();
	}
	return 0;
}
