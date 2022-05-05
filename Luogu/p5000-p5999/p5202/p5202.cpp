#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 300010;
int n, k;
int hh, tt;
int f[N], q[N], sum[N];
int main()
{
	scanf("%d%d", &n, &k);
	string s;
	cin >> s;
	for(int i = 0; i < s.size(); i++)sum[i + 1] = sum[i] + (s[i] == 'G' ? -1 : 1);
	q[tt++] = 0;
	for(int i = 1; i <= n; i++)
	{
		while(hh<tt && i - q[hh]>k)hh++;
		f[i] = f[q[hh]] + (sum[i] - sum[q[hh]] <= 0);
		while(hh < tt)
		{
			if(f[i] < f[q[tt - 1]])tt--;
			else if(f[i] == f[q[tt - 1]] && sum[i] < sum[q[tt - 1]])tt--;
			else break;
		}
		q[tt++] = i;
	}
	printf("%d\n", f[n]);
	return 0;
}
