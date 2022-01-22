#include<bits/stdc++.h>
#define re register
using namespace std;
struct node{
	int x,id;
};
struct d{
	int ans,pos;
}p[1000002];
int n,a[1000002],b[1000002],x,l;
unsigned long long ans;
inline int read(){
	int t=0;
	char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
inline bool cmp(re d x,re d y){
	return x.ans>y.ans;
}
stack <node> q;
signed main(){
	n=read();
	for(re int i=1;i<=n;++i)a[i]=read();
	sort(a+1,a+n+1);
	for(re int i=1;i<=n;++i)b[i]=read();
	sort(b+1,b+n+1);
	l=1;
	x=1;
	while(1){
		if(q.empty()){
			if(l<=n)
			x=a[l];
			else break;
		}
		while(a[l]==x){
			q.push(node{a[l],l});
			++l;
		}
		node tmp=q.top();
		q.pop();
		p[tmp.id].ans=x-tmp.x;
		++x;
	}
	sort(p+1,p+n+1,cmp);
	for(re int i=1;i<=n;++i){ans+=1llu*p[i].ans*b[i];
	}
	printf("%llu",ans);
}
