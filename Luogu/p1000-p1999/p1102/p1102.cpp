#include <bits/stdc++.h>
using namespace std;
int n,c;
long long ans;
map<int,int> a;
int num[200005];
int main()
{
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&num[i]);
        a[num[i]]++;
    }
    for(int i=1;i<=n;i++)
    {
        ans+=a[num[i]+c];
    }
    printf("%lld",ans);
    return 0;
}
