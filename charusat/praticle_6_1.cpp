#include<iostream>
using namespace std;

class circle_base{
    protected:
        float radius;
    public:
        circle_base(float r){
            radius = r;
        }
        circle_base(){
            radius = 0.0;
        }

        void input(){
            cout<<"Enter the radius of circle: ";
            cin>>radius;
        }
};

class circle_area: public circle_base{
    protected:
    public:
    void area(){
        cout<<"Area of circle is: "<<3.14*radius*radius<<endl;
    }
};

int main(){
    int n;
    cout<<"Enter the number of circle: ";
    cin>>n;

    circle_area *circle = new circle_area[n];

    for(int i=0; i<n; i++){
        circle[i].input();
    }
    cout<<"------------------------------------------------------"<<endl;
    for(int j=0; j<n; j++){
        cout<<"area  of the circle: ";
        circle[j].area();
    }
    cout<<"------------------------------------------------------"<<endl;
    return 0;
    
}