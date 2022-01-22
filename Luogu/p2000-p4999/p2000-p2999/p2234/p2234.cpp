#include<bits/stdc++.h>
using namespace std;
int tot = 0;
set<int>his;
set<int>::iterator it;
int n;
int main()
{
	scanf("%d", &n);
	his.insert(-10000000), his.insert(10000000);
	for(int i = 1; i <= n; i++)
	{
		int k;
		scanf("%d", &k);
		if(his.count(k))
		{
			continue;
		}
		his.insert(k);
		int minn = 2000020;
		it = his.find(k);
		it++;
		minn = min(minn, abs(*it - k));
		it--, it--;
		minn = min(minn, abs(*it - k));
		tot += (minn>2000000?k:minn);
	}
	printf("%d\n", tot);
	return 0;
}
