#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n, m;
int main()
{
	string s;
	cin >> n >> s;
	for(int i = 1; i <= s.length(); i++)
	{
		m = (m * 10 + s[i - 1] - '0') % n;
	}
	cout << (m ? m : n) << endl;
	return 0;
}
