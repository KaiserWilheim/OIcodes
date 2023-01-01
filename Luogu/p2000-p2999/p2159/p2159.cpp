#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 210, M = 510;
int n, k;
int m[N], f[N];
struct i32
{
	int n;
	int a[M];
	i32() { n = 0; memset(a, 0, sizeof(a)); }
	i32(int x)
	{
		n = 0;
		memset(a, 0, sizeof(a));
		while(x)
		{
			a[++n] = x % 10;
			x /= 10;
		}
	}
	friend i32 operator + (const i32 &lhs, const i32 &rhs)
	{
		i32 res;
		res.n = max(lhs.n, rhs.n);
		for(int i = 1; i <= res.n; i++)
			res.a[i] = lhs.a[i] + rhs.a[i];
		for(int i = 1; i <= res.n; i++)
		{
			if(res.a[i] > 9)
			{
				res.a[i] -= 10;
				res.a[i + 1]++;
				if(i == res.n)res.n++;
			}
		}
		return res;
	}
	friend i32 operator * (const i32 &lhs, const i32 &rhs)
	{
		i32 res;
		res.n = lhs.n + rhs.n - 1;
		for(int i = 1; i <= lhs.n; i++)
		{
			for(int j = 1; j <= rhs.n; j++)
			{
				res.a[i + j - 1] += lhs.a[i] * rhs.a[j];
				if(res.a[i + j - 1] > 9)
				{
					res.a[i + j] += res.a[i + j - 1] / 10;
					res.a[i + j - 1] %= 10;
					if(i + j - 1 == res.n)res.n++;
				}
			}
		}
		while(res.n > 1 && res.a[res.n] == 0)res.n--;
		return res;
	}
	friend i32 operator + (const i32 &lhs, const int &rhs)
	{
		return lhs + i32(rhs);
	}
	friend i32 operator * (const i32 &lhs, const int &rhs)
	{
		return lhs * i32(rhs);
	}
	void operator = (int rhs)
	{
		n = 0;
		memset(a, 0, sizeof(a));
		while(rhs)
		{
			a[++n] = rhs % 10;
			rhs /= 10;
		}
	}
	void write(string s = "")
	{
		for(int i = n; i; i--)
			printf("%d", a[i]);
		cout << s;
	}
};
i32 dp[2][N];
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &m[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &f[i]);
	sort(m + 1, m + 1 + n);
	sort(f + 1, f + 1 + n);
	dp[0][0] = 1;
	for(int i = 1; i <= n; i++)
	{
		int a = 0, sign = i & 1;
		for(int j = 0; j <= i; j++)dp[sign][j] = 0;
		if(m[i] >= f[i])
		{
			for(int j = 1; j <= i; j++)
				a += (m[j] >= f[i]);
			for(int j = 0; j <= i; j++)
				dp[sign][j] = dp[!sign][j] * (j + a);
			for(int j = 1; j <= i - a; j++)
				dp[sign][j] = (dp[sign][j] + (dp[!sign][j - 1] * (i - a - (j - 1))));
		}
		else
		{
			for(int j = 1; j < i; j++)
				a += (f[j] > m[i]);
			for(int j = 1; j <= i; j++)
				dp[sign][j] = dp[sign][j] + (dp[!sign][j - 1] * (i - (j - 1 - a)));
			for(int j = a; j <= i; j++)
				dp[sign][j] = dp[sign][j] + (dp[!sign][j] * (j - a));
		}
	}
	i32 ans = 0;
	for(int i = 0; i <= k; i++)
		ans = ans + dp[n & 1][i];
	ans.write("\n");
	return 0;
}
