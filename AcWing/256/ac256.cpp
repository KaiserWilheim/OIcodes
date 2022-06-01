#include<bits/stdc++.h>
using namespace std;
const int N = 600010, M = N * 25;
struct trie
{
	int s[2];
	int maxid;
}tr[M];
int idx;
int root[N];
int a[N];
int n, m;
void insert(int i, int k, int p, int q);
//i=index,k=length,p=previous ver.,q=present ver.;
void init();
int query(int root, int c, int lim);
int main()
{
	scanf("%d%d", &n, &m);
	init();
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		a[i] = a[i - 1] ^ x;
		root[i] = ++idx;
		insert(i, 23, root[i - 1], root[i]);
	}
	char op[2];
	int x, l, r;
	while(m--)
	{
		scanf("%s", op);
		if(*op == 'A')
		{
			scanf("%d", &x);
			n++;
			a[n] = a[n - 1] ^ x;
			root[n] = ++idx;
			insert(n, 23, root[n - 1], root[n]);
		}
		else if(*op == 'Q')
		{
			scanf("%d%d%d", &l, &r, &x);
			printf("%d\n", query(root[r - 1], a[n] ^ x, l - 1));
		}
		else
		{
			puts("Youwike AK IOI!");
		}
	}
	return 0;
}
void init()
{
	tr[0].maxid = -1;
	root[0] = ++idx;
	insert(0, 23, 0, root[0]);
	return;
}
void insert(int i, int k, int p, int q)
{
	if(k < 0)
	{
		tr[q].maxid = i;
		return;
	}
	int v = a[i] >> k & 1;
	if(p)tr[q].s[v ^ 1] = tr[p].s[v ^ 1];
	tr[q].s[v] = ++idx;
	insert(i, k - 1, tr[p].s[v], tr[q].s[v]);
	tr[q].maxid = max(tr[tr[q].s[0]].maxid, tr[tr[q].s[1]].maxid);
	return;
}
int query(int root, int c, int lim)
{
	int p = root;
	for(int i = 23; i >= 0; i--)
	{
		int v = c >> i & 1;
		if(tr[tr[p].s[v ^ 1]].maxid >= lim) p = tr[p].s[v ^ 1];
		else p = tr[p].s[v];
	}
	return c ^ a[tr[p].maxid];
}
