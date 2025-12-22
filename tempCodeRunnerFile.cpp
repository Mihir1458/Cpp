#include<iostream>
#include<string>

using namespace std;
class Bin 
{
    private:
    string s;
    public:
    void read();
    void chk_bin();
    void ones_compliment();
    void display(); 
};
void Bin::read()
{
    cout << "Enter a binary number" << endl;
    cin >> s;
}
void Bin::chk_bin()
{
    for(int i=0;i<s.length();i++)
    {
        if(s.at(i)!='0' && s.at(i)!='1')
        {
            cout << "Invalid binary number" << endl;
            exit(0);
        }
    }
}
void Bin::ones_compliment()
{
    for(int i=0;i<s.length();i++)
    {
        if(s.at(i)=='0')
        {
            s.at(i)='1';
        }
        else
        {
            s.at(i)='0';
        }
    }
}
void Bin::display()
{
    for(int i=0;i<s.length();i++)
    {
        cout << s.at(i);
    }
}
int main()
{
    Bin b;
    b.read();
    b.chk_bin();
    b.ones_compliment();
    b.display();
    return 0;
}