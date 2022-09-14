#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
bool vis[N];
ll prime[N / 10];
map<int, int>occur;
void seive()
{
	ll lim = 1e6;
	for(ll i = 2; i <= lim; i++)
	{
		if(!vis[i])
		{
			prime[++prime[0]] = i;
			int x = i, tot = 0;
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
	ll n;
	cin >> n;
	for(int i = 1; i <= prime[0]; i++)
	{
		while(n % prime[i] == 0)
		{
			occur[i]++;
			n /= prime[i];
		}
		if(n == 1)break;
	}
	bool flag = true;
	for(auto i : occur)
	{
		if(i.second > 1)
		{
			flag = false;
			break;
		}
	}
	if(flag)puts("-1");
	else
	{
		ll res = 1;
		for(auto i : occur)
		{
			int t;
			if(i.second % 2 == 0)t = i.second / 2;
			else t = (i.second + 1) / 2;
			while(t--)res *= prime[i.first];
		}
		cout << res << endl;
	}
	return 0;
}