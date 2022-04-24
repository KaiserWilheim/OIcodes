#include<bits/stdc++.h>
using namespace std;
const int N = 12500;
int a[N], b[N];
int n = 1, p, py;

int main()
{
	cin >> p;
	cin >> a[1] >> b[1];
	while(1)
	{
		int rx, ry;
		cin >> rx >> ry;
		if(rx == -1 && ry == -1)break;
		int lx = a[n], ly = b[n];
		for(int i = lx + 1; i <= rx; i++)
		{
			n++;
			a[n] = a[n - 1] + 1;
			b[n] = b[n - 1] + (ry - ly) / (rx - lx);
		}
	}
	int X;
	cin >> X;
	if(p >= a[n])
	{
		int lx = a[n], ly = b[n];
		for(int i = lx + 1; i <= p + 1; i++)
		{
			n++;
			a[n] = a[n - 1] + 1;
			b[n] = b[n - 1] - X;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(a[i] == p)
		{
			py = b[i];
			break;
		}
	}
	double minn = -1919810.0, maxn = 1919810.0;
	for(int i = 1; i <= n; i++)
	{
		if(py - b[i] > 0)
		{
			minn = max(minn, ( double )(( double )(a[i] - a[1]) * b[i] - ( double )(p - a[1]) * py) / ( double )(py - b[i]));
		}
		else
		{
			maxn = min(maxn, ( double )(( double )(a[i] - a[1]) * b[i] - ( double )(p - a[1]) * py) / ( double )(py - b[i]));
		}
	}
	if(minn > maxn) printf("NO SOLUTION\n"); 
	else
		if(minn > 0) printf("%.0lf", ceil(minn)); 
		else
			if(maxn < 0) printf("%.0lf", floor(maxn)); 
			else printf("0");
	return 0;
}
