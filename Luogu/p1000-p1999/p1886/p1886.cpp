#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
int n, k;
int a[N];
int q[N], p[N];
int hd, tl;
void maximize()
{
    hd = 1, tl = 0;
    for(int i = 1; i <= n; i++)
    {
        while((hd <= tl) && (a[i] >= q[tl]))tl--;
        q[++tl] = a[i];
        p[tl] = i;
        while(p[hd] <= i - k)hd++;
        if(i >= k)printf("%d ", q[hd]);
    }
    putchar('\n');
}

void minimize()
{
    hd = 1, tl = 0;
    for(int i = 1; i <= n; i++)
    {
        while((hd <= tl) && (a[i] <= q[tl]))tl--;
        q[++tl] = a[i];
        p[tl] = i;
        while(p[hd] <= i - k)hd++;
        if(i >= k)printf("%d ", q[hd]);
    }
    putchar('\n');
}
int main()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i++)cin >> a[i];
    minimize();
    maximize();
    return 0;
}
