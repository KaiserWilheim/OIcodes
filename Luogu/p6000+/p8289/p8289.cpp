#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 110;
//检查字符是否合法
bool legal(char c)
{
	if(c >= 'a' && c <= 'z')return true;
	if(c >= 'A' && c <= 'Z')return true;
	if(c >= '0' && c <= '9')return true;
	if(c == '_')return true;
	return false;
}

//存储宏
map < string, pair<string, bool> >def;
//    宏名          内容    是否正在展开

string dfs(string s)
{
	string res;
	int len = s.length();
	for(int i = 0, j; i < len; i += j)
	{
		for(j = 0; i + j < len && legal(s[i + j]); j++);
		//检索出可能的合法宏名
		if(j)
		{
			string t = s.substr(i, j);
			if(def.count(t) && !def[t].second)
			{//定义过
				def[t].second = true;
				res += dfs(def[t].first);
				//递归展开
				def[t].second = false;
			}
			else
			{
				res += t;//未定义过，忽略
			}
		}
		else
		{
			res += s[i++];//不合法，忽略
		}
	}
	return res;
}

string s[N];
int main()
{
	int n;
	cin >> n;
	for(int i = 0; i <= n; i++)getline(cin, s[i]);
	for(int i = 1; i <= n; i++)
	{
		if(s[i][0] == '#')
		{
			if(s[i][1] == 'd')
			{
				int k = s[i].find_first_of(' ', 8);
				//找到宏定义内容
				string name = s[i].substr(8, k - 8);
				string content = s[i].substr(k + 1);
				def[name] = make_pair(content, false);
			}
			else
			{
				def.erase(s[i].substr(7));
			}
			cout << endl;
		}
		else
		{
			cout << dfs(s[i]) << endl;
		}
	}
	return 0;
}
