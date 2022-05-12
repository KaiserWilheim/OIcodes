#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3000010;
int n, m;
int a[N];
int qmin[N], qmax[N];
int h1, t1, h2, t2;
int main()
{
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int ans = 0, pos = 1;
	qmax[0] = qmin[0] = 1;
	for(int i = 2; i <= n; i++)
	{
		while(t1 >= h1 && a[qmin[t1]] > a[i])t1--;
		qmin[++t1] = i;
		while(t2 >= h2 && a[qmax[t2]] < a[i])t2--;
		qmax[++t2] = i;
		while(a[qmax[h2]] - a[qmin[h1]] > m)
		{
			if(qmax[h2] > qmin[h1])pos = qmin[h1] + 1, h1++;
			else pos = qmax[h2] + 1, h2++;
		}
		ans = max(ans, i - pos + 1);
	}
	printf("%d\n", ans);
	return 0;
}
