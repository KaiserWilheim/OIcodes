#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10010;
int n;
ll r, p, s;
bool hA()
{
	n = log(r + p + s) / log(2);
	if(r == p && abs(p - s) == 1)return true;
	if(p == s && abs(r - s) == 1)return true;
	if(r == s && abs(p - r) == 1)return true;
	return false;
}
string Min(string x, string y)
{
	return min(x + y, y + x);
}
string get(int k, char c)
{
	if(!k)
	{
		string res = "";
		res.push_back(c);
		return res;
	}
	if(c == 'P')return Min(get(k - 1, 'P'), get(k - 1, 'R'));
	else if(c == 'R')return Min(get(k - 1, 'R'), get(k - 1, 'S'));
	else return Min(get(k - 1, 'S'), get(k - 1, 'P'));
}
bool iV(string &str)
{
	int len = str.size();
	ll cr = 0, cp = 0, cs = 0;
	for(int i = 0; i < len; i++)
	{
		cr += (str[i] == 'R');
		cp += (str[i] == 'P');
		cs += (str[i] == 'S');
	}
	return (cr == r && cp == p && cs == s);
}
int main()
{
	cin >> r >> p >> s;
	if(!hA())
	{
		puts("IMPOSSIBLE");
		return 0;
	}
	string a = get(n, 'P');
	string b = get(n, 'R');
	string c = get(n, 'S');
	string ans = "Z";
	if(iV(a))ans = a;
	if(iV(b) && b < ans)ans = b;
	if(iV(c) && c < ans)ans = c;
	cout << ans << endl;
	return 0;
}