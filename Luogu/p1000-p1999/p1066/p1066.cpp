#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 550, M = 210;
string c[N][N];
int n, k;
int p, t;
int res;
int aa[M], bb[M], cc[M];
inline string sum(string a, string b)
{
	memset(aa, 0, sizeof(aa));
	memset(bb, 0, sizeof(bb));
	memset(cc, 0, sizeof(cc));
	int lena = a.size();
	int lenb = b.size();
	for(int i = 0; i < lena; i++)
		aa[i + 1] = a[lena - i - 1] - 48;
	for(int i = 0; i < lenb; i++)
		bb[i + 1] = b[lenb - i - 1] - 48;
	int p = 1;
	for(p = 1; p <= max(lena, lenb) || cc[p]; p++)
	{
		cc[p] += aa[p] + bb[p];
		cc[p + 1] += cc[p] / 10;
		cc[p] %= 10;
	}
	string C = "\0";
	for(int i = p - 1; i; i--)
		C += char(cc[i] + 48);
	return C;
}
int main()
{
	scanf("%d%d", &k, &n);
	p = n / k;
	res = n % k;
	t = (1 << k);
	c[0][0] = "1";
	for(int i = 1; i <= t - 1; i++)
		c[i][0] = c[i][i] = "1";
	for(int i = 1; i < t; i++)
		for(int j = 1; j < i; j++)
			c[i][j] = sum(c[i - 1][j - 1], c[i - 1][j]);
	string ans = "0";
	for(int i = 2; i <= p && i <= t - 1; i++)
		ans = sum(ans, c[t - 1][i]);
	int pp = (1 << res) - 1;
	for(int i = 1; i <= pp && i <= t - p - 1; i++)
		ans = sum(ans, c[t - 1 - i][p]);
	cout << ans << endl;
	return 0;
}
