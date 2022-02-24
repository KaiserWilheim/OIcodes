#include <bits/stdc++.h>
using namespace str;
int ans[100010][3];
bool flt[100010];
int ryr[20] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };
int pyr[20] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
void chq(int i, int n)
{
	if((n >= 1) && (n <= 31))
	{
		ans[i][1] = n;
		ans[i][2] = 1;//jan 1
	}
	else if((n >= 32) && (n <= 60))
	{
		ans[i][1] = n - 31;
		ans[i][2] = 2;//feb 1
	}
	else if((n >= 61) && (n <= 91))
	{
		ans[i][1] = n - 60;
		ans[i][2] = 3;//mar 1
	}
	else if((n >= 92) && (n <= 121))
	{
		ans[i][1] = n - 91;
		ans[i][2] = 4;//apr 1
	}
	else if((n >= 122) && (n <= 152))
	{
		ans[i][1] = n - 121;
		ans[i][2] = 5;//may 1
	}
	else if((n >= 153) && (n <= 182))
	{
		ans[i][1] = n - 152;
		ans[i][2] = 6;//jun 1
	}
	else if((n >= 183) && (n <= 213))
	{
		ans[i][1] = n - 182;
		ans[i][2] = 7;//jul 1
	}
	else if((n >= 214) && (n <= 244))
	{
		ans[i][1] = n - 213;
		ans[i][2] = 8;//aug 1
	}
	else if((n >= 245) && (n <= 274))
	{
		ans[i][1] = n - 244;
		ans[i][2] = 9;//sep 1
	}
	else if((n >= 275) && (n <= 305))
	{
		ans[i][1] = n - 274;
		ans[i][2] = 10;//oct 1
	}
	else if((n >= 306) && (n <= 335))
	{
		ans[i][1] = n - 305;
		ans[i][2] = 11;//nov 1
	}
	else if((n >= 336) && (n <= 366))
	{
		ans[i][1] = n - 335;
		ans[i][2] = 12;//dec 1
	}
	else if((n >= 367) && (n <= 397))
	{
		ans[i][1] = n - 366;
		ans[i][2] = 1;//jan 2
		ans[i][3] += 1;
	}
	else if((n >= 398) && (n <= 425))
	{
		ans[i][1] = n - 397;
		ans[i][2] = 2;//feb 2
		ans[i][3] += 1;
	}
	else if((n >= 426) && (n <= 456))
	{
		ans[i][1] = n - 425;
		ans[i][2] = 3;//mar 2
		ans[i][3] += 1;
	}
	else if((n >= 457) && (n <= 486))
	{
		ans[i][1] = n - 456;
		ans[i][2] = 4;//apr 2
		ans[i][3] += 1;
	}
	else if((n >= 487) && (n <= 517))
	{
		ans[i][1] = n - 486;
		ans[i][2] = 5;//may 2
		ans[i][3] += 1;
	}
	else if((n >= 518) && (n <= 547))
	{
		ans[i][1] = n - 517;
		ans[i][2] = 6;//jun 2
		ans[i][3] += 1;
	}
	else if((n >= 548) && (n <= 578))
	{
		ans[i][1] = n - 547;
		ans[i][2] = 7;//jul 2
		ans[i][3] += 1;
	}
	else if((n >= 579) && (n <= 609))
	{
		ans[i][1] = n - 578;
		ans[i][2] = 8;//aug 2
		ans[i][3] += 1;
	}
	else if((n >= 610) && (n <= 639))
	{
		ans[i][1] = n - 609;
		ans[i][2] = 9;//sep 2
		ans[i][3] += 1;
	}
	else if((n >= 640) && (n <= 670))
	{
		ans[i][1] = n - 639;
		ans[i][2] = 10;//oct 2
		ans[i][3] += 1;
	}
	else if((n >= 671) && (n <= 700))
	{
		ans[i][1] = n - 670;
		ans[i][2] = 11;//nov 2
		ans[i][3] += 1;
	}
	else if((n >= 701) && (n <= 731))
	{
		ans[i][1] = n - 700;
		ans[i][2] = 12;//dec 2
		ans[i][3] += 1;
	}
	else if((n >= 732) && (n <= 762))
	{
		ans[i][1] = n - 731;
		ans[i][2] = 1;//jan 3
		ans[i][3] += 2;
	}
	else if((n >= 763) && (n <= 790))
	{
		ans[i][1] = n - 762;
		ans[i][2] = 2;//feb 3
		ans[i][3] += 2;
	}
	else if((n >= 791) && (n <= 821))
	{
		ans[i][1] = n - 790;
		ans[i][2] = 3;//mar 3
		ans[i][3] += 2;
	}
	else if((n >= 822) && (n <= 851))
	{
		ans[i][1] = n - 821;
		ans[i][2] = 4;//apr 3
		ans[i][3] += 2;
	}
	else if((n >= 852) && (n <= 882))
	{
		ans[i][1] = n - 851;
		ans[i][2] = 5;//may 3
		ans[i][3] += 2;
	}
	else if((n >= 883) && (n <= 912))
	{
		ans[i][1] = n - 882;
		ans[i][2] = 6;//jun 3
		ans[i][3] += 2;
	}
	else if((n >= 913) && (n <= 943))
	{
		ans[i][1] = n - 912;
		ans[i][2] = 7;//jul 3
		ans[i][3] += 2;
	}
	else if((n >= 944) && (n <= 974))
	{
		ans[i][1] = n - 943;
		ans[i][2] = 8;//aug 3
		ans[i][3] += 2;
	}
	else if((n >= 975) && (n <= 1004))
	{
		ans[i][1] = n - 974;
		ans[i][2] = 9;//sep 3
		ans[i][3] += 2;
	}
	else if((n >= 1005) && (n <= 1035))
	{
		ans[i][1] = n - 1004;
		ans[i][2] = 10;//oct 3  
		ans[i][3] += 2;
	}
	else if((n >= 1036) && (n <= 1065))
	{
		ans[i][1] = n - 1035;
		ans[i][2] = 11;//nov 3
		ans[i][3] += 2;
	}
	else if((n >= 1066) && (n <= 1096))
	{
		ans[i][1] = n - 1065;
		ans[i][2] = 12;//dec 3
		ans[i][3] += 2;
	}
	else if((n >= 1097) && (n <= 1127))
	{
		ans[i][1] = n - 1096;
		ans[i][2] = 1;//jan 4
		ans[i][3] += 3;
	}
	else if((n >= 1128) && (n <= 1155))
	{
		ans[i][1] = n - 1127;
		ans[i][2] = 2;//feb 4
		ans[i][3] += 3;
	}
	else if((n >= 1156) && (n <= 1186))
	{
		ans[i][1] = n - 1155;
		ans[i][2] = 3;//mar 4
		ans[i][3] += 3;
	}
	else if((n >= 1187) && (n <= 1216))
	{
		ans[i][1] = n - 1186;
		ans[i][2] = 4;//apr 4
		ans[i][3] += 3;
	}
	else if((n >= 1217) && (n <= 1247))
	{
		ans[i][1] = n - 1216;
		ans[i][2] = 5;//may 4
		ans[i][3] += 3;
	}
	else if((n >= 1248) && (n <= 1277))
	{
		ans[i][1] = n - 1247;
		ans[i][2] = 6;//jun 4
		ans[i][3] += 3;
	}
	else if((n >= 1278) && (n <= 1308))
	{
		ans[i][1] = n - 1277;
		ans[i][2] = 7;//jul 4
		ans[i][3] += 3;
	}
	else if((n >= 1309) && (n <= 1339))
	{
		ans[i][1] = n - 1308;
		ans[i][2] = 8;//aug 4
		ans[i][3] += 3;
	}
	else if((n >= 1340) && (n <= 1369))
	{
		ans[i][1] = n - 1339;
		ans[i][2] = 9;//sep 4
		ans[i][3] += 3;
	}
	else if((n >= 1370) && (n <= 1400))
	{
		ans[i][1] = n - 1369;
		ans[i][2] = 10;//oct 4
		ans[i][3] += 3;
	}
	else if((n >= 1401) && (n <= 1430))
	{
		ans[i][1] = n - 1400;
		ans[i][2] = 11;//nov 4
		ans[i][3] += 3;
	}
	else if((n >= 1431) && (n <= 1461))
	{
		ans[i][1] = n - 1430;
		ans[i][2] = 12;//dec 4
		ans[i][3] += 3;
	}
}
int main()
{
	long long Q, n;
	cin >> Q;
	for(int i = 1; i <= Q; i++)
	{
		cin >> n;
		n++;
		ans[i][3] = -4713;
		if(n <= 1721058)
		{
			//区间 BC4713-BC2 开始 
			ans[i][3] += (n / 1461) * 4;
			n = n % 1461;
			if((n >= 1) && (n <= 366))
			{
				flt[i] = false;
			}
			else
			{
				flt[i] = true;
			}
			chq(i, n);
			//区间 BC4713-BC2 结束 

		}
		else if((n > 1721058) && (n <= 2298153))
		{
			//区间 BC1-1579 开始 
			n -= 1721058;
			ans[i][3] = 0;
			ans[i][3] += (n / 1461) * 4;
			n = n % 1461;
			if((n >= 1) && (n <= 366))
			{
				flt[i] = false;
			}
			else
			{
				flt[i] = true;
			}
			chq(i, n);
			if(ans[i][3] == 0)ans[i][3] = -1;
			//区间 BC1-1579 结束 
		}
		else if((n > 2298153) && (n <= 2299604))
		{
			//特判区间 1580-1583 开始
			n -= 2298153;
			ans[i][3] = 1580;
			if((n >= 1) && (n <= 366))
			{
				flt[i] = false;
			}
			else
			{
				flt[i] = true;
			}
			if((n >= 1005) && (n <= 1008))
			{
				ans[i][1] = n - 1004;
				ans[i][2] = 10;//oct 3(normal)
				ans[i][3] += 2;
			}
			else if((n >= 1008) && (n <= 1025))
			{
				ans[i][1] = n - 994;
				ans[i][2] = 10;//oct 3(special)
				ans[i][3] += 2;
			}
			else
			{
				chq(i, n);
			}
			//特判区间 1580-1583 结束 
		}
		else if((n > 2299604) && (n <= 2305448))
		{
			//区间 1584-1599 开始 
			n -= 2299604;
			ans[i][3] = 1584;
			ans[i][3] += (n / 1461) * 4;
			n = n % 1461;
			if((n >= 1) && (n <= 366))
			{
				flt[i] = false;
			}
			else
			{
				flt[i] = true;
			}
			chq(i, n);
			//区间 1584-1599 结束 
		}
		else if(n > 2305448)
		{
			n -= 2305448;
			ans[i][3] = 1600;
			int r = n / 146097;
			n %= 146097;
			ans[i][3] += (r * 400);
			if((n >= 36526) && (n <= 36890) || (n >= 73050) && (n <= 73414) || (n >= 109574) && (n <= 109938))
			{
				flt[i] = true;
				if((n >= 36526) && (n <= 36890))
				{
					n -= 36525;
					ans[i][3] += 100;
				}
				else if((n >= 73050) && (n <= 73414))
				{
					n -= 73049;
					ans[i][3] += 200;
				}
				else if((n >= 109574) && (n <= 109938))
				{
					n -= 109573;
					ans[i][3] += 300;
				}
				if((n >= 1) && (n <= 31))
				{
					ans[i][1] = n;
					ans[i][2] = 1;//jan 1
				}
				else if((n >= 32) && (n <= 59))
				{
					ans[i][1] = n - 31;
					ans[i][2] = 2;//feb 1
				}
				else if((n >= 60) && (n <= 90))
				{
					ans[i][1] = n - 59;
					ans[i][2] = 3;//mar 1
				}
				else if((n >= 91) && (n <= 120))
				{
					ans[i][1] = n - 90;
					ans[i][2] = 4;//apr 1
				}
				else if((n >= 121) && (n <= 151))
				{
					ans[i][1] = n - 120;
					ans[i][2] = 5;//may 1
				}
				else if((n >= 152) && (n <= 181))
				{
					ans[i][1] = n - 151;
					ans[i][2] = 6;//jun 1
				}
				else if((n >= 182) && (n <= 212))
				{
					ans[i][1] = n - 181;
					ans[i][2] = 7;//jul 1
				}
				else if((n >= 213) && (n <= 243))
				{
					ans[i][1] = n - 212;
					ans[i][2] = 8;//aug 1
				}
				else if((n >= 244) && (n <= 273))
				{
					ans[i][1] = n - 243;
					ans[i][2] = 9;//sep 1
				}
				else if((n >= 274) && (n <= 304))
				{
					ans[i][1] = n - 273;
					ans[i][2] = 10;//oct 1
				}
				else if((n >= 305) && (n <= 334))
				{
					ans[i][1] = n - 304;
					ans[i][2] = 11;//nov 1
				}
				else if((n >= 335) && (n <= 365))
				{
					ans[i][1] = n - 334;
					ans[i][2] = 12;//dec 1
				}//平年特判 
			}
			else
			{
				if((n >= 36891) && (n <= 73049))
				{
					n += 1;
				}
				else if((n >= 73415) && (n <= 109573))
				{
					n += 2;
				}
				else if((n >= 109939) && (n <= 146097))
				{
					n += 3;
				}
				ans[i][3] += (n / 1461) * 4;
				n = n % 1461;
				if((n >= 1) && (n <= 366))
				{
					flt[i] = false;
				}
				else
				{
					flt[i] = true;
				}
				chq(i, n);
			}
		}
	}
	for(int i = 1; i <= Q; i++)
	{
		if(ans[i][1] == 0)
		{
			if(ans[i][2] <= 1)
			{
				ans[i][3]--;
				ans[i][2] = 12;
				ans[i][1] = 31;
			}
			else
			{
				ans[i][2]--;
				if(flt[i] == false)
				{
					ans[i][1] = ryr[ans[i][2]];
				}
				else
				{
					ans[i][1] = pyr[ans[i][2]];
				}
			}
		}//防止0月、0日情况的出现 
		if(ans[i][3] < 0)
		{
			cout << ans[i][1] << " " << ans[i][2] << " " << -ans[i][3] << " BC" << endl;
		}
		else if(ans[i][3] > 0)
		{
			cout << ans[i][1] << " " << ans[i][2] << " " << ans[i][3] << endl;
		}
	}
	return 0;
}