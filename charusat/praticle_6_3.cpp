#include <iostream>
using namespace std;
class Fuel
{
protected:
    string fuelType;

public:
Fuel()
    {
        fuelType = "**";
    }
    Fuel(string a)
    {
        fuelType = a;
    }
    void display()
    {
        cout << "Fuel Type: " << fuelType << endl;
    }
};
class brand
{
protected:
    string brandname;
    string model;

public:
brand()
    {
        brandname = "**";
        model = "**";
    }
    brand(string name, string mdl)
    {
        brandname = name;
        model = mdl;
    }
    void display()
    {

        cout << "Brand Name: " << brandname << endl;
        cout << "Model: " << model << endl;
    }
};
class car : public Fuel, public brand
{
protected:
    long long price;

public:
car()
    {
        price = 0.0;
    }
    car(string fuel, string name, string mdl, long long prc) : Fuel(fuel), brand(name, mdl)
    {
        price = prc;
    }
    void display()
    {
        cout << "Fuel Type: " << fuelType << endl;
        cout << "Brand Name: " << brandname << endl;
        cout << "Model: " << model << endl;
        cout << "Price: " << price << endl;
    }
};
int main()
{
    int k;
    cout << "Enter number of cars: ";
    cin >> k;
    
    car c1[k];
    for (int i = 0; i < k; i++)
    {
        string fuel, name, mdl;
        long long prc;
        cout << "Car " << i + 1 << ":" << endl;
        cout << "Enter fuel type: ";
        cin >> fuel;
        cout << "Enter brand name: ";
        cin >> name;
        cout << "Enter model: ";
        cin >> mdl;
        cout << "Enter price: ";
        cin >> prc;
        car temp(fuel, name, mdl, prc);
        c1[i] = temp;
        cout<<"------------------------------"<<endl;
    }
    for(int i=0;i<k;i++)
    {
        cout<<"Car "<<i+1<<":"<<endl;
        c1[i].display();
        cout<<endl;
    }
    return 0;

}