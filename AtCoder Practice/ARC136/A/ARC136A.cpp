#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
string s;
int main()
{
	int n;
	cin >> n;
	cin >> s;
	char t[N >> 1];
	int lent = 0;
	for(int i = 0; i < n; i++)
	{
		if(s[i] == 'A')
		{
			t[++lent] = 'B';
			t[++lent] = 'B';
		}
		else
		{
			t[++lent] = s[i];
		}
	}
	char ans[N];
	int len = 0;
	for(int i = 1; i <= lent; i++)
	{
		if(t[i] == 'B' && t[i + 1] == 'B')
		{
			ans[++len] = 'A';
			i++;
		}
		else
		{
			ans[++len] = t[i];
		}
	}
	for(int i = 1; i <= len; i++)printf("%c", ans[i]);
	putchar('\n');
	return 0;
}
