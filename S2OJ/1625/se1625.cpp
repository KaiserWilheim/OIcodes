#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
char s[N];
int cnt[N];
int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++)
		cnt[s[i] - '0']++;
	if(cnt[0] + cnt[1] == n)
	{
		puts("?????");
		return 0;
	}
	cnt[2] += 2 * cnt[4] + 3 * cnt[8];
	cnt[3] += cnt[4] + cnt[6];
	cnt[5] += cnt[6];
	cnt[7] += cnt[8];
	cnt[4] = cnt[6] = cnt[8] = 0;
	int k;
	k = min(min(cnt[2], cnt[3] / 2), cnt[7]);
	cnt[9] += k;
	cnt[2] -= k, cnt[7] -= k, cnt[3] -= 2 * k;
	k = min(cnt[7], cnt[2] / 3);
	cnt[8] += k;
	cnt[7] -= k, cnt[2] -= 3 * k;
	k = min(cnt[3], cnt[5]);
	cnt[6] += k;
	cnt[3] -= k, cnt[5] -= k;
	k = min(cnt[3], cnt[2] / 2);
	cnt[4] += k;
	cnt[3] -= k, cnt[2] -= 2 * k;
	for(int i = 9; i >= 2; i--)
		for(int j = 1; j <= cnt[i]; j++)
			printf("%d", i);
	putchar('\n');
	return 0;
}