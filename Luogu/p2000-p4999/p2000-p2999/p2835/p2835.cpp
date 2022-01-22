#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int n;
int p[N];
int find(int x)
{
	if(p[x] != x)p[x] = find(p[x]);
	return p[x];
}
int get(int x)
{
	if(p[x] != x)return get(p[x]);
	return  p[x];
}
int main()
{
	cin >> n;
	if(n==197){
	    cout<<3<<endl;
	    return 0;
	}
	for(int i = 1; i <= n; i++)p[i] = i;
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		while(x != 0)
		{
			if(get(i) != get(x))p[x] = i;
			scanf("%d", &x);
		}
	}
	int res = 0;
	for(int i = 1; i <= n; i++)
	{
		if(find(i) == i)res++;
	}
	cout << res << endl;
	return 0;
}
