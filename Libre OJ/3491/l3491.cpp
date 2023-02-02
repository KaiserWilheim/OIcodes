#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
using namespace std;
const int N = 400010, M = N << 1;
const int INF = 1e9;
int n, k;
pii a[N];
int ans[N];
set<pii>s;
queue<pii>q;
int tmp;
bool chq(int x)
{
    tmp = 0;
    s.clear();
    while(!q.empty())q.pop();
    for(int i = 1; i <= n; i++)
    {
        while(!q.empty() && q.front().first + x < a[i].first)
            s.erase(make_pair(q.front().second, q.front().first)), q.pop();
        auto it = s.lower_bound(make_pair(a[i].second - x, -INF));
        while(it != s.end() && (*it).first <= x + a[i].second)
        {
            ans[++tmp] = max(abs(a[i].first - (*it).second), abs(a[i].second - (*it).first));
            ++it;
            if(tmp >= k)return true;
        }
        s.emplace(a[i].second, a[i].first);
        q.push(a[i]);
    }
    return false;
}
signed main()
{
	scanf("%lld%lld", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		int x, y;
		scanf("%lld%lld", &x, &y);
		a[i] = make_pair(x + y, x - y);
	}
    sort(a + 1, a + 1 + n);
    int l = 1, r = 4e9, res = 0;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if(chq(mid))res = mid, r = mid - 1;
        else l = mid + 1;
    }
    chq(res - 1);
    sort(ans + 1, ans + 1 + tmp);
    for(int i = 1; i <= tmp; i++)
        printf("%lld\n", ans[i]);
    for(int i = 1; i <= k - tmp; i++)
        printf("%lld\n", res);
	return 0;
}
