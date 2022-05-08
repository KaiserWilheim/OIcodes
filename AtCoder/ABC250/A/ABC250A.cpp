#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	int h, w, a, b;
	scanf("%d%d%d%d", &h, &w, &a, &b);
	int ans = 4;
	if(a == 1)ans--;
	if(b == 1)ans--;
	if(a == h)ans--;
	if(b == w)ans--;
	cout << ans << endl;
	return 0;
}
