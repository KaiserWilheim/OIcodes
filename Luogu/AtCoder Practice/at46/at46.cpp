#include <bits/stdc++.h>
using namespace std;
int fin[11]={0,1,2,3,2,1,2,3,3,2,1};
int main(){
	int a,b;
	cin>>a>>b;
	int c=abs(a-b);
	cout<<(c/10+fin[c%10])<<endl;
	return 0;
}
