#include<bits/stdc++.h>
using namespace std;
char c[260];
int main()
{
    int len, i, j, s;
    scanf("%s%d", &c, &s);
    len = strlen(c);
    while(s--)
    {
        for(i = 0; i <= len - 2; i++)
        {
            if(c[i] > c[i + 1])
            {
                for(j = i; j <= len - 2; j++)
                    c[j] = c[j + 1];
                break;
            }
        }
        len--;
    }
    i = 0;
    while(i <= len - 1 && c[i] == '0')i++;
    if(i == len)
    {
        printf("0");
    }
    else
    {
        for(j = i; j <= len - 1; j++)
        {
            printf("%c", c[j]);
        }
    }
    return 0;
}
