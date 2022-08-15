#include<bits/stdc++.h>
using namespace std;
int n;
int maxn, maxp;
map<string, int>dic;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		string s;
		int x;
		cin >> s >> x;
		if(!dic.count(s))
		{
			dic.insert({ s,x });
			if(x > maxn)
			{
				maxn = x;
				maxp = i;
			}
		}
	}
	printf("%d\n", maxp);
	return 0;
}
