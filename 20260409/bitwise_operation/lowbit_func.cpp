#include<bits/stdc++.h>
using namespace std;

int lowbit(int num)
{
    return num & (~num+1);
}
int main(void)
{
    int num=32,tnum=num;
    int result=lowbit(num);
    cout << result << endl;

    /*统计数的二进制中有多少个一*/
    int counter=0;
    while(tnum)
    {
        tnum-=lowbit(tnum);
        counter++;
    }
    cout << counter << endl;

    /*判断数是否为2的整数次幂*/
    if(lowbit(num)==num)
    {
        cout << num << ' ' << "is two's integer power." << endl;
    }
    else
    {
        cout << num << ' ' << "is not two's integer power." << endl;
    }

    return 0;
}