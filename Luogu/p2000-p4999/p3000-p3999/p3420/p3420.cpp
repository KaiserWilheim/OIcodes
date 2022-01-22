#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
int n;
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)p[i] = i;
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		int pa = find(i), pb = find(x);
		if(pa != pb)p[pa] = pb;
	}
	int res = 0;
	for(int i = 1; i <= n; i++)
	{
		if(find(i) == i)res++;
	}
	cout << res << endl;
	return 0;
}
