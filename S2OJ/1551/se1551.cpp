#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
#define ll long long
const int N = 100010;
int n;
int m, s;
int a[N];
void solve1()
{
	int k = sqrt(n) + 1;
	vector<int>in[400], out[400];
	for(int i = 0; i < n; i++)
	{
		if(a[i] == i)continue;
		int dis = (a[i] - i + n) % n;
		int x = dis / k, y = dis % k;
		in[k - y].push_back(a[i]);
		out[x].push_back(a[i]);
	}
	int tot = 2 * k;
	for(int i = 0; i <= k; i++)
	{
		if(!in[i].empty())tot++;
		if(!out[i].empty())tot++;
	}
	printf("%d\n", tot);
	for(int i = 0; i <= k; i++)
	{
		if(!in[i].empty())
		{
			printf("1 %d", in[i].size());
			for(auto v : in[i])
				printf(" %d", v);
			putchar('\n');
		}
		if(i != k)printf("3 1\n");
	}
	for(int i = 0; i <= k; i++)
	{
		if(!out[i].empty())
		{
			printf("2 %d", out[i].size());
			for(auto v : out[i])
				printf(" %d", v);
			putchar('\n');
		}
		if(i != k)printf("3 %d\n", k);
	}
}
void solve2()
{
	unordered_set<int>bit[20];
	vector<int>in[20], out[20];
	int top = log2(n) + 1;
	for(int i = 0; i < n; i++)
	{
		if(a[i] == i)continue;
		int dis = (a[i] - i + n) % n;
		for(int k = 0; dis != 0; k++)
		{
			if(dis & 1)bit[k].insert(a[i]);
			dis >>= 1;
		}
	}
	if(!bit[0].empty())
	{
		for(auto v : bit[0])
			in[0].push_back(v);
	}
	for(int i = 1; i <= top; i++)
	{
		if(bit[i].empty())
		{
			if(!bit[i - 1].empty())
			{
				for(auto v : bit[i - 1])
					out[i - 1].push_back(v);
			}
		}
		else
		{
			if(bit[i - 1].empty())
			{
				for(auto v : bit[i])
					in[i].push_back(v);
			}
			else
			{
				for(auto v : bit[i - 1])
				{
					if(!bit[i].count(v))
						out[i - 1].push_back(v);
				}
				for(auto v : bit[i])
				{
					if(!bit[i - 1].count(v))
						in[i].push_back(v);
				}
			}
		}
	}
	int tot = top;
	for(int i = 0; i < top; i++)
	{
		if(!in[i].empty())tot++;
		if(!out[i].empty())tot++;
	}
	printf("%d\n", tot);
	for(int i = 0; i < top; i++)
	{
		if(!in[i].empty())
		{
			printf("1 %d", in[i].size());
			for(auto v : in[i])
				printf(" %d", v);
			putchar('\n');
		}
		printf("3 %d\n", (1 << i));
		if(!out[i].empty())
		{
			printf("2 %d", out[i].size());
			for(auto v : out[i])
				printf(" %d", v);
			putchar('\n');
		}
	}
}
int main()
{
	scanf("%d", &n);
	scanf("%d%d", &m, &s);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	if(m >= 2048)solve1();
	else solve2();
	return 0;
}