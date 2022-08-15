#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	char c = 'A' + ((b - 1) / a);
	cout << c << endl;
	return 0;
}
