#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long a = 0, b = 0, k;
    string c, d;
    cin >> k;
    if(k == 10)
    {
        cin >> a >> b;
        cout << a * b << endl;
        return 0;
    }
    cin >> c >> d;
    for(int i = c.length() - 1; i >= 0; i--)
    {
        a += pow(k, c.length() - i) * (c[i] - '0') / k;
    }
    for(int i = d.length() - 1; i >= 0; i--)
    {
        b += pow(k, d.length() - i) * (d[i] - '0') / k;
    }
    cout << a * b << endl;
    return 0;
}
