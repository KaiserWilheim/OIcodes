#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010;
int cnt[N << 1], fa[N << 1], ch[N << 1][4], l[N << 1], last, tot;
char s[N]; int c[N], a[N], ans, m, val[N];

void ins(int c)
{
    int p = last, np = ++tot; last = np, l[np] = l[p] + 1, cnt[np] = 1;
    for(; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
    if(!p) fa[np] = 1;
    else
    {
        int q = ch[p][c];
        if(l[q] == l[p] + 1) fa[np] = q;
        else
        {
            int nq = ++tot; l[nq] = l[p] + 1;
            memcpy(ch[nq], ch[q], sizeof(ch[q]));
            fa[nq] = fa[q], fa[q] = fa[np] = nq;
            for(; ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
        }
    }
}

inline void calc()
{
    memset(c, 0, sizeof(c));
    for(int i = 1; i <= tot; ++i) ++c[l[i]];
    for(int i = 1; i <= tot; ++i) c[i] += c[i - 1];
    for(int i = 1; i <= tot; ++i) a[c[l[i]]--] = i;
    for(int i = tot, p; i; --i)
        p = a[i], cnt[fa[p]] += cnt[p];
}

void dfs(int p, int len, int j)
{
    if(len > m) return ( void )(ans += cnt[p]);
    for(int i = 0; i < 4; ++i)
    {
        if(!ch[p][i]) continue;
        if(val[s[len]] == i) dfs(ch[p][i], len + 1, j);
        else if(j < 3) dfs(ch[p][i], len + 1, j + 1);
    }
}

int main()
{
    val['T'] = 0, val['A'] = 1, val['C'] = 2, val['G'] = 3;
    int T; scanf("%d", &T);
    while(T--)
    {
        memset(ch, 0, sizeof(ch)), memset(cnt, 0, sizeof(cnt));
        last = tot = 1, ans = 0;
        scanf("%s", s + 1); int len = strlen(s + 1);
        for(int i = 1; i <= len; ++i) ins(val[s[i]]);
        calc();
        scanf("%s", s + 1), m = strlen(s + 1);
        dfs(1, 1, 0); printf("%d\n", ans);
    }
    return 0;
}
