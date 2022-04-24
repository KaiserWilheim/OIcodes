#include<bits/stdc++.h>
using namespace std;
int i, m, n, j, k, l, o, p;
int a[1001][1001], ma[1001], maxx, maxy;
int z[6] = { 2,1,0,0,0,0 }, s[6] = { 6,6,6,6,5,4 };

char c[1001][1001], c1[10][10] = {
"  +---+",
" /   /|",
"+---+ |",
"|   | +",
"|   |/",
"+---+",
};

void fg(int x, int y)
{
    int i, j;
    for(i = 5; i >= 0; i--)
        for(j = z[i]; j <= s[i]; j++)
        {
            c[5 - i + x][j + y] = c1[i][j];
            if(5 - i + x > maxx) maxx = 5 - i + x;
            if(j + y > maxy) maxy = j + y;
        }
}

int main()
{
    scanf("%d%d", &n, &m);
    for(i = 1; i <= n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &a[i][j]);
    for(o = 1; o <= n; o++)
        for(k = 0; k < m; k++)
            for(l = 0; l < a[o][k]; l++)
                fg((n - o) * 2 + 1 + 3 * l, (n - o) * 2 + 1 + 4 * k);

    for(i = maxx; i >= 1; i--)
    {
        for(j = 1; j <= maxy; j++)
            if(c[i][j] == '\000') printf(".");
            else printf("%c", c[i][j]);
        printf("\n");
    }
    return 0; 
}
