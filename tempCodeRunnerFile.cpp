#include<iostream>
using namespace std;

// ================= WITHOUT VIRTUAL DESTRUCTOR =================
class Base1 {
public:
    Base1() {
        cout << "Base1 Constructor" << endl;
    }

    ~Base1() {   // ❌ Non-virtual destructor
        cout << "Base1 Destructor" << endl;
    }
};

class Derived1 : public Base1 {
    int* data;
public:
    Derived1() {
        data = new int(10);
        cout << "Derived1 Constructor" << endl;
    }

    ~Derived1() {
        delete data;
        cout << "Derived1 Destructor" << endl;
    }
};

// ================= WITH VIRTUAL DESTRUCTOR =================
class Base2 {
public:
    Base2() {
        cout << "Base2 Constructor" << endl;
    }

    virtual ~Base2() {   // ✅ Virtual destructor
        cout << "Base2 Destructor" << endl;
    }
};

class Derived2 : public Base2 {
    int* data;
public:
    Derived2() {
        data = new int(20);
        cout << "Derived2 Constructor" << endl;
    }

    ~Derived2() {
        delete data;
        cout << "Derived2 Destructor" << endl;
    }
};

// ================= MAIN FUNCTION =================
int main() {

    cout << "===== WITHOUT VIRTUAL DESTRUCTOR =====" << endl;
    Base1* ptr1 = new Derived1();
    delete ptr1;   // ❌ Derived destructor will NOT be called

    cout << "\n===== WITH VIRTUAL DESTRUCTOR =====" << endl;
    Base2* ptr2 = new Derived2();
    delete ptr2;   // ✅ Both destructors will be called

    return 0;
}