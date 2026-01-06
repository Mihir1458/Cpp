#include <iostream> 
using namespace std; 
class A { 
public: 
    void say() 
    { 
        cout << "Hello world"<<endl; 
    } 
}; 
class B : virtual public A { 
};   
class C : virtual public A { 
};   
class D : public B, public C{ 
    public:
    void say()
    {
         A :: say();
    }
}; 
int main() 
{ 
    D d; 
    d.say(); // No ambiguity, works fine
    return 0; 
}