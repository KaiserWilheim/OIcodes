#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n;
int a[N], b[N];
int cnt[N];
int ans;
void solve(int l, int r)
{
	if(l > r)return;
	if(r - l + 1 <= ans)
	{
		for(int i = l; i <= r; i++)
			cnt[a[i]]--;
		return;
	}
	if(l == r)
	{
		cnt[a[l]]--;
		if(b[1] == 1)ans = 1;
		return;
	}
	int pos = -1;
	for(int i = l; i <= r; i++)
	{
		if(cnt[a[i]] < b[r - l + 1])
		{
			pos = i;
			break;
		}
	}
	if(pos == -1)
	{
		ans = r - l + 1;
		for(int i = l; i <= r; i++)
			cnt[a[i]]--;
		return;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid)
	{
		for(int i = l; i <= pos; i++)cnt[a[i]]--;
		solve(pos + 1, r);
		for(int i = l; i < pos; i++)cnt[a[i]]++;
		solve(l, pos - 1);
	}
	else
	{
		for(int i = pos; i <= r; i++)cnt[a[i]]--;
		solve(l, pos - 1);
		for(int i = pos + 1; i <= r; i++)cnt[a[i]]++;
		solve(pos + 1, r);
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		cnt[a[i]]++;
	}
	for(int i = 1; i <= n; i++)
		scanf("%d", &b[i]);
	solve(1, n);
	printf("%d\n", ans);
	return 0;
}