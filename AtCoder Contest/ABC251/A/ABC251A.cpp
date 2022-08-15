#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin >> s;
	int len = s.size();
	for(int i = 1; i * len <= 6; i++)
		cout << s;
	putchar('\n');
	return 0;
}
