#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;
int n, l, r;
int a[N];
int f[N];
deque<int>q;
int ans = INT_MIN;
int main()
{
	memset(f, 128, sizeof(f));
	f[0] = 0;
	scanf("%d%d%d", &n, &l, &r);
	for(int i = 0; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = l; i <= n; i++)
	{
		while(!q.empty() && f[i - l] >= f[q.back()])q.pop_back();
		q.push_back(i - l);
		while(!q.empty() && q.front() + r < i)q.pop_front();
		f[i] = f[q.front()] + a[i];
		if(i + r > n)ans = max(ans, f[i]);
	}
	printf("%d\n", ans);
	return 0;
}