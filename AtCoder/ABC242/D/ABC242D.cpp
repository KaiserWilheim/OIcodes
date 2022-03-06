#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
int n, ans;
int to[4][3] = { {1,2},{2,0},{0,1} };
int bk[100];
string s;

int main()
{
	int T;
	cin >> s;
	scanf("%d", &T);
	while(T--)
	{
		memset(bk, 0, sizeof(bk));
		ll t, k;
		scanf("%lld%lld", &t, &k);
		k--;
		int now;
		if(t >= 63)
		{
			now = s[0] - 'A';
		}
		else
		{
			ll x = 1ll << t;
			now = s[k / x] - 'A';
			k %= x;
		}
		ll tot = 0;
		ll temp = k;
		while(temp)
		{
			bk[++tot] = temp & 1;
			temp >>= 1;
		}
		ll ed = tot + (t - tot) % 3;
		for(int i = ed; i >= 1; i--)now = to[now][bk[i]];
		printf("%c\n", now + 'A');
	}
	return 0;
}
