#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const double eps = 1e-6;
int n;
struct Point
{
	double x, y;
	Point() {}
	Point(double _x, double _y) { x = _x, y = _y; }
};
Point p[N];
int b = 1;
double dis(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double iprod(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
bool cmp(Point lhs, Point rhs)
{
	double lang = -((lhs.x - p[b].x) / dis(lhs, p[b]));
	double rang = -((rhs.x - p[b].x) / dis(rhs, p[b]));
	if(lang - rang == 0)
	{
		return dis(lhs, p[b]) < dis(rhs, p[b]);
	}
	else
	{
		return lang < rang;
	}
}
int sta[N], tt;
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> p[i].x >> p[i].y;
	b = 1;
	for(int i = 2; i <= n; i++)
	{
		if(p[i].y < p[b].y)b = i;
		else if(p[i].y - p[b].y == 0 && p[i].x < p[b].x)b = i;
	}
	vector<Point>v;
	for(int i = 1; i <= n; i++)
		if(i != b)v.push_back(p[i]);
	sort(v.begin(), v.end(), cmp);
	p[1] = p[b];
	for(int i = 2; i <= n; i++)
		p[i] = v[i - 2];
	sta[1] = 1, sta[2] = 2, sta[3] = 3, tt = 3;
	for(int i = 4; i <= n; i++)
	{
		while(tt > 2 && iprod(p[sta[tt - 1]], p[sta[tt]], p[i]) <= 0)
			tt--;
		sta[++tt] = i;
	}
	double res = dis(p[sta[1]], p[sta[tt]]);
	for(int i = 2; i <= tt; i++)
		res += dis(p[sta[i]], p[sta[i - 1]]);
	printf("%.2lf\n", res);
	return 0;
}
