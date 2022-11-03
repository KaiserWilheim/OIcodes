#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
int a[N];
#define pl push_back('L')
#define pr push_back('R')
void solve()
{
	string prf, suf;
	string ans1, ans2;
	cin >> n;
	n <<= 1;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	prf = suf = "";
	int pos;
	int lt, lb, rt, rb;
	bool flag1 = false, flag2 = false;
	prf.pl;
	suf.pl;
	for(int i = 2; i <= n; i++)
	{
		if(a[i] == a[1])
		{
			pos = i;
			break;
		}
	}
	lt = 2, lb = pos - 1, rt = n, rb = pos + 1;
	while(lt <= lb || rt >= rb)
	{
		if((a[lt] != a[lb] || lt >= lb) &&
			(a[lt] != a[rb] || lt >= rb) &&
			(a[rt] != a[rb] || rt <= rb) &&
			(a[rt] != a[lb] || rt <= lb))
		{
			flag1 = true;
			break;
		}
		if(a[lt] == a[lb] && lt < lb)
			lt++, lb--, prf.pl, suf.pl;
		else if(a[lt] == a[rb] && lt < rb)
			lt++, rb++, prf.pl, suf.pr;
		else if(a[rt] == a[lb] && rt > lb)
			rt--, lb--, prf.pr, suf.pl;
		else if(a[rt] == a[rb] && rt > rb)
			rt--, rb++, prf.pr, suf.pr;
	}
	reverse(suf.begin(), suf.end());
	ans1 = prf + suf;
	prf = suf = "";
	prf.pr;
	suf.pl;
	for(int i = 1; i < n; i++)
	{
		if(a[i] == a[n])
		{
			pos = i;
			break;
		}
	}
	lt = 1, lb = pos - 1, rt = n - 1, rb = pos + 1;
	while(lt <= lb || rt >= rb)
	{
		if((a[lt] != a[lb] || lt >= lb) &&
			(a[lt] != a[rb] || lt >= rb) &&
			(a[rt] != a[rb] || rt <= rb) &&
			(a[rt] != a[lb] || rt <= lb))
		{
			flag2 = true;
			break;
		}
		if(a[lt] == a[lb] && lt < lb)
			lt++, lb--, prf.pl, suf.pl;
		else if(a[lt] == a[rb] && lt < rb)
			lt++, rb++, prf.pl, suf.pr;
		else if(a[rt] == a[lb] && rt > lb)
			rt--, lb--, prf.pr, suf.pl;
		else if(a[rt] == a[rb] && rt > rb)
			rt--, rb++, prf.pr, suf.pr;
	}
	reverse(suf.begin(), suf.end());
	ans2 = prf + suf;
	if(flag1 && flag2)cout << -1 << endl;
	else if(flag1)cout << ans2 << endl;
	else cout << ans1 << endl;
}
#undef pl
#undef pr
int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin >> T;
	while(T--)
	{
		solve();
	}
	return 0;
}