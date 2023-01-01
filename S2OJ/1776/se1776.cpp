#include<bits/stdc++.h>
using namespace std;
#define ll __int128
#define ull unsigned long long
const int N = 3e7 + 10;
int n, A, B, C, u[N], v[N], w[N];
ull Rand(ull &k1, ull &k2)
{
	ull k3 = k1, k4 = k2;
	k1 = k4;
	k3 ^= (k3 << 23);
	k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
	return k2 + k4;
}
void GetData()
{
	ull x, y;
	std::cin >> n >> A >> B >> C >> x >> y;
	for(int i = 1; i <= n; i++)
	{
		u[i] = Rand(x, y) % A + 1;
		v[i] = Rand(x, y) % B + 1;
		w[i] = Rand(x, y) % C + 1;

		if(Rand(x, y) % 3 == 0) u[i] = A;
		if(Rand(x, y) % 3 == 0) v[i] = B;
		if((u[i] != A) && (v[i] != B)) w[i] = C;
	}
}
void write(ll x)
{
	if(x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
int maxn[N];
ll ans;
int main()
{
	GetData();
	int t = 0;
	for(int i = 1; i <= n; i++)
		if(u[i] == A && v[i] == B)t = max(t, w[i]);
	ans = (ll)A * B * t;
	for(int i = C; i > t; i--)
	{
		for(int j = 1; j <= n; j++)
		{
			if(w[j] != i)continue;
			maxn[u[j]] = max(maxn[u[j]], v[j]);
		}
		for(int j = A; j >= 1; j--)
		{
			maxn[j] = max(maxn[j], maxn[j + 1]);
			ans += maxn[j];
		}
	}
	write(ans);
	putchar('\n');
	return 0;
}