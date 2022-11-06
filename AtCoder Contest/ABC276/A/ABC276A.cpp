#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
int n, m;
char s[N];
int main()
{
	cin >> s + 1;
	n = strlen(s + 1);
	int pos = -1;
	for(int i = 1; i <= n; i++)
		if(s[i] == 'a')pos = i;
	cout << pos << endl;
	return 0;
}
