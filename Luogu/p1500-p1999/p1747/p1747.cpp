#include <bits/stdc++.h>
using namespace std;
int wa(int x,int y){
	if(x<y){
		int temp=x;
		x=y;
		y=temp;
	}
	if((x==2)&&(y==1))return 2;
	if((x==2)&&(y==2))return 3;
	int s1=x-y;
	int s2=s1%4;
	int s3=s1/4;
	int s4=s3+s2+(x+y-s2*3)/4;
	return s4;
}
int main(){
	int x1,y1,x2,y2;
	cin>>x1>>y1>>x2>>y2;
	cout<<wa(x1,y1)<<endl;
	cout<<wa(x2,y2)<<endl;
	return 0;
}
