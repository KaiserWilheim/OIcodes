#include<bits/stdc++.h>
using namespace std;
int a[100010];
int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
    int prev = 0;
    for(int i = 1; i <= n; i++)
    {
        if(prev >= a[i])break;
        prev = max(prev, a[i]);
    }
    cout << prev << endl;
    return 0;
}
