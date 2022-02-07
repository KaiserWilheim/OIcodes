#include <iostream>
using namespace std;
int n, m1, m2;
int s[10001], zs[10001] = { 0 };
int mz, t = 2, ans = 0x7fffffff;
int main()
{
    cin >> n >> m1 >> m2;
    for(int i = 1; i <= n; i++) cin >> s[i];
    if(m1 == 1) { cout << 0 << endl; return 0; }
    while(m1 != 1)
    {
        while(!(m1 % t)) m1 /= t, zs[t]++;
        mz = max(mz, t);
        zs[t++] *= m2;
    }
    for(int i = 1; i <= n; i++)
    {
        int l = 0;
        for(int j = 2; j <= mz; j++)
        {
            if(!zs[j]) continue;
            int c = 0;
            while(!(s[i] % j)) s[i] /= j, c++;
            if(!c) { l = 0x7fffffff; break; }
            l = max(l, (zs[j] - 1) / c);
        }
        ans = min(ans, l);
    }
    cout << (ans == 0x7fffffff ? -1 : ans + 1) << endl;//
    return 0;
}
