#include <bits/stdc++.h>
using namespace std;
int votes[110];
string names[110];
int idx = 0;
map<string, int>dic;
int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        if(dic.count(s) == 1)
        {
            votes[(*dic.find(s)).second]++;
        }
        else
        {
            dic.insert(make_pair(s, ++idx));
            names[idx] = s;
            votes[idx]++;
        }
    }
    int maxn = 0;
    for(int i = 1; i <= idx; i++)
    {
        if(votes[i] > votes[maxn])maxn = i;
    }
    cout << names[maxn] << endl;
    return 0;
}
