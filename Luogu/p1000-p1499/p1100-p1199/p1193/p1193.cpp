#include <bits/stdc++.h>
using namespace std;
int n, m, ta, tb, tc, td, A, H, E, r, pr, sr, sc;
int tea, self, trad, luogu;
int p[1001], s[1001], score[1001][1001], jud[1001][1001];
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> p[i];
	for(int i = 1; i <= m; i++) cin >> s[i];
	sort(p + 1, p + n + 1);
	sort(s + 1, s + m + 1);
	cin >> ta >> tb >> tc >> td >> A >> H >> E;
	cin >> r;
	trad = ta * n;
	for(int i = 1; i <= r; i++)
	{
		cin >> pr >> sr >> sc;
		pr = lower_bound(p + 1, p + n + 1, pr) - p;
		sr = lower_bound(s + 1, s + m + 1, sr) - s;
		if(sc > score[sr][pr] && E) trad += td, score[sr][pr] = sc;
		jud[sr][pr]++;
	}
	luogu = (n * ta + r * tc) * 100 / A + H;
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			tea = 0; self = ta;
			tea += tb * jud[i][j];
			self += tc * jud[i][j];
			trad += min(tea, self);
		}
	}
	cout << trad << endl << luogu << endl;
	if(luogu < trad) cout << "Use Luogu!\n";
	else cout << "Forget it...\n";
}
