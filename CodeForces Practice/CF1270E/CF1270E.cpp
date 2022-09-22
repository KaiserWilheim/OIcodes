#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n;
struct Point
{
	int x, y;
	Point() {}
	Point(int _x, int _y)
	{
		x = _x, y = _y;
	}
	void rotate()
	{
		int nx = (x + y) / 2, ny = (x - y) / 2;
		x = nx, y = ny;
	}
};
Point a[N];
vector<int>w, b;
bool solve()
{
	for(int i = 1; i <= n; i++)
	{
		if((a[i].x + a[i].y) & 1)w.push_back(i);
		else b.push_back(i);
	}
	if(b.empty())
	{
		for(int i = 1; i <= n; i++)
			a[i].x++;
		b = w;
		w.clear();
	}
	if(w.empty())
	{
		for(int i = 1; i <= n; i++)
			a[i].rotate();
		return false;
	}
	return true;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &a[i].x, &a[i].y);
	}
	while(!solve())
	{
		w.clear();
		b.clear();
	}
	printf("%d\n", w.size());
	for(int i : w)
		printf("%d ", i);
	putchar('\n');
	return 0;
}