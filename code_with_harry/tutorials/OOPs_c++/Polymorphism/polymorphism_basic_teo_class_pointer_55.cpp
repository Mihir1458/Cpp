// #include <iostream>
// using namespace std;
// class base
// {
// protected:
//     int A;

// public:
//     void get()
//     {
//         cout << "Enter the value of A: ";
//         cin >> A;
//     }
//     void display()
//     {
//         cout << "The base class value of A is: " << A << endl;
//     }
// };
// class derived : public base
// {
//     int B;

// public:
//     void get()
//     {
//         cout << "Enter the value of B: ";
//         cin >> B;
//     }
//     void display()
//     {

//         cout << "The base class value of A is: " << A << endl;
//         cout << "The derived class value of B is: " << B << endl;
//     }
// };

// int main()
// {
//     base *ptr, a;
//     derived d, *ptr2;
//     //ptr = &a;
//     ptr = &d;
//     ptr2 = ptr;
//     ptr->get();
//     ptr2->get();
//     ptr2->display();
//     return 0;
// }
#include<iostream>
using namespace std;
class BaseClass{
    public:
        int var_base;
        void display(){
            cout<<"Dispalying Base class variable var_base "<<var_base<<endl;
        }
};

class DerivedClass : public BaseClass{
    public:
            int var_derived;
            void display(){
                cout<<"Dispalying Base class variable var_base "<<var_base<<endl;
                cout<<"Dispalying Derived class variable var_derived "<<var_derived<<endl;
            }
};
int main(){
    BaseClass * base_class_pointer;
    BaseClass obj_base;
    DerivedClass obj_derived;
    base_class_pointer = &obj_derived; // Pointing base class pointer to derived class

    base_class_pointer->var_base = 34;
    // base_class_pointer->var_derived= 134; // Will throw an error
    base_class_pointer->display();

    base_class_pointer->var_base = 3400; 
    base_class_pointer->display();

    DerivedClass * derived_class_pointer;
    derived_class_pointer = &obj_derived;
    derived_class_pointer->var_base = 9448;
    derived_class_pointer->var_derived = 98;
    derived_class_pointer->display();

    return 0;
}
