#include<bits/stdc++.h>
#define N 1001
using namespace std;
int t;
int mapp[N][N], c[N];
int main()
{
    cin >> t;
    while(t)
    {
        memset(c, 0, sizeof c);
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= 5; j++)
            {
                cin >> mapp[i][j];
                c[j] += mapp[i][j];
            }
        }
        bool visit = false;
        for(int i = 1; i <= 5; i++)
        {
            for(int j = i + 1; j <= 5; j++)
            {
                int cnt = 0, l = 0, r = 0;
                for(int k = 1; k <= n; k++)
                {
                    if(mapp[k][i] == 1 && mapp[k][j] == 1)cnt++;
                    else l += mapp[k][i], r += mapp[k][j];
                }
                if(cnt + l + r == n && l <= n / 2 && r <= n / 2)
                {
                    puts("Yes");
                    visit = true;
                    break;
                }
            }
            if(visit)break;
        }
        if(!visit)puts("No");
        t--;
    }
}
