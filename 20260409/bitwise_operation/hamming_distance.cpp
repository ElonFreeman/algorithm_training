#include<bits/stdc++.h>
using namespace std;

int lowbit(int num)
{
    return num & (~num+1);
}

/*汉明距离（Hamming Distance） 是指两个等长字符串之间对应位置不同字符的个数*/

int main(void)
{
    int num1=14,num2=17,XOR=num1 ^ num2,counter=0;

    while(XOR)
    {
        XOR=XOR-lowbit(XOR);
        counter++;
    }

    cout << "Hamming distance is " << counter;

    return 0;
}