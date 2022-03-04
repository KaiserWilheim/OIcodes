#include <cstdio>
#define ll long long
const int N = 500010;
int n;
ll q[N], w[N];
ll merge_sort(int l, int r)
{
    if (l == r) return 0;
    int mid = l + r >> 1;
    ll res = merge_sort(l, mid) + merge_sort(mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
        if (q[i] <= q[j]) w[k ++ ] = q[i ++ ];
        else
        {
            res += mid - i + 1;
            w[k ++ ] = q[j ++ ];
        }
    while (i <= mid) w[k ++ ] = q[i ++ ];
    while (j <= r) w[k ++ ] = q[j ++ ];
    for (i = l, j = 0; i <= r; i ++, j ++ ) q[i] = w[j];
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%d", &q[i]);
    printf("%lld\n", merge_sort(0, n - 1));
    return 0;
}
