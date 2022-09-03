#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010, M = N << 2;
const double pi = 3.141592653589793238462643383279;
int n, m;
double ans = 1e18;
struct Point
{
	double x, y;
	Point() {};
	Point(double _x, double _y) { this->x = _x, this->y = _y; }
	bool operator < (const Point &a)const
	{
		return x < a.x;
	}
};
Point a[N];
double dis(Point u, Point v)
{
	return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
}
void calc()
{
	sort(a + 1, a + 1 + n);
	for(int i = 1; i < n; i++)
		for(int j = i + 1; j <= i + 5 && j <= n; j++)
			ans = min(ans, dis(a[i], a[j]));
}
void spin(double o)
{
	o = o / 180.0 * pi;
	for(int i = 1; i <= n; i++)
	{
		double x = a[i].x, y = a[i].y;
		double xn = x * cos(o) - y * sin(o);
		double yn = x * sin(o) + y * cos(o);
		a[i] = { xn,yn };
	}
}
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i].x >> a[i].y;
	calc();
	spin(rand() % 360);
	calc();
	printf("%.4lf\n", ans);
	return 0;
}