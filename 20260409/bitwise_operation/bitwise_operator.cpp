#include<bits/stdc++.h>
using namespace std;

vector<int> to_bin(int num)
{
    vector<int> bitdigis;
    while(num)
    {
        bitdigis.push_back(num%2);
        num/=2;
    }

    return bitdigis;
}

int main(void)
{
    int num1=7,num2=12,result;
    //cin >> num1 >> num2;
    
    cout << "num1:" << num1 << endl;
    cout << "num1:" << bitset<8>(num1) << endl;
     
    cout << "num2:" << num2 << endl;
    cout << "num2:" << bitset<8>(num2) << endl;


    /*NOT*/
    result=~num1;
    cout << "~num1:" << result << endl;
    cout << "~num1:" << bitset<8>(result) << endl;
    result=~num2;
    cout << "~num2:" << result << endl;
    cout << "~num2:" << bitset<8>(result) << endl;


    /*AND*/
    result=num1 & num2;
    cout << "num1 & num2:" << result << endl;
    cout << "num1 & num2:" << bitset<8>(result) << endl;


    /*OR*/
    result=num1 | num2;
    cout << "num1 | num2:" << result << endl;
    cout << "num1 | num2:" << bitset<8>(result) << endl;


    /*XOR*/
    result=num1 ^ num2;
    cout << "num1 ^ num2:" << result << endl;
    cout << "num1 ^ num2:" << bitset<8>(result) << endl;

    /*XNOR*/
    result=~(num1 ^ num2);
    cout << "~(num1 ^ num2):" << result << endl;
    cout << "~(num1 ^ num2):" << bitset<8>(result) << endl;


    
    
    return 0;
}