#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
const int N = 55;
int n, m;
PII q[N];
int ans;
int calc()
{
    int res = 0;
    for(int i = 0; i < m; i++)
    {
        res += q[i].first + q[i].second;
        if(i < n)
        {
            if(q[i].first == 10) res += q[i + 1].first + q[i + 1].second;
            else if(q[i].first + q[i].second == 10)
                res += q[i + 1].first;
        }
    }
    ans = max(ans, res);
    return res;
}
void simulate_anneal()
{
    for(double t = 1e4; t > 1e-4; t *= 0.99)
    {
        int a = rand() % m, b = rand() % m;
        int x = calc();
        swap(q[a], q[b]);
        if(n + (q[n - 1].first == 10) == m)
        {
            int y = calc();
            int delta = y - x;
            if(exp(delta / t) < ( double )rand() / RAND_MAX)
                swap(q[a], q[b]);
        }
        else swap(q[a], q[b]);
    }
}
int main()
{
    cin >> n;
    for(int i = 0; i < n; i++) cin >> q[i].first >> q[i].second;
    if(q[n - 1].first == 10) m = n + 1, cin >> q[n].first >> q[n].second;
    else m = n;

    for(int i = 0; i < 100; i++) simulate_anneal();

    cout << ans << endl;
    return 0;
}
