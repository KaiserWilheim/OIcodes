#include<bits/stdc++.h>
using namespace std;
char s[20];
int main()
{
    int a, b;
    scanf("%s%d%d", s, &a, &b);
    char t = s[b - 1];
    s[b - 1] = s[a - 1];
    s[a - 1] = t;
    cout << s;
    return 0;
}
