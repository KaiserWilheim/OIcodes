#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2000010;
int n;
string chart;
int op[N], a[N], tt;
bitset<65535>g, h[65535][2];
bitset<65535>base, all0, all1, ans;
int getNum(string s)
{
	int x = 0;
	for(int i = 0; i < s.length(); i++)
	{
		if(isdigit(s[i]))
			x = (x * 10) + (s[i] - 48);
	}
	return x;
}
int main()
{
	cin >> n;
	cin >> chart;
	for(int i = 0; i < chart.size(); i++)
		if(chart[i] == '1')
			g.set(i);
	string buf;
	cin >> buf;
	int f = 1;
	while(buf != "END")
	{
		if(buf == "N")f = -f;
		else if(buf == "A")op[tt] = 1;
		else if(buf == "O")op[tt] = 0;
		else if(buf[0] == 'a')a[++tt] = f * getNum(buf), f = 1;
		else a[++tt] = f * 114514 * (buf == "1" ? 1 : -1), f = 1;
		cin >> buf;
	}
	for(int S = 0; S < (1 << n); S++)
		for(int i = 0; i < n; i++)
			h[i][(S >> i) & 1].set(S);
	base.set();
	for(int i = 0; i < (1 << n); i++)
		all1.set(i);
	bitset<65535>sum = base;
	for(int i = 1; i <= tt; i++)
	{
		if(a[i] == -114514)sum &= all0;
		else if(a[i] == 114514)sum &= all1;
		else if(a[i] > 0)sum &= h[n - a[i]][1];
		else sum &= h[n + a[i]][0];
		if(!op[i])ans |= sum, sum = base;
	}
	if(ans == g)puts("YES");
	else puts("NO");
	return 0;
}