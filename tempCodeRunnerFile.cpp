#include<iostream>
#include<cmath>
using namespace std;
int NegativeNumberException()
{
    cout<<"Negative number"<<endl;
    return -1;
}
int main()
{
    int a;
    cout <<"Entre the number you want to sqaure root :"<<endl;
    cin>>a;
    try{
        if(a<0)
        {
            throw NegativeNumberException();
        }
        else
        {
            cout<<"The square root of "<<a<<" is "<<sqrt(a)<<endl;
        }
    }
    catch(int e)
    {
        cout<<"Caught an exception: "<<e<<endl;
    }
    return 0;
}