#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <unordered_map>
using namespace std;
const int N = 1000010;
int xlcd;
unordered_map <int, int> fw;
int ys[N];
int main()
{
	int csds;
	scanf("%d", &csds);
	while(csds--)
	{
		scanf("%d", &xlcd);
		fw.clear();
		int jg = -1;
		for(int i = 1; i <= xlcd; ++i)
		{
			scanf("%d", &ys[i]);
			if(fw[ys[i]])
			{
				jg = max(jg, fw[ys[i]] + xlcd - i);
			}
			fw[ys[i]] = i;
		}
		printf("%d\n", jg);
	}
	return 0;
}
