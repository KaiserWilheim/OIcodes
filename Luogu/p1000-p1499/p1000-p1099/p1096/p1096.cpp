#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;
int num[210];

void mul(int k)
{
	for(int i = 1; i <= num[0]; i++)num[i] *= k;
	for(int i = 1; i <= num[0]; i++)
	{
		if(num[i] > 9)
		{
			num[i + 1]++;
			num[i] -= 10;
		}
		if(num[num[0] + 1] != 0)num[0]++;
	}
}

int main()
{
	int n;
	cin >> n;
	num[1] = 1, num[0] = 1;
	for(int i = 0; i <= n; i++)mul(2);
	num[1] -= 2;
	for(int i = 1; i <= num[0]; i++)
	{
		if(num[i] < 0)
		{
			num[i] += 10;
			num[i + 1]--;
		}
		if(num[num[0]] == 0)num[0]--;
	}
	for(int i = num[0]; i >= 1; i--)printf("%d", num[i]);
	putchar('\n');
	return 0;
}

