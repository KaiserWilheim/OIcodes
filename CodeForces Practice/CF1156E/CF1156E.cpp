#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, a[N];
int L[N], R[N];
int pos[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		pos[a[i]] = i;
		L[i] = R[i] = i;
	}
	stack<int>h;
	for(int i = 1; i <= n; i++)
	{
		while(h.size() && a[h.top()] < a[i])h.pop();
		if(h.size())L[i] = h.top() + 1;
		else L[i] = 1;
		h.push(i);
	}
	h = stack<int>();
	for(int i = n; i >= 1; i--)
	{
		while(h.size() && a[h.top()] < a[i])h.pop();
		if(h.size())R[i] = h.top() - 1;
		else R[i] = n;
		h.push(i);
	}
	ll ans = 0;
	for(int i = 1; i <= n; i++)
	{
		int ls = i - L[i], rs = R[i] - i;
		if(ls < rs)
		{
			for(int j = L[i]; j <= i; j++)
			{
				int y = a[i] - a[j];
				if(1 <= y && y <= n)
					if(i <= pos[y] && pos[y] <= R[i])
						ans++;
			}
		}
		else
		{
			for(int j = i; j <= R[i]; j++)
			{
				int y = a[i] - a[j];
				if(1 <= y && y <= n)
					if(L[i] <= pos[y] && pos[y] <= i)
						ans++;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
