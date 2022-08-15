#include<bits/stdc++.h>
using namespace std;
map<int, int>dic;
map<int, int>::iterator it;
int idx = 0;
vector<int>s[200010];
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		it = dic.find(a);
		int p;
		if(it == dic.end())
		{
			dic.insert(make_pair(a, ++idx));
			p = idx;
		}
		else
		{
			p = (*it).second;
		}
		s[p].push_back(i);
	}
	while(m--)
	{
		int x, k;
		scanf("%d%d", &x, &k);
		if(dic.find(x) == dic.end())
		{
			cout << -1 << endl;
			continue;
		}
		it = dic.find(x);
		if(s[(*it).second].size() < k)
		{
			cout << -1 << endl;
			continue;
		}
		else
		{
			cout << s[(*it).second][k - 1] << endl;
		}
	}
	return 0;
}
