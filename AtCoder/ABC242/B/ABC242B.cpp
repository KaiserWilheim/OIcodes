#include<bits/stdc++.h>
using namespace std;
int n, ans;
int a[300009];
string s;

int main()
{
	cin >> s;
	n = s.length();
	for(int i = 0; i < n; i++)a[i] = s[i];
	sort(a, a + n);
	for(int i = 0; i < n; i++)printf("%c", a[i]);
	return 0;
}
