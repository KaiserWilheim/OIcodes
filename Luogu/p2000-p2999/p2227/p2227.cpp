#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n, s, x[N], p[N], A[N], B[N], z = 1;
int main()
{
	scanf("%d%d", &n, &s);
	for(int i = 1; i <= n; i++) scanf("%d", &p[i]);
	for(int i = 1, j = 1; i <= n; i++, j = p[j]) A[i] = p[j];
	for(int i = 1; i <= s; i++) z = (z * 2) % n;
	for(int i = 1, j = 1; i <= n; i++, j = (j + z - 1) % n + 1) B[j] = A[i];
	for(int i = 1; i <= n; i++) x[B[i]] = B[i % n + 1];
	for(int i = 1; i <= n; i++) printf("%d ", x[i]);
	return 0;
}
