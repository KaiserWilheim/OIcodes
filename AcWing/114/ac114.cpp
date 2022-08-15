#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
int n, k;
struct Bint
{
	int n;
	int a[N];
	Bint()
	{
		n = 0;
		memset(a, 0, sizeof(a));
	}

	void init(int x)
	{
		while (x)
		{
			a[++n] = x % 10;
			x /= 10;
		}
	}
	void output()
	{
		for (int i = n; i >= 1; i--)
			printf("%d", a[i]);
		if (n == 0)putchar('0');
		putchar('\n');
	}
	Bint max(Bint& lhs, Bint& rhs)
	{
		if (rhs < lhs)return lhs;
		else return rhs;
	}

	friend bool operator < (const Bint& lhs, const Bint& rhs)
	{
		if (rhs.n > lhs.n)return true;
		else if (lhs.n < rhs.n)return false;
		for (int i = lhs.n; i >= 1; i--)
		{
			if (lhs.a[i] < rhs.a[i])return true;
		}
		return false;
	}
	friend bool operator > (const Bint& lhs, const Bint& rhs)
	{
		if (rhs.n < lhs.n)return true;
		else if (lhs.n > rhs.n)return false;
		for (int i = lhs.n; i >= 1; i--)
		{
			if (lhs.a[i] > rhs.a[i])return true;
		}
		return false;
	}

	friend Bint operator + (const Bint& lhs, const Bint& rhs)
	{
		Bint res = lhs;
		res.n = std::max(lhs.n, rhs.n);
		for (int i = 1; i <= res.n; i++)
			res.a[i] += rhs.a[i];
		for (int i = 1; i <= res.n; i++)
		{
			if (res.a[i] > 9)
			{
				res.a[i + 1]++;
				res.a[i] -= 10;
				if (i == res.n)res.n++;
			}
		}
		return res;
	}

	friend Bint operator * (const Bint& lhs, int rhs)
	{
		Bint res;
		res.n = lhs.n;
		for (int i = 1; i <= lhs.n; i++)
			res.a[i] = lhs.a[i] * rhs;
		for (int i = 1; i <= res.n; i++)
		{
			if (res.a[i] > 9)
			{
				res.a[i + 1] += res.a[i] / 10;
				res.a[i] %= 10;
				if (i == res.n)res.n++;
			}
			if (i == res.n && res.a[i + 1] != 0)res.n++;
		}
		return res;
	}

	friend Bint operator / (const Bint& lhs, int rhs)
	{
		Bint res;
		res.n = lhs.n;
		int x = 0;
		for (int i = lhs.n; i >= 1; i--)
		{
			res.a[i] = (x * 10 + lhs.a[i]) / rhs;
			x = (x * 10 + lhs.a[i]) % rhs;
		}
		while (res.a[res.n] == 0)res.n--;
		return res;
	}
};
struct minister
{
	int a, b;
	bool operator < (const minister& x)const
	{
		return a * b < x.a* x.b;
	}
}d[N];
int main()
{
	int ka, kb;
	scanf("%d", &n);
	scanf("%d%d", &ka, &kb);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &d[i].a, &d[i].b);
	sort(d + 1, d + 1 + n);
	Bint maxn, cnt;
	cnt.init(ka);
	for (int i = 1; i <= n; i++)
	{
		maxn = max(maxn, cnt / d[i].b);
		cnt = cnt * d[i].a;
	}
	maxn.output();
	return 0;
}
