#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility> 
using namespace std;
int A,B,n,ra,rb;
int a[201],b[201];
int score[5][5];
int main(){
	cin>>n>>ra>>rb;
	for(int i=1;i<=ra;i++){
		cin>>a[i];
	}
	for(int i=1;i<=rb;i++){
		cin>>b[i];
	}
	score[0][0]=0;
	score[0][1]=-1;
	score[0][2]=1;
	score[0][3]=1;
	score[0][4]=-1;
	score[1][0]=1;
	score[1][1]=0;
	score[1][2]=-1;
	score[1][3]=1;
	score[1][4]=-1;
	score[2][0]=-1;
	score[2][1]=1;
	score[2][2]=0;
	score[2][3]=-1;
	score[2][4]=1;
	score[3][0]=-1;
	score[3][1]=-1;
	score[3][2]=1;
	score[3][3]=0;
	score[3][4]=1;
	score[4][0]=1;
	score[4][1]=1;
	score[4][2]=-1;
	score[4][3]=-1;
	score[4][4]=0;
	int ia=1,ib=1;
	for(int i=1;i<=n;i++){
		if(score[a[ia]][b[ib]]==1){
			A++;
		}else if(score[a[ia]][b[ib]]==-1){
			B++;
		}
		if(ia==ra){
			ia=0;
		}
		if(ib==rb){
			ib=0;
		}
		ia++;
		ib++;
	}
	cout<<A<<" "<<B;
	return 0;
}
