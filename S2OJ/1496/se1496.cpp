#include <bits/stdc++.h>
using namespace std;
int n, T;
char s[20][3];
int a[20];
int cnt1[50], cnt2[50], cnt[50];

int check1(int s, int x) {
	for (int i = 1; i <= n; ++i) {
		cnt1[a[i]] = cnt2[a[i]] = 0;
	}
	int flag = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == x && flag < 2) ++flag;
		else if (s >> (i - flag - 1) & 1) {
			++cnt1[a[i]];
		}
		else ++cnt2[a[i]];
	}
	if (flag != 2) return 0;
	flag = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == x && flag < 2) ++flag;
		else if (s >> (i - flag - 1) & 1) {
			if (cnt1[a[i]] % 3) return 0;
		}
		else {
			if (cnt2[a[i]]) {
				if (!cnt2[a[i] + 1] || !cnt2[a[i] + 2]) return 0;
				--cnt2[a[i]], --cnt2[a[i] + 1], --cnt2[a[i] + 2];
			}
		}
	}
	return 1;
}

int check() {
	for (int i = 0; i <= 30; ++i) cnt[i] = cnt1[i] = cnt2[i] = 0;
	for (int i = 1; i <= n; ++i) {
		if (s[i][1] == 'm') a[i] = s[i][0] - '0';
		else if (s[i][1] == 'p') a[i] = s[i][0] - '0' + 10;
		else a[i] = s[i][0] + 20 - '0';
	}
	for (int i = 1; i <= n; ++i) {
		++cnt[a[i]];
		if (cnt[a[i]] > 4) return 0;
	}
	std::sort(a + 1, a + n + 1);
	for (int s = 0; s < (1 << (n - 2)); ++s) {
		for (int i = 1; i <= n; ++i) {
			if (check1(s, a[i])) return 1;
		}
	}
	return 0;
}

int main() {
	scanf("%d%d", &n, &T);
	if (n == 14) {
		while (T--) {
			for (int i = 1; i <= 14; ++i) {
				scanf("%s", s[i]);
			}
			printf("%d\n", check());
		}
	}
	else {
		while (T--) {
			n = 14;
			for (int i = 1; i <= 13; ++i) {
				scanf("%s", s[i]);
			}
			for (int i = 1; i <= 9; ++i) {
				s[n][0] = i + '0';
				s[n][1] = 'm';
				if (check()) printf("%c%c ", s[n][0], s[n][1]);
			}
			for (int i = 1; i <= 9; ++i) {
				s[n][0] = i + '0';
				s[n][1] = 'p';
				if (check()) printf("%c%c ", s[n][0], s[n][1]);
			}
			for (int i = 1; i <= 9; ++i) {
				s[n][0] = i + '0';
				s[n][1] = 's';
				if (check()) printf("%c%c ", s[n][0], s[n][1]);
			}
			puts("");
		}
	}
    return 0;
}