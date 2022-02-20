#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,w;
	cin >> n >> w;
	vector<int>a;
	for(int i = 0, t; i < n; ++i)
	{
		cin >> t;
		a.insert(lower_bound(a.begin(), a.end(), t), t);
		cout << a[a.size() - max(1, int((w * a.size()) / 100))] << ' ';
    }
	return 0;
}
