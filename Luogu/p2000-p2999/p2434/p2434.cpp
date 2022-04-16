#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int a[N], b[N];
int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		a[x]++;
		b[y]++;
	}
	int cnt = 0;
	for(int i = 1; i < N; i++)
	{
		if(!cnt && a[i])cout << i << " ";
		cnt += a[i] - b[i];
		if(!cnt && b[i])cout << i << endl;
	}
	return 0;
}
