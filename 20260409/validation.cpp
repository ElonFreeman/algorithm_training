#include<bits/stdc++.h>
using namespace std;

vector<int> generan_testset(int testscale)
{
    random_device rdnum;
    mt19937 gen(rdnum());
    uniform_int_distribution<> dis(1,1000);

    vector<int> testset(testscale);
    for(int i=0;i<testscale;i++)
    {
        testset[i]=dis(gen);
    }

    return testset;
}

vector<int> select_sort(vector<int> testset)
{
    for(int i=0;i<size(testset)-1;i++)
    {
        int min=testset[i];
        for(int j=i+1;j<size(testset);j++)
        {
            if(testset[i+1]>min)
            {
                min=testset[j];
            }
        }

        testset[i]=testset[i]^min;
        min=testset[i]^min;
        testset[i]=testset[i]^min;
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
    long long int testscale,testtimes; cin >> testscale >> testtimes;

    for(int i=0;i<testtimes;i++)
    {
        vector<int> testset=generan_testset(testscale);
        vector<int> resultest=select_sort(testset);
        vector<int> resultcheck=algo_check(testset);
        bool correctornot=compare(resultest,resultcheck);

        if(!correctornot)
        {
            cout << "Somthing wrong!" << endl;

        }
        

        if(i%1000==0)
        {
            cout << i << "test completed." << endl;
        }


    }

    return 0;
}