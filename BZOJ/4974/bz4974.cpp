#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010, M = 400010;
int n;
int ne[N];
bool flag[26];
char s[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &ne[i]);
		ne[i] = i - ne[i];
	}
	ne[0] = -1;
	for(int i = 1; i <= n; i++)
	{
		int j = ne[i - 1];
		memset(flag, 0, sizeof(flag));
		while(~j && j + 1 != ne[i])flag[s[j + 1] - 'a'] = true, j = ne[j];
		if(j == -1)
		{
			for(int k = 0; k < 26; k++)
				if(!flag[k]) { s[i] = 'a' + k; break; }
		}
		else s[i] = s[j + 1];
	}
	printf("%s\n", s + 1);
	return 0;
}
