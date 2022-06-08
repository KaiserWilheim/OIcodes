#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5010, M = 1000010;
template<typename T>
inline T read()
{
	T x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-')f = -1; c = getchar(); }
	while(isdigit(c))x = x * 10 + (c ^ 48), c = getchar();
	return x * f;
}
int n, m;
struct item
{
	int c, a, b;
	bool operator < (const item &x)const
	{
		return a == x.a ? b < x.b : a < x.a;
	}
}t[N];
struct query
{
	int m, k, s, id;
	bool operator < (const query &x)const
	{
		return m == x.m ? s < x.s : m < x.m;
	}
}q[M];
int f[M];
bool ans[M];
int main()
{
	n = read<int>();
	for(int i = 1; i <= n; i++)
	{
		t[i].c = read<int>();
		t[i].a = read<int>();
		t[i].b = read<int>();
	}
	sort(t + 1, t + 1 + n);
	m = read<int>();
	for(int i = 1; i <= m; i++)
	{
		q[i].m = read<int>();
		q[i].k = read<int>();
		q[i].s = read<int>();
		q[i].id = i;
	}
	sort(q + 1, q + 1 + m);
	int j = 1;
	f[0] = 1 << 30;
	for(int i = 1; i <= m; i++)
	{
		for(; t[j].a <= q[i].m && j <= n; j++)
		{
			for(int k = 100000; k >= t[j].c; k--)
			{
				int tmp = f[k - t[j].c] < t[j].b ? f[k - t[j].c] : t[j].b;
				f[k] = f[k] > tmp ? f[k] : tmp;
			}
		}
		if(f[q[i].k] > q[i].m + q[i].s)
			ans[q[i].id] = true;
	}
	for(int i = 1; i <= m; i++)
		puts(ans[i] ? "TAK" : "NIE");
	return 0;
}
