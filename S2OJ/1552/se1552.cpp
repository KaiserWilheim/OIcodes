#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
#define ll long long
const int N = 100010;
int n;
double c = 1.0 * sqrt(1.25) - 0.5;
int get(int a)
{
	int b = a * c;
	if(a == ceil(b * (1 + c)) && get(b) == a)return b;
	else return ceil(a * (1 + c));
}
map<int, int>cnt;
ll res = 0;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		int b = get(a);
		int ans = i - 1;
		if(cnt.count(b))ans -= cnt[b];
		cnt[a]++;
		res += ans;
		printf("%lld\n", res);
	}
	return 0;
}