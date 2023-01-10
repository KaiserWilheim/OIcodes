#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = 400010;
int n;
char s[N];
void solve()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	if(s[1] == 'a' && s[n] == 'a')
	{
		putchar('a');
		putchar(' ');
		for(int i = 2; i < n; i++)
			putchar(s[i]);
		putchar(' ');
		putchar('a');
		putchar('\n');
	}
	else if(s[1] == 'b' && s[n] == 'b')
	{
		int pos = 0;
		for(int i = 2; i < n; i++)
			if(s[i] == 'a') { pos = i; break; }
		if(pos == 0)
		{
			putchar('b');
			putchar(' ');
			putchar('b');
			putchar(' ');
			for(int i = 3; i <= n; i++)
				putchar(s[i]);
			putchar('\n');
		}
		else
		{
			for(int i = 1; i < pos; i++)
				putchar(s[i]);
			putchar(' ');
			putchar('a');
			putchar(' ');
			for(int i = pos + 1; i <= n; i++)
				putchar(s[i]);
			putchar('\n');
		}
	}
	else
	{
		if(s[2] == 'a')
		{
			putchar(s[1]);
			putchar(' ');
			putchar(s[2]);
			putchar(' ');
			for(int i = 3; i <= n; i++)
				putchar(s[i]);
			putchar('\n');
		}
		else
		{
			putchar(s[1]);
			putchar(' ');
			for(int i = 2; i < n; i++)
				putchar(s[i]);
			putchar(' ');
			putchar(s[n]);
			putchar('\n');
		}
	}
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		solve();
	}
	return 0;
}
