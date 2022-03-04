#include<bits/stdc++.h>
#define ll long long
using namespace std;
int lim, ans;
bool flag;
int num[1011], tot[1011];
void dfs(ll dep, ll mol, ll den, ll pre)
{
	if(dep == lim + 1)
	{
		if(mol == 0)
		{
			flag = true;
			if(num[lim] < tot[lim])
			{
				for(ll i = 1; i <= lim; i++)
					tot[i] = num[i];
				ans = num[lim];
			}
		}
		return;
	}
	if((den * (lim + 1 - dep)) / mol > ans || num[dep] > ans)
		return;
	for(ll i = max(pre, den / mol); i <= den * (lim + 1 - dep) / mol; i++)
	{
		num[dep] = i;
		dfs(dep + 1, mol * i - den, den * i, i + 1);
	}
}
int main()
{
	int a, b;
	cin >> a >> b;
	for(lim = 1;; lim++)
	{
		tot[lim] = 0x3f3f3f3f;
		ans = 0x3f3f3f3f;
		dfs(1, a, b, 1);
		if(flag)break;
	}
	for(ll i = 1; i < lim; i++)
		cout << tot[i] << " ";
	cout << tot[lim] << endl;
	return 0;
}
