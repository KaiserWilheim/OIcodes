#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++)
    {
        int n;
        cin >> n;
        int ans = 0;
        for(int j = 1; j <= n; j++)
        {
            int a;
            cin >> a;
            ans = max(ans, a - j);
        }
        cout << ans << endl;
    }
    return 0;
}
