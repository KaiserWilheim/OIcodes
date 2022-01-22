#include<bits/stdc++.h>
using namespace std;
const int N = 5000100;
int n, m, cnt, fa[N], sum;
double ans;
struct Node {
	int x, y;
}E[N];
struct node {
	int from, to;
	double w;
}e[N];
int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') w = -1;ch = getchar();}
	while(isdigit(ch)) {s = s * 10 + ch - '0';ch = getchar();}
	return s * w;
}
void add(int x, int y, double z) {
	e[++cnt].from =x;
	e[cnt].to = y;
	e[cnt].w = z;
}
double jl(int x, int y) {
	return (double)(sqrt((double)(E[x].x - E[y].x) * (E[x].x - E[y].x) + (double)(E[x].y - E[y].y) * (E[x].y - E[y].y)));
}
bool cmp(node x, node y) {
	if(x.w == y.w) return x.from < y.from;
	return x.w < y.w;
}
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) 
		E[i].x = read(), E[i].y = read();
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			double z = jl(i, j);
			add(i, j, z);
		}
	}
	for(int i = 1; i <= m; i++) {
		int x = read(), y = read();
		add(x, y, 0.0);
	}
	sort(e + 1, e + 1 + cnt, cmp);
	for(int i = 1; i <= cnt; i++) {
		int fx = find(e[i].from), fy = find(e[i].to);
		if(fx != fy) {
			fa[fx] = fy;
			sum++;
			ans += e[i].w;
		}
		if(sum == n - 1) break;
	}
	printf("%.2lf\n", ans);
	return 0;
}
