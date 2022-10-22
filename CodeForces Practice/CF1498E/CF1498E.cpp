#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
vector<int>deg[N];
pair<int, int>a[N];
int idx;
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		deg[x].push_back(i);
	}
	for(int i = 0; i <= n; i++)
		for(auto j : deg[i])
			a[++idx] = make_pair(i, j);
	int sum = 0, maxn = -1;
	int last = 0;
	int ansu = 0, ansv = 0;
	for(int i = 1; i <= n; i++)
	{
		sum += a[i].first;
		if(sum == i * (i - 1) / 2)
		{
			if(last != i - 1)
			{
				int now = a[i].first - a[last + 1].first;
				if(now > maxn)
				{
					maxn = now;
					ansu = a[last + 1].second;
					ansv = a[i].second;
				}
			}
			last = i;
		}
	}
	cout << "! " << ansu << " " << ansv << endl;
	return 0;
}