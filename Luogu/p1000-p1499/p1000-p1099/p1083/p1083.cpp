#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 1000010;
int diff[N], need[N], num[N], r[N], l[N], d[N];
bool isok(int x)
{
    memset(diff, 0, sizeof(diff));
    for(int i = 1; i <= x; i++)
    {
        diff[l[i]] += d[i];
        diff[r[i] + 1] -= d[i];
    }
    for(int i = 1; i <= n; i++)
    {
        need[i] = need[i - 1] + diff[i];
        if(need[i] > num[i])return 0;
    }
    return 1;
}
int main()
{

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)scanf("%d", &num[i]);
    for(int i = 1; i <= m; i++)scanf("%d%d%d", &d[i], &l[i], &r[i]);
    int begin = 1, end = m;
    if(isok(m)) { cout << "0"; return 0; }
    while(begin < end)
    {
        int mid = (begin + end) / 2;
        if(isok(mid))begin = mid + 1;
        else end = mid;
    }
    cout << "-1" << endl << begin;
}
