#include <bits/stdc++.h>
using namespace std;
int n,m;
long long s;
long long w[200010],v[200010],ri[200010],li[200010],cnt[200010],sum[200010];
long long chk(long long mid){
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1];
		cnt[i]=cnt[i-1];
		if(w[i]>=mid){
			sum[i]+=v[i];
			cnt[i]++;
		}
	}//Ç°×ººÍ 
	long long ans=0;
	for(int i=1;i<=m;i++){
		ans+=(cnt[ri[i]]-cnt[li[i]-1])*(sum[ri[i]]-sum[li[i]-1]);
	}
	return ans;
}
int main(){
	long long l=0,r=0,mid;
	cin>>n>>m>>s;
	for(int i=1;i<=n;i++){
		cin>>w[i]>>v[i];
		r=max(r,w[i]);
	}
	for(int i=1;i<=m;i++){
		cin>>li[i]>>ri[i];
	}
	long long ans=1e18;
	while(l<=r){
		mid=(l+r)/2;
		long long y=chk(mid);
		ans=min(ans,abs(y-s));
		if(y<=s){
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	cout<<ans<<endl;
	return 0;
}
