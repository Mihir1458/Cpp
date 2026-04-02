#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{

    // connecting our file with hout stream
    ofstream o("sample60.txt");

    // creating a name string variable and filling it with string entered by the user
    string name;
    cout << "Enter your name: ";
    cin >> name;

    // writing a string to the file
    o << name + " is my name";

    // disconnecting our file
    o.close();
    // connecting our file with hin stream
    ifstream h("sample60.txt");

    // creating a content string variable and filling it with string present there in the text file
    string content;
    getline(h, content); // use getline for taking input with spaces

    cout << "The content of the file is: " << content;

    // disconnecting our file
    h.close();
    return 0;
}
