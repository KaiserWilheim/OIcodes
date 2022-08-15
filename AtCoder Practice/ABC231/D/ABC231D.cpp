#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int p[N];
int find(int x)
{
	if(x != p[x])p[x] = find(p[x]);
	return p[x];
}
bool chq(int a, int b)
{
	int pa = find(a), pb = find(b);
	if(pa == pb)
	{
		return false;
	}
	else
	{
		p[pa] = pb;
		return true;
	}
}
int in[N];
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)p[i] = i;
	bool flag = true;
	while(m--)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		in[a]++, in[b]++;
		if(!chq(a, b))
			flag = false;
	}
	for(int i = 1; i <= n; i++)
		if(in[i] > 2)
			flag = false;
	if(flag)puts("Yes");
	else puts("No");
	return 0;
}
