#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int n, m;
struct Node
{
	int c[26];
	int sum;
	vector<int>t;
};
Node tr[N << 1];
int idx;
void insert(string s, int id)
{
	int p = 0;
	for(int i = 0; i < s.length(); i++)
	{
		if(tr[p].c[s[i] - 'a'] != 0)p = tr[p].c[s[i] - 'a'];
		else
		{
			tr[p].c[s[i] - 'a'] = ++idx;
			p = idx;
		}
		tr[p].sum++;
		if(tr[p].sum > tr[p].t.size())
			tr[p].t.push_back(id);
	}
}
void loschn(string s)
{
	int p = 0;
	for(int i = 0; i < s.length(); i++)
	{
		p = tr[p].c[s[i] - 'a'];
		tr[p].sum--;
	}
}
int query(string s, ll sum)
{
	int p = 0;
	for(int i = 0; i < s.length(); i++)
		p = tr[p].c[s[i] - 'a'];
	if(tr[p].t.size() <= sum)return -1;
	else return tr[p].t[sum];
}
int main()
{
	ll lans = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int op;
		ll a, b, c;
		string s;
		cin >> op >> s;
		if(op == 1)insert(s, i);
		else if(op == 2)loschn(s);
		else
		{
			cin >> a >> b >> c;
			ll sum = (a * abs(lans) + b) % c;
			lans = query(s, sum);
			cout << lans << endl;
		}
	}
	return 0;
}