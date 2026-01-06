 #include<iostream>
using namespace std;
class compound{
    int principal;
    int years;
    float intrest;
    float final;
    public:
    compound(int p,int y,float r){
        principal=p;
        years=y;
        intrest=r;
        final=principal;
        for(int i=0;i<years;i++){
            final=final+(final*intrest);
        }
    }
    compound(int p,int y,int r){
        principal=p;
        years=y;
        intrest=float(r)/100;
        final=principal;
        for(int i=0;i<years;i++){
            final=final+(final*intrest);
        }
    }
    void display();
};
void compound::display(){
 cout<<endl<<"Principal amount was "<<principal
        << ". Return value after "<<years
        << " years is "<<final<<endl;
}
int main()
{
    int p,y;
    float r1;
    int r2;
    cout<<"Enter principal amount, no of years and rate of intrest in float format: "<<endl;
    cin>>p>>y>>r1;
    compound c1(p,y,r1);
    c1.display();
    cout<<"Enter principal amount, no of years and rate of intrest in integer format: ";
    cin>>p>>y>>r2;
    compound c2(p,y,r2);
    c2.display();
    return 0;
}
