#include<iostream>
using namespace std;
int main()
{
    int s, e, k;
    cin >> s >> e >> k;
    bool flaga = false;
    if(s > e)
    {
        flaga = true;
        swap(s, e);
    }
    bool flagb = false;
    if(s <= k && k < e)flagb = true;
    if(flaga ^ flagb)
    {
        puts("Yes");
    }
    else
    {
        puts("No");
    }
    return 0;
}
