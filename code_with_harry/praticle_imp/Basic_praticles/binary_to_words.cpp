#include<iostream>
using namespace std;
int main()
{
    string binary;
    cout<<"Enter a binary number: ";
    cin>>binary;
    if(binary.length()%8!=0)
    {
        cout<<"Invalid binary number. Length must be a multiple of 8."<<endl;
        return 0;
    }
    else{
        for (int i = 0; i < binary.length(); i ++) {
            if (binary[i] != '0' && binary[i] != '1') {
                cout << "Invalid binary number. Only 0 and 1 are allowed." << endl;
                return 0;
            }   
            else if  {
                continue;
            }
        }
    }
}