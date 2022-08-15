#include<bits/stdc++.h>
using namespace std;
int main()
{
    int x;
    cin >> x;
    int a = x % 10, b = (x / 10) % 10, c = x / 100;
    cout << 111 * (a + b + c) << endl;
    return 0;
}
