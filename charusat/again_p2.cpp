#include<iostream>
using namespace std;
class library{
    std::string Book_ID,Title,author;
    int copy_av; 
    public :
    void add_book()
    {
        cout<<"entre book_id you want to add"<<endl;
        cin>>Book_ID;
        cout<<"entre Title you want to add"<<endl;
        cin>>Title;
        cout<<"entre author you want to add"<<endl;
        cin>>author;
        cout<<"book added succesfully"<<endl;
    }
    void issue_book()
    {
        int k=0,m;
        std::string issu;
        cout<<"How many books you want to issue (max 5)"<<endl;
        cin>>m;
        for(int i=0;i<=m && i<=5;i++)
        {
           if(copy_av > 0){ cout<<"Entre the Book_id of book you want to issue"<<endl;
            cin>>issu;
            k++;
            copy_av--;
            cout<<"book issued succesfully"<<endl;
           }
           else{
            exit(0);
           }
        }
        cout<<"you issued total"<<k<< "no.of books"<<endl;
        
    }
    void returnbook()
    {
        int k=0,m;
        std::string ret;
        cout<<"how many books do you want to return"<<endl;
        cin>>m;
        for(int i=0;i<=m;i++)
        {
            cout<<"entre book id and title";
            cin>>Book_ID;
            cin>>Title;
        }
    
    }
    void display ()
    
    {
        cout<<"book id is"<<Book_ID<<endl;
        cout<<"book title"<<Title<<endl;
        cout<<"book author"<<author<<endl;
        cout<<"book copy avaliable"<<copy_av<<endl;
        copy_av--;
    }
    
    void set_data ()
    {
        
        cout<<"book id is"<<endl;
        cin>>Book_ID;
        cout<<"book title"<<endl;
        cin>>Title;
        cout<<"book author"<<endl;
        cin>>author;
        cout<<"book copy avaliable"<<endl;
        cin>>copy_av;
    }
    

    };
int main()
{
    int k;
   class library digital;
   cout<<"which task do want to do"<<endl;
   cout<<"1. Set data"<<endl <<"2. Add book"<<endl<<"3. Issue book"<<endl<<"4. diplay all the books "<<"5. return book"<<"0 .exit"<<endl;
   cin>>k;
   do{
   switch(k)
   {
    case 1:
    cout<<"you entred set data"<<endl;
    digital.set_data();
    break;
    case 2:
    cout<<"you entre add book"<<endl;
    digital.add_book();
   break ;
    case 3:
    cout<<"you entred issue book "<<endl;
       digital.issue_book(); 
     
break ;
case 4:
cout <<"you entred display all books"<<endl;
digital.display();
break;
case 5:
cout<<"You entred return book"<<endl;
digital.returnbook();
break;
   }
}while (k!=0);
    
   
    return 0;

}