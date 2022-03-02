#include<bits/stdc++.h> 
using namespace std;
const int N = 1010;
int n;
int num[N], minv[N], col[N];
int pos = 1;
stack<int>s[2];
vector<int>g[N];

inline bool pop(int id)
{
	if((!s[id].empty()) && (s[id].top() == pos))
	{
		printf("%c ", (id ? 'd' : 'b'));
		s[id].pop();
		++pos;
		return true;
	}
	return false;
}

inline void push(int cur, int id)
{
	if(id == 1)
		while(pop(0));
	while((!s[id].empty()) && (s[id].top() < cur))
		if(!pop(id))
			pop(id ^ 1);
	if(id == 1)
		while(pop(0));
	s[id].push(cur);
	printf("%c ", (id ? 'c' : 'a'));
	return;
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	minv[n + 1] = n + 1;
	for(int i = n; i >= 1; i--)
		minv[i] = min(minv[i + 1], num[i]);
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			if((minv[j + 1] < num[i]) && (num[i] < num[j]))
			{
				g[i].push_back(j);
				g[j].push_back(i);
				col[i] = col[j] = -1;
			}
	for(int i = 1; i <= n; i++)
		if(!~col[i])
		{
			queue<int>q;
			q.push(i);
			col[i] = 0;
			while(!q.empty())
			{
				int u = q.front();
				q.pop();
				for(int v : g[u])
				{
					if((~col[v]) && (col[v] != (col[u] ^ 1)))
					{
						puts("0");
						return 0;
					}
					if(!~col[v])q.push(v);
					col[v] = col[u] ^ 1;
				}
			}
		}
	for(int i = 1; i <= n; i++)
		push(num[i], col[i]);
	bool flag = true;
	while(flag)
	{
		flag = false;
		while(pop(0))flag = true;
		while(pop(1))flag = true;
	}
	return 0;
}
