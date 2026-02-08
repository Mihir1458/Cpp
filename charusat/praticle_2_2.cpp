#include<iostream>
using namespace std;
class student_record_system{
   string ID,name;
   float mark[3];
   public:
   void input();
   void display();
   void avg();
};
void student_record_system::input(){
   cout<<"Enter ID: ";
   cin>>ID;
   cout<<"Enter Name: ";
   cin>>name;
   cout<<"Enter marks in 3 subjects: ";
   for(int i=0;i<3;i++){
      cin>>mark[i];
   }
}
void student_record_system::avg()
{
    float sum = 0;
    for(int i=0;i<3;i++){
        sum += mark[i];
    }
    cout<<"    | "<<sum/3.0<<endl;
}
void student_record_system::display()
{
    cout<<"--------------------------Student Details:-------------------------"<<endl;
    cout<<"Roll number:       | Name:       | Marks:       | average:  "<<endl;
    cout<<ID<<"            | "<<name<<"       | ";
    for(int i=0;i<3;i++){
        cout<<mark[i]<<" ";
    }
    avg();
 
}
int main()
{
    student_record_system s[500];
    int n;
    cout<<"Enter number of students: ";
    cin>>n;
    for(int i=0;i<n;i++){
        s[i].input();
    }
    for(int i=0;i<n;i++){
        s[i].display();
       
    }
    return 0;
}