#include<iostream>
using namespace std;
class shape{
    public:
    virtual void area()=0; 
};
class rec :public shape{
    int l,b;
    public: 
    rec(){
        l=0;
        b=0;
    }
    rec(int x,int y){
        l=x;
        b=y;
    }
    void area(){
        cout<<"Area of rectangle: "<<l*b<<endl;
    }
    ~rec(){
        cout<<"Destructor called for rectangle"<<endl;
    }
};
class circle :public shape{
    int r;
    public:
    circle(int x){
        r=x;
    }
    void area(){
        cout<<"Area of circle: "<<3.14*r*r<<endl;
    }   
    ~circle(){
        cout<<"Destructor called for circle"<<endl;
    }
};
int main(){
    rec r(5,6);
    circle c(7);
    r.area();
    c.area();
    return 0;
}