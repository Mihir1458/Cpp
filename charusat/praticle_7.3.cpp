#include <iostream>
using namespace std;
class fren;
class cel
{
    float tempC;
public:
    cel() : tempC(0) {}
    cel(float t)
    {
        tempC = t;
    }
};
class fren
{
    float tempF;
public:
    fren() : tempF(0) {}
    fren(float t)
    {
        tempF = t;
    }
    fren operator==(cel &cX)
    {
            
            
        
        if (tempF == cX.tempC;)
        {
            cout << "Equal" << endl;
        }
        else
        {
            cout << "Not Equal" << endl;
        }
        return ans;
    }
};
int main()
{
    cel c1(10);
    fren f1(50);
    c1 == f1;
}