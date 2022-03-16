#include <bits/stdc++.h>
int book[10001];
int match[10001];
int e[101][101];
int a[10001], b[10001];
int ans = 0, n = 0;
bool dfs(int u)
{
    for(int i = 1; i <= n; i++)
    {
        if(book[i] == 0 && a[i] == 1 && e[u][i] == 1)
        {
            book[i] = 1;
            if(match[i] == 0 || dfs(match[i]) == true)
            {
                match[i] = u;
                return true;
            }
        }
    }
    return false;
}
bool work()
{
    for(int i = 1; i <= n; i++)
    {
        memset(book, 0, sizeof(book));
        if((a[i] == 0 || b[i] == 0) && (dfs(i) == false))
        {
            return false;
        }
    }
    return true;
}
int main()
{
    int t = 0;
    scanf("%d", &t);
    while(t--)
    {
        ans = 0;
        memset(book, 0, sizeof(book));
        memset(match, 0, sizeof(match));
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(e, 0, sizeof(e));
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
        }
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &b[i]);
            if(a[i] == 0)
            {
                b[i] = 1;
            }
        }
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                scanf("%d", &e[i][j]);
            }
            if(a[i] == 1)
            {
                e[i][i] = 1;
            }
        }
        if(work() == true)
        {
            printf("^_^\n");
        }
        else
        {
            printf("T_T\n");
        }
    }
    return 0;
}
