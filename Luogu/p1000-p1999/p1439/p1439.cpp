#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
int a[N], b[N];
int f[N];
int dic[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		dic[a[i]] = i;
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
		f[i] = 0x3f3f3f3f;
	}
	int len = 0;
	f[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		int l = 0, r = len, mid;
		if(dic[b[i]] > f[len])f[++len] = dic[b[i]];
		else
		{
			while(l < r)
			{
				mid = (l + r) / 2;
				if(f[mid] > dic[b[i]])r = mid;
				else l = mid + 1;
			}
			f[l] = min(dic[b[i]], f[l]);
		}
	}
	printf("%d\n", len);
	return 0;
}
