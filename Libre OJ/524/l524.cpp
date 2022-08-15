#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
int a[100010], idx = 0;
int tmp[100010];
map<int, int>dic;
int tr[100010];
inline int lowbit(int x)
{
	return x & -x;
}
inline void add(int x, int c)
{
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += c;
}
inline int sum(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
		res += tr[i];
	return res;
}
int main()
{
	scanf("%d", &n);
	if(n == 1)
	{
		puts("L");
		return 0;
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		if(s == "X")cnt++;
		else
		{
			int f = 1;
			int res = 0;
			for(int j = 0; j < s.length(); j++)
			{
				if(s[j] == '-')f = -1;
				else res = (res * 10) + (s[j] ^ 48);
			}
			a[i] = res * f;
		}
	}
	if(cnt == 0)
	{
		int tot = 0;
		for(int i = 1; i <= n; i++)
			tmp[i] = a[i];
		sort(tmp + 1, tmp + 1 + n);
		for(int i = 1; i <= n; i++)
			dic.insert(make_pair(tmp[i], ++idx));
		for(int i = 1; i <= n; i++)
		{
			tot += i - sum(dic[a[i]]) - 1;
			add(dic[a[i]], 1);
		}
		if(tot % 2)puts("W");
		else puts("L");
		return 0;
	}
	if(cnt % 2)puts("W");
	else puts("L");
	return 0;
}
