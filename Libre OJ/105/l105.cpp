#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int n, m;
struct Node
{
    int s[2], f, v;
    int size, flag;
    void init(int _v, int _f)
    {
        v = _v, f = _f;
        size = 1;
    }
}tr[N];
int rt, idx;
void pushup(int x)
{
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}
void pushdown(int x)
{
    if(tr[x].flag)
    {
        swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[0]].flag ^= 1;
        tr[tr[x].s[1]].flag ^= 1;
        tr[x].flag = 0;
    }
}
void rotate(int x)
{
    int y = tr[x].f, z = tr[y].f;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].f = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].f = y;
    tr[x].s[k ^ 1] = y, tr[y].f = x;
    pushup(y), pushup(x);
}
void splay(int x, int k)
{
    while(tr[x].f != k)
    {
        int y = tr[x].f, z = tr[y].f;
        if(z != k)
        {
            if((tr[y].s[1] == x) ^ (tr[z].s[1] == y))
            {
                rotate(x);
            }
            else
            {
                rotate(y);
            }
        }
        rotate(x);
    }
    if(!k) rt = x;
}
void insert(int v)
{
    int u = rt, f = 0;
    while(u) f = u, u = tr[u].s[v > tr[u].v];
    u = ++idx;
    if(f) tr[f].s[v > tr[f].v] = u;
    tr[u].init(v, f);
    splay(u, 0);
}
int get_k(int k)
{
    int u = rt;
    while(true)
    {
        pushdown(u);
        if(tr[tr[u].s[0]].size >= k)
        {
            u = tr[u].s[0];
        }
        else if(tr[tr[u].s[0]].size + 1 == k)
        {
            return u;
        }
        else
        {
            k -= tr[tr[u].s[0]].size + 1;
            u = tr[u].s[1];
        }
    }
    return -1;
}
void output(int u)
{
    pushdown(u);
    if(tr[u].s[0]) output(tr[u].s[0]);
    if(tr[u].v >= 1 && tr[u].v <= n) printf("%d ", tr[u].v);
    if(tr[u].s[1]) output(tr[u].s[1]);
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= n + 1; i++) insert(i);
    while(m--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l = get_k(l), r = get_k(r + 2);
        splay(l, 0), splay(r, l);
        tr[tr[r].s[0]].flag ^= 1;
    }
    output(rt);
    return 0;
}