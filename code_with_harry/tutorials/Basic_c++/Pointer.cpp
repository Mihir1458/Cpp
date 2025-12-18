#include<iostream>
using namespace std;
int main()
{
    int a=5,*b;
    b=&a;
    //addresh of pointer pointhing
    cout<<"the addhresh it is point is :"<<&a<<endl;
    cout<<"the addhresh it is point is :"<<b<<endl;
   
    //value of pointer pointhing
    cout<<"the value it is point is :"<<a<<endl;
    cout<<"the value it is point is :"<<*b<<endl;
 
    // pointer to poniter
    int **c=&b;

    cout<<"the value it is point is :"<<**c<<endl;
    cout<<"the value it is point is :"<<c<<endl;
    return 0;
 
}