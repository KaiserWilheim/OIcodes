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
		int �� = b.find(a);
		int �� = b.find(a), s = 0;
		while(�� != string::npos)
		{
			++s;
			�� = b.find(a, �� + 1);
		}
		cout << s << " " << �� << endl;
	}
	return 0;
}
