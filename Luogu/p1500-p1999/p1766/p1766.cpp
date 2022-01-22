#include<bits/stdc++.h>
using namespace std;
int n;
double X,Y;
double x[3][10010];
double y[3][10010];
int main()
{
	scanf("%d%lf",&n,&X);
	Y=1000000010;
    for(int i=1;i<=n;i++)scanf("%lf%lf%lf%lf",&x[1][i],&y[1][i],&x[2][i],&y[2][i]);
	
	while(1)
	{
		int l=0;
		double k=-1000000010;
		for(int i=1;i<=n;i++)
		if(Y>min(y[1][i],y[2][i])&&min(x[1][i],x[2][i])<=X&&X<=max(x[1][i],x[2][i]))
		{
			double now=(y[1][i]-y[2][i])/(x[1][i]-x[2][i])*X+(x[1][i]*y[2][i]-x[2][i]*y[1][i])/(x[1][i]-x[2][i]);
			if(Y<=now)continue;
			if(now>k)
			{
				l=i;
				k=now;
			}
		}
		if(l==0)
		{
			printf("%.0lf\n",X);
			break;
		}
		else
		{
			if(y[1][l]<y[2][l])
			{
				X=x[1][l];
				Y=y[1][l];
			}
			else
			{
				X=x[2][l];
				Y=y[2][l];
			}
		}
	}
	return 0;
}
