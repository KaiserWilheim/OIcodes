#include <bits/stdc++.h>
using namespace std;
const int N = 2020;
bool vis[N];
int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= 2 * n + 1; i++)
	{
		while(vis[i] == true)i++;
		cout << i << endl;
		vis[i] = true;
		int x;
		cin >> x;
		if(x == 0)return 0;
		vis[x] = true;
	}
	return 0;
}
