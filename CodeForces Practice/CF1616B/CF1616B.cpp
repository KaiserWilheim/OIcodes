#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
string a;
void solve()
{
	scanf("%d", &n);
	cin >> a;
	if(a[0] == a[1])
	{
		cout << a.substr(0, 2) << endl;
		return;
	}
	int i;
	for(i = 1; i < n; i++)
		if(a[i] > a[i - 1])break;
	string ans = a.substr(0, i);
	string tmp = ans;
	reverse(tmp.begin(), tmp.end());
	cout << ans + tmp << endl;
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
