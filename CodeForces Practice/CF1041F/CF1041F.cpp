#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, m;
int a[N], b[N];
map<int, int>dic;
int ans = 0;
void chq(int x)
{
	dic.clear();
	for(int i = 1; i <= n; i++)dic[a[i] % (2 * x)]++;
	for(int i = 1; i <= m; i++)dic[(b[i] + x) % (2 * x)]++;
	for(auto i : dic)ans = max(ans, i.second);
}
int main()
{
	int qwq;
	scanf("%d%d", &n, &qwq);
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	scanf("%d%d", &m, &qwq);
	for(int i = 1; i <= m; i++)scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++)dic[a[i]]++;
	for(int i = 1; i <= m; i++)dic[b[i]]++;
	for(auto i : dic)
		ans = max(ans, i.second);
	for(int i = 0; i <= 29; i++)
		chq(1 << i);
	printf("%d\n", ans);
	return 0;
}
