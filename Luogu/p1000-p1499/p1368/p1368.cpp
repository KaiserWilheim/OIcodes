#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;
int n, ans;
int a[N];

int get_ans()
{
	int i = 0, j = 1, k = 0;
	while((i < n) && (j < n) && (k < n))
	{
		if(a[(i + k) % n] == a[(k + j) % n])
		{
			k++;
		}
		else
		{
			if(a[(i + k) % n] > a[(j + k) % n])i += k + 1;
			else j += k + 1;
			if(i == j)i++;
			k = 0;
		}
	}
	return min(i, j);
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)scanf("%d", &a[i - 1]);
	ans = get_ans();
	for(int i = 1; i <= n; i++)printf("%d ", a[(ans + i - 1) % n]);
	return 0;
}
