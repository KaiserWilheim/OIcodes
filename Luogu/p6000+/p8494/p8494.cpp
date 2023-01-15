#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
mt19937 rnd(time(0));
void move_inside(int i);
void move_outside(int i);
int press_button();
int a[N];
bool vis[N], tvis[N];
int cnt, tot;
void ins(int i) { tot++; move_inside(i - 1); }
void del(int i) { tot--; move_outside(i - 1); }
int sum() { return press_button(); }
int min_cardinality(int n)
{
	for(int i = 1; i <= n; i++)
	{
		ins(i);
		if(sum() > 1)del(i);
		else vis[i] = true, cnt++;
	}
	if(cnt == 1)return n;
	int l = 2, r = n / cnt;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		for(int i = 1; i <= n; i++)
			tvis[i] = false, a[i] = i;
		shuffle(a + 1, a + 1 + n, rnd);
		for(int i = 1; i <= n; i++)
		{
			if(vis[a[i]])continue;
			if(cnt * mid <= tot)break;
			ins(a[i]);
			if(sum() > mid)del(a[i]);
			else tvis[a[i]] = true;
		}
		if(cnt * mid <= tot)
		{
			l = mid + 1;
			for(int i = 1; i <= n; i++)
				if(tvis[i])vis[i] = true;
		}
		else
		{
			r = tot / cnt;
			for(int i = 1; i <= n; i++)
			{
				if(tvis[i])del(i);
				else vis[i] = true;
			}
		}
	}
	return r;
}
