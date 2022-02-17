#include <iostream>
#include <string>
using namespace std;
int main()
{
	string a;
	string b;
	getline(cin, a);
	getline(cin, b);
	for(int i = 0; i < a.length(); ++i)a[i] = tolower(a[i]);
	for(int i = 0; i < b.length(); ++i)b[i] = tolower(b[i]);
	a = ' ' + a + ' ';
	b = ' ' + b + ' ';
	if(b.find(a) == string::npos)
	{
		cout << -1 << endl;
	}
	else
	{
		int ¦Á = b.find(a);
		int ¦Â = b.find(a), s = 0;
		while(¦Â != string::npos)
		{
			++s;
			¦Â = b.find(a, ¦Â + 1);
		}
		cout << s << " " << ¦Á << endl;
	}
	return 0;
}
