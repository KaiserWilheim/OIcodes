#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, k;
char a[N], b[N];
char res[N];
void solve()
{
	scanf("%s%s", a + 1, b + 1);
	scanf("%d", &k);
	n = strlen(a + 1);
	int pos = -1, cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		if(b[i] != '0')
		{
			int tmp = cnt + (a[i] >= b[i]);
			if(tmp <= k && tmp + n - i + (b[i] > a[i] && b[i] > '1') >= k)
				pos = i;
		}
		cnt += (a[i] != b[i]);
	}
	if(pos == -1)
	{
		puts("-1");
		return;
	}
	cnt = 0;
	for(int i = 1; i < pos; i++)
		cnt += (a[i] != b[i]), res[i] = b[i];
	for(int i = pos; i <= n; i++)
		res[i] = a[i];
	if(res[pos] >= b[pos])
		res[pos] = b[pos] - 1, cnt++;
	else if(res[pos] != b[pos] - 1 && cnt < k)
		res[pos] = b[pos] - 1, cnt++;
	for(int i = pos + 1; i <= n; i++)
		if(res[i] < '9' && cnt < k)
			res[i] = '9', cnt++;
	for(int i = n; i > pos; i--)
		if(a[i] == '9' && cnt < k)
			res[i] = '8', cnt++;
	while(cnt < k)
		res[pos]--, cnt++;
	for(int i = 1; i <= n; i++)
		putchar(res[i]);
	putchar('\n');
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
