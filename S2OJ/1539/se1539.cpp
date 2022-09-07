#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int M = 700010, N = 10000010;
int n, m;
bool vis[N];
set<int>occur;
int prime[M];
int sum[N];
void seive()
{
	int lim = 1e7;
	for(int i = 2; i <= lim; i++)
	{
		if(!vis[i])
		{
			prime[++prime[0]] = i;
			occur.insert(i);
			int x = i, tot = 0;
			while(x)
			{
				tot += x % 10;
				x /= 10;
			}
			if(occur.count(tot))
			{
				sum[i]++;
			}
		}
		for(int j = 1; j <= prime[0] && i * prime[j] <= lim; j++)
		{
			vis[i * prime[j]] = true;
			if(i % prime[j] == 0)break;
		}
	}
}
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	seive();
	for(int i = 1; i <= 1e7; i++)
		sum[i] += sum[i - 1];
	int t;
	cin >> t;
	int l, r, a, b, c;
	cin >> l >> r >> a >> b >> c;
	int ans = 0;
	for(int i = 1; i <= t; i++)
	{
		ans ^= (sum[r] - sum[l - 1]);
		l = ((l ^ b) + a) % c + 1;
		r = ((r ^ b) + a) % c + 1;
		if(l > r)swap(l, r);
	}
	cout << ans << endl;
	return 0;
}