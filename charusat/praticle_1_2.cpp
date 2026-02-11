#include <iostream>
using namespace std;

class Book {
private:
    int bookID;
    string title;
    string author;
    int copies;

public:

    // 1. setData
    void setData(int id, string t, string a, int c) {
        bookID = id;
        title = t;
        author = a;
        copies = c;
    }

    // 2. addNewBook
    void addNewBook() {
        cout << "Enter Book ID: ";
        cin >> bookID;
        cout << "Enter Title: ";
        cin >> title;
        cout << "Enter Author: ";
        cin >> author;
        cout << "Enter Available Copies: ";
        cin >> copies;
    }

    // 3. issueBook
    void issueBook() {
        if (copies > 0) {
            copies--;
            cout << "Book Issued Successfully\n";
        } else {
            cout << "Book Not Available\n";
        }
    }

    // 4. returnBook
    void returnBook() {
        copies++;
        cout << "Book Returned Successfully\n";
    }

    // 5. displayBook
    void displayBook() {
        cout << "\nBook ID: " << bookID;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nAvailable Copies: " << copies << endl;
    }
};

int main() {
    Book b[10];   // Array of objects
    int count = 0;
    int choice;

    do {
        cout << "\n----- Library Menu -----\n";
        cout << "1. Add New Book\n";
        cout << "2. Issue Book\n";
        cout << "3. Return Book\n";
        cout << "4. Display All Books\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            b[count].addNewBook();
            count++;
            break;

        case 2: {
            int id;
            cout << "Enter Book ID to Issue: ";
            cin >> id;
            for (int i = 0; i < count; i++) {
                if (id == i + 1) {
                    b[i].issueBook();
                }
            }
            break;
        }

        case 3: {
            int id;
            cout << "Enter Book ID to Return: ";
            cin >> id;
            for (int i = 0; i < count; i++) {
                if (id == i + 1) {
                    b[i].returnBook();
                }
            }
            break;
        }

        case 4:
            for (int i = 0; i < count; i++) {
                b[i].displayBook();
            }
            break;

        case 5:
            cout << "Exiting Program...\n";
            break;

        default:
            cout << "Invalid Choice\n";
        }

    } while (choice != 5);

    return 0;
}
