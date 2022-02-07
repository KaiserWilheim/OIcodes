#include <bits/stdc++.h>
using namespace std;
long long a[100010];
int main()
{
    long long n, x, as = 0;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        as += a[i];
    }
    cin >> x;
    long long ans = x / as;
    if(x % as == 0)
    {
        cout << ans * n + 1 << endl;
        return 0;
    }
    else
    {
        long long sum = as * ans;
        for(int i = 1; i <= n; i++)
        {
            sum += a[i];
            if(sum > x)
            {
                cout << ans * n + i << endl;
                return 0;
            }
        }
    }
    return 0;
}
