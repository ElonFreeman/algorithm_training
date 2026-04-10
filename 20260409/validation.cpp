#include<bits/stdc++.h>
using namespace std;

vector<int> generan_testset(int testscale)
{
    random_device rdnum;
    mt19937 gen(rdnum());
    uniform_int_distribution<> dis(1,10000);

    vector<int> testset(testscale);
    for(int i=0;i<testscale;i++)
    {
        testset[i]=dis(gen);
    }

    return testset;
}

vector<int> select_sort(vector<int> testset)
{
    for(int i=0;i<size(testset);i++)
    {
        int minindex=i;
        for(int j=i+1;j<size(testset);j++)
        {
            if(testset[j]<testset[minindex])
            {
                minindex=j;
            }
        }

        if(minindex!=i)
        {
            /*int tmp=testset[i];
            testset[i]=testset[minindex];
            testset[minindex]=tmp;*/

            testset[i]=testset[i]^testset[minindex];
            testset[minindex]=testset[i]^testset[minindex];
            testset[i]=testset[i]^testset[minindex];

            /*testset[i]=testset[i]+testset[minindex];
            testset[minindex]=testset[i]-testset[minindex];
            testset[i]=testset[i]-testset[minindex];*/
        }
        
    }

    return testset;
}

vector<int> algo_check(vector<int> testset)
{
    sort(testset.begin(),testset.end(),[](int a,int b){return a<b;});
    return testset;
}

bool compare(vector<int> resultest,vector<int> resultcheck)
{
    for(int i=0;i<size(resultest);i++)
    {
        if(resultest[i]!=resultcheck[i])
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    long long int testscale,testtimes; 
    cout << "testscale:";cin >> testscale;
    cout << "testtimes:";cin >> testtimes;
    cout << endl;

    for(int i=1;i<=testtimes;i++)
    {
        vector<int> testset=generan_testset(testscale);
        vector<int> resultest=select_sort(testset);
        vector<int> resultcheck=algo_check(testset);
        bool correctornot=compare(resultest,resultcheck);

        if(!correctornot)
        {
            cout << "Somthing wrong!" << endl;
            for(int output:testset)
            {
                cout << output << ' ';
            }
            cout << endl;
            for(int output:resultest)
            {
                cout << output << ' ';
            }
            cout << endl;
            for(int output:resultcheck)
            {
                cout << output << ' ';
            }
            cout << endl;
        }
        
        if(i%1000==0)
        {
            cout <<"\r" << i << "test completed." << flush;
        }


    }

    return 0;
}