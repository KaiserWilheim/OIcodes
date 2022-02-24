#include <bits/stdc++.h>
using namespace std;
const int N = 500010, INF = 1000000000;
int n, m;
struct Node
{
    int s[2], p, v;
    int rev, same;
    int sz, sum, ms, ls, rs;
    void init(int _v, int _p)
    {
        s[0] = s[1] = 0;
        p = _p, v = _v;
        rev = same = 0;
        sz = 1;
        sum = ms = v;
        ls = rs = max(v, 0);
    }
}tr[N];
int rt, recycle[N], tt;
int w[N];
void pushup(int x)
{
    auto &u = tr[x], &l = tr[u.s[0]], &r = tr[u.s[1]];
    u.sz = l.sz + r.sz + 1;
    u.sum = l.sum + r.sum + u.v;
    u.ls = max(l.ls, l.sum + u.v + r.ls);
    u.rs = max(r.rs, r.sum + u.v + l.rs);
    u.ms = max(max(l.ms, r.ms), l.rs + u.v + r.ls);
}
void pushdown(int x)
{
    auto &u = tr[x], &l = tr[u.s[0]], &r = tr[u.s[1]];
    if(u.same)
    {
        u.same = u.rev = 0;
        if(u.s[0]) l.same = 1, l.v = u.v, l.sum = l.v * l.sz;
        if(u.s[1]) r.same = 1, r.v = u.v, r.sum = r.v * r.sz;
        if(u.v > 0)
        {
            if(u.s[0]) l.ms = l.ls = l.rs = l.sum;
            if(u.s[1]) r.ms = r.ls = r.rs = r.sum;
        }
        else
        {
            if(u.s[0]) l.ms = l.v, l.ls = l.rs = 0;
            if(u.s[1]) r.ms = r.v, r.ls = r.rs = 0;
        }
    }
    else if(u.rev)
    {
        u.rev = 0, l.rev ^= 1, r.rev ^= 1;
        swap(l.ls, l.rs), swap(r.ls, r.rs);
        swap(l.s[0], l.s[1]), swap(r.s[0], r.s[1]);
    }
}
void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}
void splay(int x, int k)
{
    while(tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;
        if(z != k)
            if((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if(!k) rt = x;
}
int get_k(int k)
{
    int u = rt;
    while(u)
    {
        pushdown(u);
        if(tr[tr[u].s[0]].sz >= k) u = tr[u].s[0];
        else if(tr[tr[u].s[0]].sz + 1 == k) return u;
        else k -= tr[tr[u].s[0]].sz + 1, u = tr[u].s[1];
    }
    return 0;
}
int build(int l, int r, int p)
{
    int mid = (l + r) >> 1;
    int u = recycle[tt--];
    tr[u].init(w[mid], p);
    if(l < mid) tr[u].s[0] = build(l, mid - 1, u);
    if(mid < r) tr[u].s[1] = build(mid + 1, r, u);
    pushup(u);
    return u;
}
void del(int u)
{
    if(tr[u].s[0]) del(tr[u].s[0]);
    if(tr[u].s[1]) del(tr[u].s[1]);
    recycle[++tt] = u;
}
int main()
{
    for(int i = 1; i < N; i++) recycle[++tt] = i;
    scanf("%d%d", &n, &m);
    tr[0].ms = w[0] = w[n + 1] = -INF;
    for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
    rt = build(0, n + 1, 0);
    char op[20];
    while(m--)
    {
        scanf("%s", op);
        if(!strcmp(op, "INSERT"))
        {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            for(int i = 0; i < tot; i++) scanf("%d", &w[i]);
            int l = get_k(posi + 1), r = get_k(posi + 2);
            splay(l, 0), splay(r, l);
            int u = build(0, tot - 1, r);
            tr[r].s[0] = u;
            pushup(r), pushup(l);
        }
        else if(!strcmp(op, "DELETE"))
        {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            del(tr[r].s[0]);
            tr[r].s[0] = 0;
            pushup(r), pushup(l);
        }
        else if(!strcmp(op, "MAKE-SAME"))
        {
            int posi, tot, c;
            scanf("%d%d%d", &posi, &tot, &c);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            auto &son = tr[tr[r].s[0]];
            son.same = 1, son.v = c, son.sum = c * son.sz;
            if(c > 0) son.ms = son.ls = son.rs = son.sum;
            else son.ms = c, son.ls = son.rs = 0;
            pushup(r), pushup(l);
        }
        else if(!strcmp(op, "REVERSE"))
        {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            auto &son = tr[tr[r].s[0]];
            son.rev ^= 1;
            swap(son.ls, son.rs);
            swap(son.s[0], son.s[1]);
            pushup(r), pushup(l);
        }
        else if(!strcmp(op, "GET-SUM"))
        {
            int posi, tot;
            scanf("%d%d", &posi, &tot);
            int l = get_k(posi), r = get_k(posi + tot + 1);
            splay(l, 0), splay(r, l);
            printf("%d\n", tr[tr[r].s[0]].sum);
        }
        else printf("%d\n", tr[rt].ms);
    }
    return 0;
}
