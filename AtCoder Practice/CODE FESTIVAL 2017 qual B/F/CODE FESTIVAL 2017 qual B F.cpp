#include<bits/stdc++.h>
#define ll long long
using namespace std;
multiset<string>s;
int main()
{
	int a, b, c;
	cin >> a >> b >> c;
	while(a--)s.insert("a");
	while(b--)s.insert("b");
	while(c--)s.insert("c");
	while(s.size() > 1)
	{
		string l = *s.begin();
		string r = *s.rbegin();
		s.erase(s.find(l));
		s.erase(s.find(r));
		s.insert(l + r);
	}
	cout << *s.begin() << endl;
	return 0;
}
