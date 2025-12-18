#include<iostream>
#include <iomanip>
using namespace std;
int main()
{
    int a=8,b=865,c=75555;
    
    cout<<"With Setw output is:"<<a<<endl;
    cout<<"With Setw output is:"<<b<<endl;
    cout<<"With Setw output is:"<<c<<endl;
    
    cout<<"With Setw output is:"<<setw(5)<<a<<endl;
    cout<<"With Setw output is:"<<setw(5)<<b<<endl;
    cout<<"With Setw output is:"<<setw(5)<<c<<endl;
    return 0;
}