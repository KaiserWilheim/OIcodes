#include<bits/stdc++.h>
using namespace std;
int tot = 0;
map<vector<int>, int>dic;
void init();
int main()
{
	init();
	string s;
	cin >> s;
	vector<int>t;
	for(int i = 0; i < s.size(); i++)t.push_back(s[i] - 'a' + 1);
	cout << (*(dic.find(t))).second << endl;
}

void init()
{
	for(int i = 1; i <= 26; i++)
	{
		vector<int>t;
		t.push_back(i);
		dic.insert(make_pair(t, ++tot));
	}
	for(int i = 1; i <= 26; i++)
	{
		for(int j = i + 1; j <= 26; j++)
		{
			vector<int>t;
			t.push_back(i), t.push_back(j);
			dic.insert(make_pair(t, ++tot));
		}
	}
	for(int i = 1; i <= 26; i++)
	{
		for(int j = i + 1; j <= 26; j++)
		{
			for(int k = j + 1; k <= 26; k++)
			{
				vector<int>t;
				t.push_back(i), t.push_back(j), t.push_back(k);
				dic.insert(make_pair(t, ++tot));
			}
		}
	}
	for(int i = 1; i <= 26; i++)
	{
		for(int j = i + 1; j <= 26; j++)
		{
			for(int k = j + 1; k <= 26; k++)
			{
				for(int l = k + 1; l <= 26; l++)
				{
					vector<int>t;
					t.push_back(i), t.push_back(j), t.push_back(k), t.push_back(l);
					dic.insert(make_pair(t, ++tot));
				}
			}
		}
	}
	for(int i = 1; i <= 26; i++)
	{
		for(int j = i + 1; j <= 26; j++)
		{
			for(int k = j + 1; k <= 26; k++)
			{
				for(int l = k + 1; l <= 26; l++)
				{
					for(int m = l + 1; m <= 26; m++)
					{
						vector<int>t;
						t.push_back(i), t.push_back(j), t.push_back(k), t.push_back(l), t.push_back(m);
						dic.insert(make_pair(t, ++tot));
					}
				}
			}
		}
	}
	for(int i = 1; i <= 26; i++)
	{
		for(int j = i + 1; j <= 26; j++)
		{
			for(int k = j + 1; k <= 26; k++)
			{
				for(int l = k + 1; l <= 26; l++)
				{
					for(int m = l + 1; m <= 26; m++)
					{
						for(int n = m + 1; n <= 26; n++)
						{
							vector<int>t;
							t.push_back(i), t.push_back(j), t.push_back(k), t.push_back(l), t.push_back(m), t.push_back(n);
							dic.insert(make_pair(t, ++tot));
						}
					}
				}
			}
		}
	}
}
