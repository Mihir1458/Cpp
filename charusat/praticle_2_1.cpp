#include<iostream>
using namespace std;

class RectangleManagementSystem{
private:
    double length;
    double breadth;

public:
    RectangleManagementSystem():length(0),breadth(0){}
    RectangleManagementSystem(double l, double b):length(l),breadth(b){}

    void input();
    void display();
    double area();
    double perimeter();
};

double RectangleManagementSystem::area(){
    if(length>0 && breadth>0){
        cout<<"The rectangle is valid."<<endl;
        return length*breadth;
    }
    else{
        cout<<"The rectangle is invalid."<<endl;
        return 0;
    }
}

double RectangleManagementSystem::perimeter(){
    if(length>0 && breadth>0){
        cout<<"The rectangle is valid."<<endl;
        return 2*(length+breadth);
    }
    else{
        cout<<"The rectangle is invalid."<<endl;
        return 0;
    }
}

void RectangleManagementSystem::input(){
    cout<<"Enter the length of the rectangle: ";
    cin>>length;
    cout<<"Enter the breadth of the rectangle: ";
    cin>>breadth;

    if(length>0 && breadth>0){
        cout<<"The rectangle is valid."<<endl;
    }
    else{
        cout<<"The rectangle is invalid."<<endl;
    }
}

void RectangleManagementSystem::display(){
    cout<<"*******************************************************"<<endl;
    cout<<"The rectangle details are: "<<endl;
    cout<<"The length of the rectangle is: "<<length<<endl;
    cout<<"The breadth of the rectangle is: "<<breadth<<endl;
}

int main(){
    int n;
    cout<<"Enter the number of rectangles: ";
    cin>>n;

    // ✅ Dynamic array
    RectangleManagementSystem* R = new RectangleManagementSystem[n];

    int choice;

    cout<<"Welcome to the Rectangle Management System!"<<endl;

    do{
        cout<<"Enter your choice (1-4): "<<endl;
        cout<<"1. Input rectangle details"<<endl;
        cout<<"2. Display rectangle details"<<endl;
        cout<<"3. Calculate area and perimeter"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                for(int i=0; i<n; i++){
                    cout<<"Rectangle "<<i+1<<":"<<endl;
                    R[i].input();
                    cout<<"*******************************************************"<<endl;
                }
                break;

            case 2:
                for(int i=0; i<n; i++){
                    cout<<"Rectangle "<<i+1<<":"<<endl;
                    R[i].display();
                }
                break;

            case 3:
                for(int i=0; i<n; i++){
                    cout<<"Rectangle "<<i+1<<":"<<endl;
                    cout<<"Area: "<<R[i].area()<<endl;
                    cout<<"Perimeter: "<<R[i].perimeter()<<endl;
                }
                break;

            case 4:
                cout<<"Exiting the program. Goodbye!"<<endl;
                break;

            default:
                cout<<"Invalid choice!"<<endl;
        }

    }while(choice!=4); 


    delete[] R;

    return 0;
}