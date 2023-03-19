#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int n;
vector<int>e[N];
bool isLeaf[N], col[N], vis[N];
int fa[N], cnt[N];
void dfs(int p, int fa) {
	if (e[p].size() <= 1)isLeaf[p] = true;
	::fa[p] = fa;
	for (auto v : e[p]) {
		if (v == fa)continue;
		col[v] = col[p] ^ 1;
		dfs(v, p);
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	if (n % 2 == 0 || e[n].size() <= 1) {
		printf("%d\n", n);
		return 0;
	}
	dfs(n, 0);
	for (int i = n; i >= 1; i--) {
		if (isLeaf[i] || col[i]) {
			printf("%d\n", i);
			return 0;
		}
		int u = i;
		while (!vis[u]) {
			vis[u] = true, u = fa[u], cnt[u]++;
		}
		if (u == 0)continue;
		if (u != n && cnt[u] >= 2 && !col[u]) {
			printf("%d\n", i);
			return 0;
		}
		if (u == n && cnt[u] >= 3 && !col[u]) {
			printf("%d\n", i);
			return 0;
		}
	}
	return 0;
}
