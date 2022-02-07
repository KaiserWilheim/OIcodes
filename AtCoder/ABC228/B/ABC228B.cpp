#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int sh[N];
bool know[N];
void share(int p)
{
    if(!know[p])
    {
        know[p] = true;
        share(sh[p]);
        return;
    }
    return;
}
int main()
{
    int n, x;
    cin >> n >> x;
    for(int i = 1; i <= n; i++)
    {
        cin >> sh[i];
    }
    share(x);
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        if(know[i])ans++;
    }
    cout << ans << endl;
}
