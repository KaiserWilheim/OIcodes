#include <bits/stdc++.h>
using namespace std;
int main(){
	string s;
	int ans[22000];
	int c[8];
	cin>>s;
	if(s.length()%8!=0)
	{//Դ��Ϣ�����ܷ�8���� 
		goto end;
	}
	for(int i=0;i<s.length();i++)
	{//Դ��Ϣ����0��1������ַ� 
		if((s[i]!='1')&&(s[i]!='0')){
			goto end;
		}
	}
	for(int i=0;i<s.length()/8;i++){
		for(int j=1;j<=8;j++)c[j]=s[8*i+j-1]-'0';
		if(c[1]==1){
			if(c[2]==1){
				if(c[3]!=1)
				{//�ǿո�Ԫͷ 
					goto end;
				} 
				ans[i+1]=-100;
				continue;
			}else if(c[2]==0){
				if(c[3]!=1)
				{//����ĸ��Ԫͷ 
					goto end;
				} 
				int temp=c[4]*16+c[5]*8+c[6]*4+c[7]*2+c[8]+1;
				if(temp>26)
				{//һ����ĸ��Ԫת����Ľ�����ڵ���26 
					goto end;
				}
				ans[i+1]=-temp;
			}
		}else if(c[1]==0){
			int d[10];
			for(int j=1;j<=8;j++)d[j]=s[8*i+j+7]-'0';
			if(d[1]!=0)
			{//���ֿ�ʼ��Ԫ֮��ĵ�Ԫ�������ֵ�Ԫ 
				goto end;
			}
			int e=c[2]*64+c[3]*32+c[4]*16+c[5]*8+c[6]*4+c[7]*2+c[8];
			int f=d[2]*64+d[3]*32+d[4]*16+d[5]*8+d[6]*4+d[7]*2+d[8];
			ans[i+1]=e/2+f/2;
			ans[i+2]=-1000;
			i++;
		}
	}
	for(int i=1;i<=s.length()/8;i++){
		if(ans[i]==-1000)continue;
		if(ans[i]==-100){
			cout<<" ";
			continue;
		}
		if((ans[i]<0)&&(ans[i]!=-1000)){
			char un='A'-ans[i]-1;
			cout<<un;
			continue;
		}
		if(ans[i]>=0){
			cout<<ans[i];
			continue;
		}
	}
	cout<<endl;
	return 0;
	end:;
	cout<<"Error"<<endl;
	return 0;
} 
