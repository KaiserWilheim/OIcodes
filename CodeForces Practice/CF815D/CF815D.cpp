#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010, M = N << 1;
#define lowbit(x) ((x)&-(x))
int n, m;
struct Node
{
	int b, c;
	Node(){}
	Node(int _b, int _c) { b = _b, c = _c; }
};
int p, q, r;
int smax[N];
vector<Node>d[N];
ll ans, sum[N];
int main()
{
	scanf("%d%d%d%d", &n, &p, &q, &r);
	for(int i = 1; i <= n; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a = min(a, p), b = min(b, q), c = min(c, r);
		d[a].emplace_back(b, c);
		smax[b] = max(smax[b], c);
	}
	for(int i = q - 1; i; i--)smax[i] = max(smax[i + 1], smax[i]);
	for(int i = 1; i <= q; i++)sum[i] = sum[i - 1] + smax[i];
	int max2 = 0, max3 = 0, k = q + 1;
	for(int x = p; x; x--)
	{
		for(int i = 0; i < d[x].size(); i++)
		{
			int y = d[x][i].b, z = d[x][i].c;
			max2 = max(max2, y), max3 = max(max3, z);
			while(k > max2 + 1 && smax[k - 1] < max3)k--;
		}
		k = max(k, max2 + 1);
		ans += 1ll * (r - max3) * (q - k + 1) + 1ll * r * (k - max2 - 1) - sum[k - 1] + sum[max2];
	}
	printf("%lld\n", ans);
	return 0;
}
