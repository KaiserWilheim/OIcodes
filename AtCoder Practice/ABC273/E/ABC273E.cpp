#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
int n;
struct Trie
{
	int fa;
	ll v;
	unordered_map<ll, int>c;
};
Trie tr[N];
int idx = 0;
unordered_map<ll, int>rt;
int main()
{
	scanf("%d", &n);
	int p = 0;
	tr[0].v = -1;
	for(int _i = 1; _i <= n; _i++)
	{
		string op;
		ll k;
		cin >> op;
		if(op == "ADD")
		{
			cin >> k;
			if(tr[p].c.count(k))p = tr[p].c[k];
			else
			{
				idx++;
				tr[idx].fa = p;
				tr[idx].v = k;
				tr[p].c.emplace(k, idx);
				p = idx;
			}
		}
		else if(op == "DELETE")
		{
			p = tr[p].fa;
		}
		else if(op == "SAVE")
		{
			cin >> k;
			rt[k] = p;
		}
		else if(op == "LOAD")
		{
			cin >> k;
			if(rt.count(k))p = rt[k];
			else p = 0;
		}
		printf("%lld ", tr[p].v);
	}
	putchar('\n');
	return 0;
}