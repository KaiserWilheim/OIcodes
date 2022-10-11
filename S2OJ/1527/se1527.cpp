#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
void solve()
{
	cin >> n;
	bool flag = true;
	if(n % 3 == 2)flag = false;
	if(flag)puts("Acestar");
	else puts("Blueqwq");
	return;
}
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
}