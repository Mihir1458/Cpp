#include<iostream>
using namespace std;
class empolyee{
    public:
    int id;
    int salary;

    empolyee(){
        cout<<"default constructor called"<<endl;
    }
    empolyee(int inpId, int inpSalary){
        id=inpId;
        salary=inpSalary;
        cout<<"id: "<<id<<endl;
        cout<<"salary: "<<salary<<endl;
    }

};
class feild : public empolyee
{
    public:
    int type; // here we use heritance for difine new type 
    feild(int inpType,int ids,int sal){
        id=ids;
        salary=sal;
        type=inpType; 
        cout<<"id: "<<id<<endl;
        cout<<"salary: "<<salary<<endl;
         cout<<"type: "<<type<<endl;
    }
};
int main()
{
    empolyee n1(2,1500);
    feild n12(6,2,1521);
    cout<<"Id :-"<<n12.id<<endl; // here if i will not declare the type public then it will give error 

}
