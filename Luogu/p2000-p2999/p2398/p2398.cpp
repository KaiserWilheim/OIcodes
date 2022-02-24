#include <bits/stdc++.h>
#define ll long long
#define int long long 
const int Maxn=2e6+10;
using namespace std;
int p[Maxn],book[Maxn];
long long phi[Maxn],sum[Maxn];
void prime(int n) {
  int cnt=0; 
  phi[1]=1;
  for(int i=2;i<=n;++i){
    if(!book[i]){
      book[i]=i;p[++cnt]=i; 
      phi[i]=1ll*(i-1);
    }
    for(int j=1;j<=cnt;++j) {
      if((p[j]>book[i])||(i*p[j]>n)) break;
      book[i*p[j]] = p[j]; 
      phi[i*p[j]] = 1ll * phi[i] * p[j];
      if ( i % p[j] ) phi[i*p[j]] -= phi[i];
      else break;
    }
  }
  for ( int i = 1; i <= n; ++i ) {
    sum[i] = 1ll * ( sum[i-1] + phi[i] );
  }
  return; 
}
signed main(){
  int n;
  long long ans=0; 
  cin>>n;
  prime(n);
  for(int d=1,r;d<=n;d=r+1){
    int t=n/d; 
    r=n/t;
    ans+=t*t*(sum[r]-sum[d-1]);
  }
  cout<<ans<<endl;
  return 0;
}
