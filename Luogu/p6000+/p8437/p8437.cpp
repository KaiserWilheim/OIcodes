#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	string res;
	if(k == 1 || n == m)
	{
		for(int i = 1; i <= n; i++)
		{
			if(i & 1)res.push_back('l');
			else res.push_back('r');
		}
		cout << res << endl;
		return 0;
	}
	for(int i = 2; i <= m - 4; i += 2)
	{
		res.push_back('r');
		res.push_back('l');
	}
	for(int i = 0; i * 3 < (n - m + 4); i++)
	{
		res.push_back('r');
		if(i * 3 + 1 == n - m + 4)break;
		res.push_back('l');
		if(i * 3 + 2 == n - m + 4)break;
		res.push_back('l');
	}
	reverse(res.begin(), res.end());
	cout << res << endl;
	return 0;
}
