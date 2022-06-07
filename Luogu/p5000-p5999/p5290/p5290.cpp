#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 200010;
template <typename T>
inline T read()
{
	T x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -f; c = getchar(); }
	while(isdigit(c)) x = x * 10 + c - 48, c = getchar();
	return x * f;
}
int n, a[N], f;
vector<int> e[N], t;
priority_queue<int> tr[N];
inline void merge(int x, int y)
{
	if(tr[x].size() < tr[y].size()) swap(tr[x], tr[y]);
	while(tr[y].size())
	{
		t.push_back(max(tr[x].top(), tr[y].top()));
		tr[x].pop(), tr[y].pop();
	}
	while(t.size()) tr[x].push(t.back()), t.pop_back();
}
void dfs(int x)
{
	for(int i = 0; i < e[x].size(); i++)
		dfs(e[x][i]), merge(x, e[x][i]);
	tr[x].push(a[x]);
}
int main()
{
	n = read<int>();
	for(int i = 1; i <= n; i++)
		a[i] = read<int>();
	for(int i = 2; i <= n; i++)
	{
		f = read<int>();
		e[f].push_back(i);
	}
	dfs(1);
	ll ans = 0;
	while(tr[1].size()) ans += tr[1].top(), tr[1].pop();
	cout << ans << endl;
	return 0;
}
