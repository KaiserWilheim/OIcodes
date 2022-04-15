#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
struct node
{
    int st, ed;
}m[N];
bool cmp(node a, node b)
{
    return a.st < b.st;
}
int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d%d", &m[i].st, &m[i].ed);
    sort(m + 1, m + 1 + n, cmp);
    int st = m[1].st;
    int ed = m[1].ed;
    int ans1 = 0, ans2 = 0;
    for(int i = 2; i <= n; ++i)
    {
        if(m[i].st <= ed)
            ed = max(ed, m[i].ed);
        else
        {
            ans1 = max(ans1, ed - st);
            ans2 = max(ans2, m[i].st - ed);
            st = m[i].st;
            ed = m[i].ed;
        }
    }
    ans1 = max(ans1, ed - st);
    printf("%d %d", ans1, ans2);
    return 0;
}
