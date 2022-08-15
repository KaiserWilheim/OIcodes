#include<bits/stdc++.h>
using namespace std;
#define ll long long
int base[20][20];
bool isCaptured = false;
bool isInvalid = false;
bool isCheckmate = false;
int side = 0;
int sx, sy, tx, ty;
int knockOut = 0;
void initMap()
{
	memset(base, 0, sizeof(base));
	//1-7 王士象马车鸭卒 红+0 蓝+10
	base[4][0] = 1;
	base[4][9] = 11;
	base[3][0] = base[5][0] = 2;
	base[3][9] = base[5][9] = 12;
	base[2][0] = base[6][0] = 3;
	base[2][9] = base[6][9] = 13;
	base[1][0] = base[7][0] = 4;
	base[1][9] = base[7][9] = 14;
	base[0][0] = base[8][0] = 5;
	base[0][9] = base[8][9] = 15;
	base[0][2] = base[8][2] = 6;
	base[0][7] = base[8][7] = 16;
	base[0][3] = base[2][3] = base[4][3] = base[6][3] = base[8][3] = 7;
	base[0][6] = base[2][6] = base[4][6] = base[6][6] = base[8][6] = 17;
}

void init()
{
	isInvalid = false;
	isCheckmate = false;
	knockOut = 0;
}

void checkOut()
{
	bool flag = false;
	if (sx < 0)flag = true;
	if (sx > 8)flag = true;
	if (sy < 0)flag = true;
	if (sy > 9)flag = true;
	if (tx < 0)flag = true;
	if (tx > 8)flag = true;
	if (ty < 0)flag = true;
	if (ty > 9)flag = true;
	if (flag)
	{
		puts("Invalid command");
		isInvalid = true;
	}
}

void move()
{
	if (base[sx][sy] / 10 != side)
	{
		puts("Invalid command");
		isInvalid = true;
		return;
	}
	else if (base[sx][sy] == 0)
	{
		puts("Invalid command");
		isInvalid = true;
		return;
	}
	else if (base[tx][ty] / 10 == side && base[tx][ty] != 0)
	{
		puts("Invalid command");
		isInvalid = true;
		return;
	}
	int type = base[sx][sy] % 10;
	if (type == 1)
	{
		if (abs(sx - tx) + abs(sy - ty) > 1)
		{
			puts("Invalid command");
			isInvalid = true;
			return;
		}
	}
	else if (type == 2)
	{
		if (abs(sx - tx) != 1 || abs(sy - ty) != 1)
		{
			puts("Invalid command");
			isInvalid = true;
			return;
		}
	}
	else if (type == 3)
	{
		if (abs(sx - tx) != 2 || abs(sy - ty) != 2)
		{
			puts("Invalid command");
			isInvalid = true;
			return;
		}
		if (base[(sx + tx) / 2][(sy + ty) / 2] != 0)
		{
			puts("Invalid command");
			isInvalid = true;
			return;
		}
	}
	else if (type == 4)
	{
		if (!(abs(sx - tx) == 2 && abs(sy - ty) == 1) && !(abs(sx - tx) == 1 && abs(sy - ty) == 2))
		{
			puts("Invalid command");
			isInvalid = true;
			return;
		}
		if (abs(sx - tx) > abs(sy - ty))
		{
			if (base[sx + (tx - sx) / 2][sy] != 0)
			{
				puts("Invalid command");
				isInvalid = true;
				return;
			}
		}
		else
		{
			if (base[sx][sy + (ty - sy) / 2] != 0)
			{
				puts("Invalid command");
				isInvalid = true;
				return;
			}
		}
	}
	else if (type == 5)
	{
		if (sx != tx && sy != ty)
		{
			//if (cnt == 875)printf("4");
			puts("Invalid command");
			isInvalid = true;
			return;
		}
		bool collide = false;
		if (sx != tx)
		{
			int tmpx = min(sx, tx);
			for (int i = tmpx + 1; i < max(sx, tx); i++)
			{
				if (base[i][sy] != 0)
				{
					collide = true;
					break;
				}
			}
		}
		else if (sy != ty)
		{
			int tmpy = min(sy, ty);
			for (int i = tmpy + 1; i < max(sy, ty); i++)
			{
				if (base[sx][i] != 0)
				{
					collide = true;
					break;
				}
			}
		}
		if (collide)
		{
			//if (cnt == 875)printf("5");
			puts("Invalid command");
			isInvalid = true;
			return;
		}
	}
	else if (type == 6)
	{
		if (!(abs(sx - tx) == 3 && abs(sy - ty) == 2) && !(abs(sx - tx) == 2 && abs(sy - ty) == 3))
		{
			//if (cnt == 875)printf("4");
			puts("Invalid command");
			isInvalid = true;
			return;
		}
		int kx = (tx - sx > 0) ? 1 : -1;
		int ky = (ty - sy > 0) ? 1 : -1;
		if (abs(sx - tx) > abs(sy - ty))
		{
			if (base[sx + kx][sy] != 0 || base[sx + 2 * kx][sy + ky] != 0)
			{
				//if (cnt == 875)printf("5");
				puts("Invalid command");
				isInvalid = true;
				return;
			}
		}
		else
		{
			if (base[sx][sy + ky] != 0 || base[sx + kx][sy + 2 * ky] != 0)
			{
				//if (cnt == 875)printf("5");
				puts("Invalid command");
				isInvalid = true;
				return;
			}
		}
	}
	else if (type == 7)
	{
		if (abs(sx - tx) > 1 || abs(sy - ty) > 1)
		{
			//if (cnt == 875)printf("4");
			puts("Invalid command");
			isInvalid = true;
			return;
		}
	}

	knockOut = base[tx][ty];
	base[tx][ty] = base[sx][sy];
	base[sx][sy] = 0;
}

bool checkMate(int k)
{
	int x = 0, y = 0;
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 9; j++)
			if (base[i][j] == (k ^ 1) * 10 + 1)
			{
				x = i;
				y = j;
				break;
			}
	bool flag = false;
	for (int i = x + 1; i <= 8; i++)
	{
		if (base[i][y] == k * 10 + 5)
		{
			flag = true;
			break;
		}
		else if (base[i][y] != 0)break;
	}
	for (int i = x - 1; i >= 0; i--)
	{
		if (base[i][y] == k * 10 + 5)
		{
			flag = true;
			break;
		}
		else if (base[i][y] != 0)break;
	}
	for (int i = y + 1; i <= 9; i++)
	{
		if (base[x][i] == k * 10 + 5)
		{
			flag = true;
			break;
		}
		else if (base[x][i] != 0)break;
	}
	for (int i = y - 1; i >= 0; i--)
	{
		if (base[x][i] == k * 10 + 5)
		{
			flag = true;
			break;
		}
		else if (base[x][i] != 0)break;
	}
	if (flag)return flag;
	if (x <= 7 && base[x + 1][y] == k * 10 + 1)flag = true;
	if (y <= 8 && base[x][y + 1] == k * 10 + 1)flag = true;
	if (x >= 1 && base[x - 1][y] == k * 10 + 1)flag = true;
	if (y >= 1 && base[x][y - 1] == k * 10 + 1)flag = true;
	if (flag)return flag;
	if (x <= 7 && y <= 8 && base[x + 1][y + 1] == k * 10 + 2)flag = true;
	if (x >= 1 && y <= 8 && base[x - 1][y + 1] == k * 10 + 2)flag = true;
	if (x <= 7 && y >= 1 && base[x + 1][y - 1] == k * 10 + 2)flag = true;
	if (x >= 1 && y >= 1 && base[x - 1][y - 1] == k * 10 + 2)flag = true;
	if (flag)return flag;
	if (x <= 7 && y <= 8 && base[x + 1][y + 1] == k * 10 + 7)flag = true;
	if (x >= 1 && y <= 8 && base[x - 1][y + 1] == k * 10 + 7)flag = true;
	if (x <= 7 && y >= 1 && base[x + 1][y - 1] == k * 10 + 7)flag = true;
	if (x >= 1 && y >= 1 && base[x - 1][y - 1] == k * 10 + 7)flag = true;
	if (x <= 7 && base[x + 1][y] == k * 10 + 7)flag = true;
	if (y <= 8 && base[x - 1][y] == k * 10 + 7)flag = true;
	if (x >= 1 && base[x][y + 1] == k * 10 + 7)flag = true;
	if (y >= 1 && base[x][y - 1] == k * 10 + 7)flag = true;
	if (flag)return flag;
	if (x <= 6 && y <= 8 && base[x + 2][y + 1] == k * 10 + 4 && base[x + 1][y + 1] == 0)flag = true;
	if (x >= 2 && y <= 8 && base[x - 2][y + 1] == k * 10 + 4 && base[x - 1][y + 1] == 0)flag = true;
	if (x <= 6 && y >= 1 && base[x + 2][y - 1] == k * 10 + 4 && base[x + 1][y - 1] == 0)flag = true;
	if (x >= 2 && y >= 1 && base[x - 2][y - 1] == k * 10 + 4 && base[x - 1][y - 1] == 0)flag = true;
	if (x <= 7 && y <= 7 && base[x + 1][y + 2] == k * 10 + 4 && base[x + 1][y + 1] == 0)flag = true;
	if (x >= 1 && y <= 7 && base[x - 1][y + 2] == k * 10 + 4 && base[x - 1][y + 1] == 0)flag = true;
	if (x <= 7 && y >= 2 && base[x + 1][y - 2] == k * 10 + 4 && base[x + 1][y - 1] == 0)flag = true;
	if (x >= 1 && y >= 2 && base[x - 1][y - 2] == k * 10 + 4 && base[x - 1][y - 1] == 0)flag = true;
	if (flag)return flag;
	if (x <= 6 && y <= 7 && base[x + 2][y + 2] == k * 10 + 3 && base[x + 1][y + 1] == 0)flag = true;
	if (x >= 2 && y <= 7 && base[x - 2][y + 2] == k * 10 + 3 && base[x - 1][y + 1] == 0)flag = true;
	if (x <= 6 && y >= 2 && base[x + 2][y - 2] == k * 10 + 3 && base[x + 1][y - 1] == 0)flag = true;
	if (x >= 2 && y >= 2 && base[x - 2][y - 2] == k * 10 + 3 && base[x - 1][y - 1] == 0)flag = true;
	if (flag)return flag;
	if (x <= 5 && y <= 7 && base[x + 3][y + 2] == k * 10 + 6 && base[x + 1][y + 1] == 0 && base[x + 2][y + 2] == 0)flag = true;
	if (x >= 3 && y <= 7 && base[x - 3][y + 2] == k * 10 + 6 && base[x - 1][y + 1] == 0 && base[x - 2][y + 2] == 0)flag = true;
	if (x <= 5 && y >= 2 && base[x + 3][y - 2] == k * 10 + 6 && base[x + 1][y - 1] == 0 && base[x + 2][y - 2] == 0)flag = true;
	if (x >= 3 && y >= 2 && base[x - 3][y - 2] == k * 10 + 6 && base[x - 1][y - 1] == 0 && base[x - 2][y - 2] == 0)flag = true;
	if (x <= 6 && y <= 6 && base[x + 2][y + 3] == k * 10 + 6 && base[x + 1][y + 1] == 0 && base[x + 2][y + 2] == 0)flag = true;
	if (x >= 2 && y <= 6 && base[x - 2][y + 3] == k * 10 + 6 && base[x - 1][y + 1] == 0 && base[x - 2][y + 2] == 0)flag = true;
	if (x <= 6 && y >= 3 && base[x + 2][y - 3] == k * 10 + 6 && base[x + 1][y - 1] == 0 && base[x + 2][y - 2] == 0)flag = true;
	if (x >= 2 && y >= 3 && base[x - 2][y - 3] == k * 10 + 6 && base[x - 1][y - 1] == 0 && base[x - 2][y - 2] == 0)flag = true;
	return flag;
}

void write()
{
	switch (base[tx][ty])
	{
		case 1: { printf("red captain;"); break; }
		case 2: { printf("red guard;"); break; }
		case 3: { printf("red elephant;"); break; }
		case 4: { printf("red horse;"); break; }
		case 5: { printf("red car;"); break; }
		case 6: { printf("red duck;"); break; }
		case 7: { printf("red soldier;"); break; }
		case 11: { printf("blue captain;"); break; }
		case 12: { printf("blue guard;"); break; }
		case 13: { printf("blue elephant;"); break; }
		case 14: { printf("blue horse;"); break; }
		case 15: { printf("blue car;"); break; }
		case 16: { printf("blue duck;"); break; }
		case 17: { printf("blue soldier;"); break; }
	}
	switch (knockOut)
	{
		case 0: { printf("NA;"); break; }
		case 1: { printf("red captain;"); break; }
		case 2: { printf("red guard;"); break; }
		case 3: { printf("red elephant;"); break; }
		case 4: { printf("red horse;"); break; }
		case 5: { printf("red car;"); break; }
		case 6: { printf("red duck;"); break; }
		case 7: { printf("red soldier;"); break; }
		case 11: { printf("blue captain;"); break; }
		case 12: { printf("blue guard;"); break; }
		case 13: { printf("blue elephant;"); break; }
		case 14: { printf("blue horse;"); break; }
		case 15: { printf("blue car;"); break; }
		case 16: { printf("blue duck;"); break; }
		case 17: { printf("blue soldier;"); break; }
	}
	if (knockOut == 1 || knockOut == 11)isCaptured = true;
	if (!isCaptured && isCheckmate)printf("yes;");
	else printf("no;");
	if (isCaptured)printf("yes\n");
	else printf("no\n");
}

int main()
{
	initMap();
	int Q;
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++)
	{
		init();
		scanf("%d%d%d%d", &sy, &sx, &ty, &tx);
		if (isCaptured)
		{
			puts("Invalid command");
			continue;
		}
		checkOut();
		move();
		if (isInvalid)continue;
		isCheckmate = checkMate(0) || checkMate(1);
		write();
		side ^= 1;
	}
	return 0;
}