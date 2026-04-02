#include<iostream>
#include<vector>
// Visit c plus plus plus dot com for more details and examples on vectors in C++.
using namespace std;
void display(vector<int> &v){
    for (int i = 0; i < v.size(); i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}
int main(){ 
    vector<int> vec1;
    int element, size;
    cout<<"Enter the size of your vector"<<endl;
    cin>>size;
    for (int i = 0; i < size; i++)
    {
        cout<<"Enter an element to add to this vector: ";
        cin>>element;
        vec1.push_back(element);
    }
    display(vec1);    
    return 0;
}
    // vector<int> vec1;      //zero length integer vector
    // vector<char> vec2(4);  //4-element character vector
    // vector<char> vec3(vec2);//4-element character vector from vec2
    // vector<int> vec4(6,3); //6-element vector of 3s