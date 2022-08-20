#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
ll ans, cnt;
int a[N];
int tot[N];
char s[N];
int tmp, len;
int main()
{
	scanf("%d%d", &m, &n);
	cin >> s + 1;
	tot[0] = 1;
	for(int i = 1; i <= n; i++)
	{
		if(s[i] == '1')
		{
			tmp ^= 1; cnt++;
			if(len != i - 1)cnt += 2 * len;
			else cnt += len; len = 0;
		}
		else len++;
		tot[tmp]++;
		ans += tot[tmp ^ 1];
	}
	cnt += len;
	printf("%lld", ans - cnt);
	return 0;
}