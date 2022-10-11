#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 500010;
struct ExprTree
{
	int ls, rs;
	int type;
	char var;
};
ExprTree tr[N << 3];
string s;
int n;
bool vis[N];
vector<char>dic;
int rt, idx = 0;
int build(int l, int r)
{
	int p = ++idx;
	if(l == r)
	{
		tr[p].type = 0;
		tr[p].var = s[l];
		if(!vis[tr[p].var])
		{
			vis[tr[p].var] = true;
			dic.push_back(tr[p].var);
			n++;
		}
		return p;
	}
	if(s[l + 1] == '~')
	{
		tr[p].type = 1;
		tr[p].ls = build(l + 2, r - 1);
		return p;
	}
	int sta = 1;
	for(int i = l + 1; i < r; i++)
	{
		if(s[i] == '(')sta++;
		else if(s[i] == ')')sta--;
		if(sta != 1)continue;
		if(s[i] == '&')
		{
			tr[p].type = 2;
			tr[p].ls = build(l + 1, i - 1);
			tr[p].rs = build(i + 1, r - 1);
			return p;
		}
		if(s[i] == '|')
		{
			tr[p].type = 3;
			tr[p].ls = build(l + 1, i - 1);
			tr[p].rs = build(i + 1, r - 1);
			return p;
		}
		if(s[i] == '^')
		{
			tr[p].type = 4;
			tr[p].ls = build(l + 1, i - 1);
			tr[p].rs = build(i + 1, r - 1);
			return p;
		}
		if(s[i] == '$')
		{
			tr[p].type = 5;
			tr[p].ls = build(l + 1, i - 1);
			tr[p].rs = build(i + 1, r - 1);
			return p;
		}
	}
	return 0;
}
#define bs bitset<1024>
bs val[200];
bs getVal(int p)
{
	if(tr[p].type == 0)
	{
		return val[tr[p].var];
	}
	else if(tr[p].type == 1)
	{
		bs res = getVal(tr[p].ls);
		return ~res;
	}
	else
	{
		bs lhs = getVal(tr[p].ls);
		bs rhs = getVal(tr[p].rs);
		if(tr[p].type == 2)return lhs & rhs;
		if(tr[p].type == 3)return lhs | rhs;
		if(tr[p].type == 4)return lhs ^ rhs;
		if(tr[p].type == 5)return ~(lhs & rhs);
	}
	return bs(0);
}
string getNull()
{
	string res = "(((v$v)$v)$((v$v)$v))";
	for(int i = 0; i < 21; i++)
		if(res[i] == 'v')res[i] = dic[0];
	return res;
}
string getEine()
{
	string res = "((v$v)$v)";
	for(int i = 0; i < 9; i++)
		if(res[i] == 'v')res[i] = dic[0];
	return res;
}
string getVar(int i, int x)
{
	string res;
	if(x)res = dic[i];
	else
	{
		res = "(v$v)";
		for(int j = 0; j < 5; j++)
			if(res[j] == 'v')res[j] = dic[i];
	}
	return res;
}
string getBlock(int S)
{
	string res = getVar(0, S & 1), prf;
	for(int i = 1; i < n; i++)
	{
		string tmp = getVar(i, (S >> i) & 1);
		prf += "((";
		res += '$' + tmp + ")$" + getEine() + ')';
	}
	return prf + res;
}
string getRes(bs ans)
{
	string res, prf;
	for(int S = 0; S < (1 << n); S++)
	{
		if(!ans[S])continue;
		if(res.empty())res = getBlock(S);
		else
		{
			string tmp = getBlock(S);
			prf += "((";
			res += '$' + getEine() + ")$(" + tmp + "$" + getEine() + "))";
		}
	}
	res = prf + res;
	if(res.empty())res = getNull();
	return res;
}
void SCP(int p)
{//shape checker program
	if(tr[p].type == 0)
	{
		putchar(tr[p].var);
		return;
	}
	putchar('(');
	if(tr[p].type == 1)
	{
		putchar('~');
		SCP(tr[p].ls);
	}
	else if(tr[p].type == 2)
	{
		SCP(tr[p].ls);
		putchar('&');
		SCP(tr[p].rs);
	}
	else if(tr[p].type == 3)
	{
		SCP(tr[p].ls);
		putchar('|');
		SCP(tr[p].rs);
	}
	else if(tr[p].type == 4)
	{
		SCP(tr[p].ls);
		putchar('^');
		SCP(tr[p].rs);
	}
	else if(tr[p].type == 5)
	{
		SCP(tr[p].ls);
		putchar('$');
		SCP(tr[p].rs);
	}
	putchar(')');
}
int main()
{
	cin >> s;
	if(s.length() == 1)
	{
		cout << s << endl;
		return 0;
	}
	rt = build(0, s.length() - 1);
	for(int S = 0; S < (1 << n); S++)
	{
		for(int i = 0; i < n; i++)
		{
			if((S >> i) & 1)
				val[dic[i]].set(S);
		}
	}
	bs outExpr = getVal(rt);
	/string res = getRes(outExpr);
	cout << res << endl;
	return 0;
}
#undef bs