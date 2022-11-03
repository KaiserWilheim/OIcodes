#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 4000010;
int n;
char a[N], b[N];
void solve()
{
	scanf("%d", &n);
	cin >> a + 1 >> b + 1;
	bool flag = true;
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] != b[i])flag = false;
		cnt += a[i] - '0';
	}
	if(flag)
	{
		puts("0");
		return;
	}
	if(!cnt)
	{
		puts("-1");
		return;
	}
	cnt = 0;
	int cnt00 = 0, cnt01 = 0, cnt10 = 0, cnt11 = 0;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] == '0' && b[i] == '0')cnt00++;
		if(a[i] == '0' && b[i] == '1')cnt01++;
		if(a[i] == '1' && b[i] == '0')cnt10++;
		if(a[i] == '1' && b[i] == '1')cnt11++;
	}
	int ans = 1e9;
	if(cnt01 == cnt10)ans = min(ans, cnt10 + cnt01);
	if(cnt11 == cnt00 + 1)ans = min(ans, cnt00 + cnt11);
	if(ans == 1e9)puts("-1");
	else printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
