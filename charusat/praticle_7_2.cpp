#include<iostream>
using namespace std;

class Complex{
    private:
        float real;
        float imag;
    public:
        Complex():real(0),imag(0){}
      

        void input(){
            cout<<"Enter the real part of the complex number: ";
            cin>>real;
            cout<<"Enter the imaginary part of the complex number: ";
            cin>>imag;
        }

        void display(){
            cout<<"The complex number is: "<<real<<" + "<<imag<<"i"<<endl;
        }
         
      
        
        Complex operator + (Complex n) {
            Complex temp;
            temp.real = real + n.real;
            temp.imag = imag + n.imag;
            return temp;
        }

        Complex operator - (Complex n) {
            Complex temp;
            temp.real= real - n.real;
            temp.imag = imag - n.imag;
            return temp;
        }
        Complex operator * (Complex n) {
            Complex temp;
            temp.real= real * n.real;
            temp.imag = imag *  n.imag;
            return temp;
        }
    
};

int main(){
    Complex c1, c2, c3, c4,c5;
    c1.input();
    c1.display();

    c2.input();
    c2.display();

    c3 = c1 + c2; // Here c1 is calling object and c2 is argument object and c3 is the object which will store the result of addition of c1 and c2 
    c4 = c1 - c2;
    c5 = c1 * c2; 
    cout<<"The sum of the two complex numbers is: ";
    c3.display();

    cout<<"The difference of the two complex numbers is: ";
    c4.display();

    cout<<"The product of the two complex numbers is: ";
    c5.display();

    return 0;
}