#include <bits/stdc++.h>
using namespace std;
string s1, s2, s3, s4, s5, s6;
int main()
{
	int ans = 0;
	cin >> s1 >> s2 >> s3 >> s4 >> s5 >> s6;
	if(s1 != s4)
		ans++;
	if(s2 != s5)
		ans++;
	if(s3 != s6)
		ans++;
	if(ans == 0 || ans == 3)puts("Yes");
	else puts("No");
	return 0;
}
