#include<bits/stdc++.h> 
using namespace std;
int n, m, t, stx, sty, edx, edy;
int X[4] = { 1,-1,0,0 }, Y[4] = { 0,0,1,-1 };
bool ok[110][110];
int ans;
inline int abs(int s)
{
    if(s < 0)return -s;
    return s;
}
inline void dfs(int x, int y, int time)
{
    if((x == edx) && (y == edy) && (time == 0))ans++;
    if((!time) || (abs(x - edx) + abs(y - edy) > time))return;
    int i;
    for(i = 0; i < 4; i++)
        if((x >= 1) && (x <= n) && (y >= 1) && (y <= m) && (ok[x][y]))
            dfs(x + X[i], y + Y[i], time - 1);
}
int main()
{
    cin >> n >> m >> t;
    int i, j, k;
    char c;
    for(i = 1; i <= n; i++)
        for(j = 1; j <= m; j++) { 
            cin >> c; 
            if(c == '.')ok[i][j] = true; 
            else ok[i][j] = false; 
        }
    cin >> stx >> sty >> edx >> edy;
    dfs(stx, sty, t);
    cout << ans;
}
