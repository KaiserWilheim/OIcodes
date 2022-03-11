#include<bits/stdc++.h>
using namespace std;
const int N = 300010;
int n;
int a[N], b[N];
int main()
{
    int ans = -1e9;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if(i < 2) b[i] = a[i];
        else b[i] = max(a[i], b[i - 1] + a[i]);
        ans = max(ans, b[i]);
    }
    cout << ans << endl;
    return 0;
}
