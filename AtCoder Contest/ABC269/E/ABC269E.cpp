#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int n;
int main()
{
	cin >> n;
	int row, col;
	int l = 1, r = n;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		cout << "? " << l << " " << mid << " 1 " << n << endl;
		int cnt;
		cin >> cnt;
		if(cnt != mid - l + 1)r = mid;
		else l = mid + 1;
	}
	row = l;
	l = 1, r = n;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		cout << "? 1 " << n << " " << l << " " << mid << endl;
		int cnt;
		cin >> cnt;
		if(cnt != mid - l + 1)r = mid;
		else l = mid + 1;
	}
	col = l;
	cout << "! " << row << " " << col << endl;
	return 0;
}