#include<bits/stdc++.h>
#include<random>
using namespace std;
#define ll long long
const int N = 20;
const double dim = 0.99995;
int n, m, k;
struct Point
{
	double x[N];
	Point() { for(int i = 1; i <= 10; i++)x[i] = 0; }
};
Point obj[N];
Point E(Point x)
{
	Point f;
	double pdis = 0, res = 0;
	double dx, dis[N];
	for(int i = 1; i <= n + 1; i++)
	{
		dis[i] = 0;
		for(int j = 1; j <= n; j++)
		{
			dx = x.x[j] - obj[i].x[j];
			dis[i] += dx * dx;
		}
		dis[i] = sqrt(dis[i]);
		pdis += dis[i];
	}
	pdis /= (n + 1);
	for(int i = 1; i <= n + 1; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			dx = x.x[j] - obj[i].x[j];
			double tmp = (dis[i] - pdis) * dx;
			f.x[j] += tmp;
		}
	}
	return f;
}
mt19937 gen(19260817);
int rnd(int minn, int maxn)
{
	int lim = maxn - minn;
	int res = gen() % lim;
	return res + minn;
}
Point ans;
void SimAnn()
{
	double t = 1000;
	while(t > 1e-5)
	{
		Point f = E(ans);
		for(int i = 1; i <= n; i++)
			ans.x[i] -= f.x[i] * t;
		t *= dim;
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n + 1; i++)
	{
		for(int j = 1; j <= n; j++)
			cin >> obj[i].x[j];
	}
	for(int i = 1; i <= n; i++)
		ans.x[i] = rnd(-20000, 20000);
	Point f = E(ans);
	SimAnn();
	for(int i = 1; i <= n; i++)
		printf("%.3lf ", ans.x[i]);
	putchar('\n');
	return 0;
}