#include<iostream>
using namespace std;
int fact(int a);
int main()
{
  // Factorial of a number:
    // 6! = 6*5*4*3*2*1 = 720
    // 0! = 1 by definition
    // 1! = 1 by definition
    // n! = n * (n-1)!
      int a=0,ans;
    cout<<"ENtre number for which do want to find the facorial:- ";
    cin>>a;
    ans=fact(a);
    cout<<ans;
    return 0;
}
int fact(int a){
    if(a<=1)
    {
        return 1;
    }
    return (a)*fact(a-1);
    
     
}