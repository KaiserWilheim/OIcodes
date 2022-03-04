#include<bits/stdc++.h>
using namespace std;
stack<int>q;
int num[10001], n, c, in = 0, whe = 1, i, m = 0;
int main()
{
    cin >> n >> c;
    for(i = 1; i <= n; i++)
    {
        scanf("%d", &num[i]);
    }
    while((q.size() + m) < n)
    {
        in = q.size();
        int minn = 0x7fffffff, wher = whe, len = c - in;
        for(i = wher; (i < wher + len) && (i <= n); i++)
            if(num[i] < minn)
            {
                whe = i;
                minn = num[i];
            }
        if((q.empty()) || (minn <= q.top()))
        {
            for(int i = wher; i <= whe; i++) q.push(num[i]); 
            ++whe;
        }
        else 
        {
            whe = wher;
        }
        cout << q.top() << ' ';
        m++;
        q.pop();
    }
    while(!q.empty())
    {
        cout << q.top() << ' ';
        m++;
        q.pop();
    }
    return 0;
}
