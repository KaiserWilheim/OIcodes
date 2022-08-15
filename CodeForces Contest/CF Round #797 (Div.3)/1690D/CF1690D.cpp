#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 400010;
int n, m;
char s[N];
void solve()
{
	scanf("%d%d", &n, &m);
	cin >> s + 1;
	int l = 1, r = 1;
	int sum = 0, minn = m;
	while(r - l < m)sum += (s[r++] == 'B');
	minn = min(minn, m - sum);
	while(r <= n)
	{
		if(s[l++] == 'B')sum--;
		if(s[r++] == 'B')sum++;
		minn = min(minn, m - sum);
		if(minn == 0)break;
	}
	printf("%d\n", minn);
	return;
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		solve();
	}
	return 0;
}
