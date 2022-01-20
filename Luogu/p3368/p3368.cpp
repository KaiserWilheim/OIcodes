/*
    __ __      _               _       ___ ____         _         
   / //_/___ _(_)_______  ____| |     / (_) / /_  ___  (_)___ ___ 
  / ,< / __ `/ / ___/ _ \/ ___/ | /| / / / / __ \/ _ \/ / __ `__ \
 / /| / /_/ / (__  )  __/ /   | |/ |/ / / / / / /  __/ / / / / / /
/_/ |_\__,_/_/____/\___/_/    |__/|__/_/_/_/ /_/\___/_/_/ /_/ /_/

           £¯£¾¡¡ ¥Õ
           |  _  _l
¡¡ ¡¡¡¡¡¡£¯`¥ß£ßw¥Î
¡¡¡¡ ¡¡ /¡¡¡¡¡¡ ¡¡|
¡¡¡¡¡¡ /¡¡ ©c¡¡¡¡ |
¡¡ ¡¡ ©¦¡¡¡¡|¡¡|¡¡|
¡¡£¯£þ|¡¡¡¡ |¡¡|¡¡|
¡¡| (£þ©c£ß_©c_)__)
 £Ü¶þ¤Ä
*/
#include <bits/stdc++.h>
using namespace std;
const int N=500010;
int num[N],a[N],tr[N];
int idx,hd,n;
int lowbit(int a){
	return a&-a;
}
void add(int x,int c){
	for(int i=x;i<=n;i+=lowbit(i)){
		tr[i]+=c;
	}
	return;
}
int sum(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i)){
		res+=tr[i];
	}
	return res;
}
int main(){
	int m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>num[i];
		a[i]=num[i]-num[i-1];
		add(i,a[i]);
	}
	for(int i=1;i<=m;i++){
		int op;
		cin>>op;
		if(op==1){
			int x,y,k;
			cin>>x>>y>>k;
			add(x,k);
			add(y+1,-k);
		}else if(op==2){
			int x;
			cin>>x;
			cout<<sum(x)<<endl; 
		}
	}
	return 0;
}
