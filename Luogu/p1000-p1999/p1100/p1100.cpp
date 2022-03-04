#include<bits/stdc++.h>
int main(){
    long long x,a,b,c;
    std::cin>>x;
    a=x%65536;
    b=x/65536;
    c=a*65536+b;
    std::cout<<c<<std::endl;
    return 0;
}
