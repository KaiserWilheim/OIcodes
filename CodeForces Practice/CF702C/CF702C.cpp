#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int tower[N], city[N];
int n, m;

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &city[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d", &tower[i]);
	sort(tower + 1, tower + 1 + m);
	sort(city + 1, city + 1 + n);
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		int k;
		k = lower_bound(tower + 1, tower + 1 + m, city[i]) - tower;
		if(k > m)ans = max(ans, abs(tower[m] - city[i]));
		else if(k == 1)ans = max(ans, abs(tower[1] - city[i]));
		else ans = max(ans, min(abs(tower[k] - city[i]), abs(tower[k - 1] - city[i])));
	}
	printf("%d\n", ans);
}
