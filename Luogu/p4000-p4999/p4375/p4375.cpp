#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100500;
int d[N], n;
struct node
{
	int val, pos;
	bool operator < (const node &i) const
	{
		if(val == i.val) return pos < i.pos;
		return val < i.val;
	}
}p[N];
bool cmp(node i, node j)
{
	return i.pos < j.pos;
}

inline int low(int x)
{
	return x & -x;
}
int get(int x)
{
	int tmp = 0;
	for(; x; x -= low(x)) tmp += d[x];
	return tmp;
}
void add(int x)
{
	for(; x <= n; x += low(x)) d[x]++;
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		p[i] = { x,i };
	}
	sort(p + 1, p + n + 1);
	for(int i = 1; i <= n; i++) p[i].val = i;
	sort(p + 1, p + n + 1, cmp);
	int ans = 1;
	for(int i = 1; i <= n; i++)
	{
		add(p[i].val);
		ans = max(ans, i - get(i));
	}
	printf("%d\n", ans);
	return 0;
}
