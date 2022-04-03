#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int fnt[N], bck[N];
int tt = 0, hh = 0;
int sum[N], maxn[N];

int main()
{
	int q;
	scanf("%d", &q);
	for(int i = 0; i < N; i++)maxn[i] = -1e9;
	while(q--)
	{
		string op;
		int k;
		cin >> op;
		if(op[0] == 'I')
		{
			cin >> k;
			fnt[++tt] = k;
			sum[tt] = sum[tt - 1] + k;
			maxn[tt] = max(maxn[tt - 1], sum[tt]);
		}
		else if(op[0] == 'D')
		{
			if(tt > 0)tt--;
		}
		else if(op[0] == 'L')
		{
			if(tt > 0)bck[++hh] = fnt[tt--];
		}
		else if(op[0] == 'R')
		{
			if(hh > 0)
			{
				fnt[++tt] = bck[hh--];
				sum[tt] = sum[tt - 1] + fnt[tt];
				maxn[tt] = max(maxn[tt - 1], sum[tt]);
			}
		}
		else if(op[0] == 'Q')
		{
			cin >> k;
			cout << maxn[k] << endl;
		}
	}
	return 0;
}
