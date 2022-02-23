#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1010;
int ans[N];
string a, b;
int main()
{
	cin >> a >> b;
	for(int i = 1; i <= a.length(); i++)ans[i] += a[a.length() - i] - '0';
	for(int i = 1; i <= b.length(); i++)ans[i] += b[b.length() - i] - '0';
	ans[0] = max(a.length(), b.length());
	for(int i = 1; i <= ans[0]; i++)
	{
		if(ans[i] > 9)
		{
			ans[i + 1]++;
			ans[i] -= 10;
			if(ans[ans[0] + 1] > 0)ans[0]++;
		}
	}
	for(int i = ans[0]; i >= 1; i--)cout << ans[i];
	putchar('\n');
	return 0;
}
