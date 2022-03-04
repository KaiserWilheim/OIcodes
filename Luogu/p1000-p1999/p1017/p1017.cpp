#include <bits/stdc++.h>
using namespace std;
int num[20];
int main(){
	long long n,r;
	cin>>n>>r;
	long long m=n;
	for(int i=1;n!=0;i++){
		int t=n%r;
		n=(n-t)/r;
		//cout<<"i="<<i<<" n="<<n<<" t="<<t<<endl;
		if(t<0){
			t-=r;
			n++;
			//puts("Detected t<0.Changing results.");
			//cout<<"i="<<i<<" n="<<n<<" t="<<t<<endl;
		}
		num[i]=t;
		num[0]++;
	}
	cout<<m<<"=";
	for(int i=num[0];i>=1;i--){
		if(num[i]>=10){
			char c=num[i]-10+'A';
			cout<<c;
		}else{
			cout<<num[i];
		}
	}
	cout<<"(base"<<r<<")"<<endl;
	return 0;
}
