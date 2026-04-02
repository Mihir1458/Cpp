#include<iostream>
#include<fstream>

using namespace std;

int main(){
    string st = "mihir bhai";
    // Opening files using constructor and writing it
    ofstream fout("sample60.txt"); // Write operation
    fout<<st;

    return 0;
}
// #include<iostream>
// #include<fstream>

// using namespace std;

// int main(){
//     string st2;
//     // Opening files using constructor and reading it
//     ifstream in("sample60b.txt"); // Read operation
//     in>>st2;
//     getline(in, st2);  
//     cout<<st2;

//     return 0;
// }
