#include<bits/stdc++.h>
#include<random>
using namespace std;
#define ll long long
const int N = 2010;
const double dim = 0.998;
int n, m, k;
struct Point
{
	int x, y;
	int w;
};
Point obj[N];
double E(double x, double y)
{
	double res = 0;
	double dx, dy;
	for(int i = 1; i <= n; i++)
	{
		dx = x - obj[i].x;
		dy = y - obj[i].y;
		res += sqrt(dx * dx + dy * dy) * obj[i].w;
	}
	return res;
}
double ansx, ansy, ans;
mt19937 gen(19260817);
int rnd(int minn, int maxn)
{
	int lim = maxn - minn;
	int res = gen() % lim;
	return res + minn;
}
void SimAnn()
{
	double t = 114514.0;
	while(t > 1e-15)
	{
		double px = ansx + rnd(-100000, 100000) * t;
		double py = ansy + rnd(-100000, 100000) * t;
		double pans = E(px, py);
		double del = pans - ans;
		if(del < 0)
		{
			ansx = px;
			ansy = py;
			ans = pans;
		}
		else if(exp(-del / t) * 10000 > rnd(0, 10000))
		{
			ansx = px;
			ansy = py;
		}
		t *= dim;
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		obj[i] = { x,y,w };
		ansx += x;
		ansy += y;
	}
	ansx /= n;
	ansy /= n;
	ans = 1e18;
	for(int i = 1; i <= 10; i++)
		SimAnn();
	printf("%.3lf %.3lf\n", ansx, ansy);
	return 0;
}