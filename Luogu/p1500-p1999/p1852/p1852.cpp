#include<bits/stdc++.h>
using namespace std;
#define ll long long
int ori[3], goal[3], tem[3];
int get(int a, int b, int c)
{
	int d1 = b - a, d2 = c - b, cnt = 0;
	if(d1 > d2)
	{
		cnt = d1 / d2;
		int d = d1 % d2;
		if(!d)
		{
			d += d2;
			cnt--;
		}
		cnt += get(a, a + d, a + d + d2);
	}
	else if(d1 < d2)
	{
		cnt = d2 / d1;
		int d = d2 % d1;
		if(!d)
		{
			d += d1;
			cnt--;
		}
		cnt += get(c - d - d1, c - d, c);
	}
	else
		tem[0] = a, tem[1] = b, tem[2] = c;
	return cnt;
}//不断缩小范围至最简形式
void up(int a, int b, int c, int step)
{
	if(!step)
	{
		tem[0] = a, tem[1] = b, tem[2] = c;
		return;
	}
	int d1 = b - a, d2 = c - b, cnt = 0;
	if(d1 > d2)
	{
		cnt = d1 / d2;
		int d = d1 % d2;
		if(!d)
		{
			d += d2;
			cnt--;
		}
		if(step >= cnt)
			up(a, a + d, a + d + d2, step - cnt);
		else
		{
			int k = cnt - step;
			up(a, a + d + k * d2, a + d + (k + 1) * d2, 0);
		}
	}
	else if(d1 < d2)
	{
		cnt = d2 / d1;
		int d = d2 % d1;
		if(!d)
		{
			d += d1;
			cnt--;
		}
		if(step >= cnt)
			up(c - d - d1, c - d, c, step - cnt);
		else
		{
			int k = cnt - step;
			up(c - d - (k + 1) * d1, c - d - k * d1, c, 0);
		}
	}
	else
		tem[0] = a, tem[1] = b, tem[2] = c;
}
bool chq(int step)
{
	int to[3];
	up(goal[0], goal[1], goal[2], step);
	to[0] = tem[0], to[1] = tem[1], to[2] = tem[2];
	up(ori[0], ori[1], ori[2], step);
	if((to[0] != tem[0]) || (to[1] != tem[1]) || (to[2] != tem[2]))return false;
	return true;
}
int main()
{
	int to[3], ans = 0;
	scanf("%d%d%d%d%d%d", &ori[0], &ori[1], &ori[2], &goal[0], &goal[1], &goal[2]);
	sort(ori, ori + 3);
	sort(goal, goal + 3);
	int step1 = get(ori[0], ori[1], ori[2]);
	to[0] = tem[0], to[1] = tem[1], to[2] = tem[2];
	int step2 = get(goal[0], goal[1], goal[2]);
	if((to[0] != tem[0]) || (to[1] != tem[1]) || (to[2] != tem[2]))
	{
		puts("NO");
		return 0;
	}
	if(step1 < step2)
	{
		ans += step2 - step1;
		up(goal[0], goal[1], goal[2], step2 - step1);
		goal[0] = tem[0], goal[1] = tem[1], goal[2] = tem[2];
	}
	else if(step1 > step2)
	{
		ans += step1 - step2;
		up(ori[0], ori[1], ori[2], step1 - step2);
		ori[0] = tem[0], ori[1] = tem[1], ori[2] = tem[2];
	}
	int l = 0, r = min(step1, step2);
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(chq(mid))r = mid;
		else l = mid + 1;
	}
	printf("YES\n%d\n", (l << 1) + ans);
	return 0;
}
