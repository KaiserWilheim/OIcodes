#include <bits/stdc++.h>
using namespace std;
const int N = 30010;
int m;
int p[N], d[N], s[N];
int find(int x)
{
	if(p[x] != x)
	{
		int rt = find(p[x]);
		d[x] += d[p[x]];
		p[x] = rt;
	}
	return p[x];
}
int main()
{
	scanf("%d", &m);
	for(int i = 1; i < N; i++)p[i] = i, s[i] = 1;
	while(m--)
	{
		char op[2];
		int a, b;
		scanf("%s%d%d", op, &a, &b);
		if(op[0] == 'M')
		{
			int pa = find(a), pb = find(b);
			d[pa] = s[pb];
			s[pb] += s[pa];
			p[pa] = pb;
		}
		else if(op[0] == 'C')
		{
			int pa = find(a), pb = find(b);
			if(pa != pb)cout << -1 << endl;
			else printf("%d\n", max(0, abs(d[a] - d[b]) - 1));
		}
		else
		{
			puts("Youwike AK IOI!");
		}
	}
	return 0;
}
