#include<cstdio>
const long long p=9999991;
int n;
long long ans=1;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n-2;i++) ans=(ans*n)%p;
    for(int i=1;i<=n-1;i++) ans=(ans*i)%p;
    printf("%lld\n",ans);
	return 0;
}
