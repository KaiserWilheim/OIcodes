#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 10010;
int chq(int h, int d)
{
	if(h == -2)
	{
		if(d == 1)return -3;
	}
	else if(h == -1)
	{
		if(d == 1)return -2;
		else if(d == 2)return -3;
	}
	else if(h == 0)
	{
		if(d == 1)return 0;
		else if(d == 2)return -2;
	}
	else if(h == 1)
	{
		if(d == 1)return 2;
		else if(d == 2)return -1;
		else if(d == 3)return -3;
	}
	else if(h == 2)
	{
		if(d == 1)return 3;
		else if(d == 2)return 1;
		else if(d == 3)return -2;
	}
	else if(h == 3)
	{
		if(d == 2)return 2;
		else if(d == 3)return -1;
		else if(d == 4)return -3;
	}
	else if(h == 4)
	{
		if(d == 2)return 3;
		else if(d == 3)return 1;
		else if(d == 4)return -2;
	}
	else if(h == 5)
	{
		if(d == 3)return 2;
		else if(d == 4)return 0;
		else if(d == 5)return -3;
	}
	else if(h == 6)
	{
		if(d == 3)return 3;
		else if(d == 4)return 2;
		else if(d == 5)return -2;
		else if(d == 6)return -3;
	}
	else if(h == 7)
	{
		if(d == 4)return 3;
		else if(d == 5)return 0;
		else if(d == 6)return -2;
	}
	else if(h == 8)
	{
		if(d == 5)return 2;
		else if(d == 6)return -1;
		else if(d == 7)return -3;
	}
	else if(h == 9)
	{
		if(d == 5)return 3;
		else if(d == 6)return 1;
		else if(d == 7)return -2;
	}
	else if(h == 10)
	{
		if(d == 6)return 2;
		else if(d == 7)return -1;
		else if(d == 8)return -3;
	}
	else if(h == 11)
	{
		if(d == 6)return 3;
		else if(d == 7)return 1;
		else if(d == 8)return -2;
	}
	else if(h == 12)
	{
		if(d == 7)return 2;
		else if(d == 8)return 0;
	}
	else if(h == 13)
	{
		if(d == 7)return 3;
		else if(d == 8)return 2;
	}
	else if(h == 14)
	{
		if(d == 8)return 3;
	}
	return 4;
}
char x[10] = { '{','[','<','@','>',']','}' };
void solve(char *s)
{
	int idx = 0;
	ll n1 = 0, n2 = 0, m1 = 0, m2 = 0;
	int d1 = 0, d2 = 0, f1 = 1, f2 = 1;
	int nr = 0, mr = 0, dr = 0;

	if(s[idx] >= 'A' && s[idx] <= 'G')
	{
		n1 = s[idx] - 'A' + 1;
		idx++;
	}
	else
	{
		puts("Compile Error");
		return;
	}

	if(s[idx] == 'b')
	{
		d1 = -1;
		idx++;
	}
	else if(s[idx] == '#')
	{
		d1 = 1;
		idx++;
	}
	else if(s[idx] == '-')
	{
		f1 = -1;
		idx++;
	}
	else if(!(s[idx] >= '0' && s[idx] <= '9'))
	{
		puts("Compile Error");
		return;
	}

	if(s[idx] == '-')
	{
		if(f1 == -1)
		{
			puts("Compile Error");
			return;
		}
		f1 = -1;
		idx++;
	}

	if(!(s[idx] >= '0' && s[idx] <= '9'))
	{
		puts("Compile Error");
		return;
	}

	while(s[idx] >= '0' && s[idx] <= '9')
	{
		if(m1 == 0 && s[idx - 1] == '0')
		{
			puts("Compile Error");
			return;
		}
		if(m1 >= 1000000000)
		{
			puts("Compile Error");
			return;
		}
		m1 = (m1 * 10) + (s[idx] - '0');
		idx++;
	}

	if(m1 >= 1000000000)
	{
		puts("Compile Error");
		return;
	}

	if(s[idx] != '-')
	{
		puts("Compile Error");
		return;
	}
	else idx++;

	if(s[idx] >= 'A' && s[idx] <= 'G')
	{
		n2 = s[idx] - 'A' + 1;
		idx++;
	}
	else
	{
		puts("Compile Error");
		return;
	}

	if(s[idx] == 'b')
	{
		d2 = -1;
		idx++;
	}
	else if(s[idx] == '#')
	{
		d2 = 1;
		idx++;
	}
	else if(s[idx] >= '0' && s[idx] <= '9') {}
	else if(s[idx] == '-')
	{
		f2 = -1;
		idx++;
	}
	else
	{
		puts("Compile Error");
		return;
	}

	if(s[idx] == '-')
	{
		if(f2 == -1)
		{
			puts("Compile Error");
			return;
		}
		f2 = -1;
		idx++;
	}

	if(!isdigit(s[idx]))
	{
		puts("Compile Error");
		return;
	}

	while(isdigit(s[idx]))
	{
		if(m2 == 0 && s[idx - 1] == '0')
		{
			puts("Compile Error");
			return;
		}
		if(m2 >= 1000000000)
		{
			puts("Compile Error");
			return;
		}
		m2 = (m2 * 10) + (s[idx] - 48);
		idx++;
	}

	if(m2 >= 1000000000)
	{
		puts("Compile Error");
		return;
	}

	if(s[idx] != '=')
	{
		puts("Compile Error");
		return;
	}
	else idx++;

	if(s[idx] == '+')
	{
		nr = 1;
		idx++;
	}
	else if(s[idx] == '-')
	{
		nr = -1;
		idx++;
	}
	else
	{
		puts("Compile Error");
		return;
	}

	if(s[idx] == '@')
	{
		dr = 0;
		idx++;
	}
	else if(s[idx] == '>')
	{
		dr = 1;
		idx++;
	}
	else if(s[idx] == '<')
	{
		dr = -1;
		idx++;
	}
	else if(s[idx] == '[')
	{
		dr = -2;
		idx++;
	}
	else if(s[idx] == ']')
	{
		dr = 2;
		idx++;
	}
	else if(s[idx] == '{')
	{
		dr = -3;
		idx++;
	}
	else if(s[idx] == '}')
	{
		dr = 3;
		idx++;
	}
	else
	{
		puts("Compile Error");
		return;
	}

	if(s[idx] >= '1' && s[idx] <= '8')
	{
		mr = s[idx] - '0';
		idx++;
	}
	else
	{
		puts("Compile Error");
		return;
	}

	if(idx < strlen(s))
	{
		puts("Compile Error");
		return;
	}

	if(f1 == -1 && m1 == 0)
	{
		puts("Compile Error");
		return;
	}
	if(f2 == -1 && m2 == 0)
	{
		puts("Compile Error");
		return;
	}

	if(dr == 0 && (mr == 2 || mr == 3 || mr == 6 || mr == 7))
	{
		puts("Compile Error");
		return;
	}
	if((dr == 1 || dr == -1) && (mr == 1 || mr == 4 || mr == 5 || mr == 8))
	{
		puts("Compile Error");
		return;
	}

	m1 *= f1;
	m2 *= f2;
	//cout << m1 << " " << m2 << " " << ((d1 == -1) ? "b" : (d1 == 1 ? "#" : "")) << n1 << " " << ((d2 == -1) ? "b" : (d2 == 1 ? "#" : "")) << n2 << " ";

	if(abs(m1 - m2) >= 2)
	{
		puts("Compile Error");
		return;
	}

	if(m1 < m2 && n1 < n2)
	{
		puts("Compile Error");
		return;
	}
	else if(m1 > m2 && n1 > n2)
	{
		puts("Compile Error");
		return;
	}

	int flag = 0;
	if(m1 < m2)flag = 1;
	else if(m1 > m2)flag = -1;
	else
	{
		if(n1 < n2)flag = 1;
		else if(n1 > n2)flag = -1;
	}

	bool isRight = true;
	int nd, dd;

	if(flag == 1)
	{
		nd = n2 - n1 + 7 * (m2 - m1) + 1;
		dd = nd * 2 + d2 - d1 - 2;
		if(n1 < n2)
		{
			if(n1 <= 2 && n2 >= 3)dd--;
			if(n1 <= 5 && n2 >= 6)dd--;
		}
		else if(n1 >= n2)
		{
			if(n1 <= 5)dd--;
			if(n1 <= 2)dd--;
			if(n2 >= 3)dd--;
			if(n2 >= 6)dd--;
		}
		if(nr != flag)
		{
			isRight = false;
			goto end;
		}
		if(nd != mr)
		{
			isRight = false;
			goto end;
		}
		if(dr != chq(dd, nd))
		{
			isRight = false;
			goto end;
		}
	}
	else if(flag == -1)
	{
		nd = n1 - n2 + 7 * (m1 - m2) + 1;
		dd = nd * 2 + d1 - d2 - 2;
		if(n2 < n1)
		{
			if(n2 <= 2 && n1 >= 3)dd--;
			if(n2 <= 5 && n1 >= 6)dd--;
		}
		else if(n2 >= n1)
		{
			if(n2 <= 2)dd--;
			if(n2 <= 5)dd--;
			if(n1 >= 3)dd--;
			if(n1 >= 6)dd--;
		}
		if(nr != flag)
		{
			isRight = false;
			goto end;
		}
		if(nd != mr)
		{
			isRight = false;
			goto end;
		}
		if(dr != chq(dd, nd))
		{
			isRight = false;
			goto end;
		}
	}
	else
	{
		nd = 1;
		dd = d2 - d1;
		if(nr != 1)
		{
			isRight = false;
			goto end;
		}
		if(mr != 1)
		{
			isRight = false;
			goto end;
		}
		if(dr != chq(dd, nd))
		{
			isRight = false;
			goto end;
		}
	}

	end:;
	//cout << nd << " " << dd << " ";
	if(isRight)
	{
		puts("Accepted");
	}
	else
	{
		char a = (flag == -1 ? '-' : '+');
		int b = chq(dd, nd) + 3;
		char c = ('0' + nd);
		if(b == 7)printf("Wrong Answer,excepted %c%c\n", a, c);
		else printf("Wrong Answer,excepted %c%c%c\n", a, x[b], c);
	}
}
int main()
{
	const char endl = '\n';
	char s[N];
	while(scanf("%s", s) != EOF)
	{
		solve(s);
	}
	return 0;
}