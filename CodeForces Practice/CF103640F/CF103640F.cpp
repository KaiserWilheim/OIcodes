#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
int p[N];
bool ans[N];
int find(int x)
{
	if(x != p[x])return p[x] = find(p[x]);
	return x;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		p[i] = i;
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if(u > v)swap(u, v);
		if(v == n)continue;
		p[find(u)] = find(v);
	}
	for(int i = 1; i < n; i++)
		if(find(i) == find(n - 1))
			ans[i] = true;
	for(int i = 1; i <= n; i++)
	{
		if(ans[i])printf("B");
		else printf("A");
	}
	return 0;
}
