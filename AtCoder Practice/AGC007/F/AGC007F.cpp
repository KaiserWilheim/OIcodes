#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n, ans;
string s, t;
queue<int>q;
int main()
{
	const char endl = '\n';
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	cin >> s >> t;
	if(s == t)
	{
		puts("0");
		return 0;
	}
	int up = n - 1, down = n - 1;
	while(down >= 0)
	{
		while(down && t[down - 1] == t[down])down--;
		while(up >= 0 && (up > down || s[up] != t[down]))up--;
		if(up < 0)
		{
			puts("-1");
			return 0;
		}
		while(!q.empty() && q.front() - q.size() >= down)q.pop();
		if(up != down)q.push(up);
		ans = max(ans, int(q.size() + 1));
		down--;
	}
	cout << ans << endl;
	return 0;
}