#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    ifstream file;
    string filename;

    // Retry mechanism for file opening
    while (true) {
        cout << "Enter file path (or type exit): ";
        cin >> filename;

        if (filename == "exit") {
            cout << "Program exited.\n";
            return 0;
        }

        file.open(filename);

        if (file.is_open()) {
            break;
        } else {
            cout << "Error: File not found. Try again.\n";
        }
    }

    string line;
    int lineNo = 0;
    int validCount = 0, invalidCount = 0;
    double sum = 0;

    // Error log (fixed size)
    string errorLog[100];
    int errorIndex = 0;

    while (getline(file, line)) {
        lineNo++;
        stringstream ss(line);
        double num;
        bool isValid = true;

        // Try extracting numbers
        try {
            if (!(ss >> num)) {
                throw "Invalid data";
            }

            sum += num;
            validCount++;
        }
        catch (...) {
            isValid = false;
        }

        if (!isValid) {
            invalidCount++;
            if (errorIndex < 100) {
                errorLog[errorIndex++] = "Line " + to_string(lineNo) + ": " + line;
            }
            cout << "Corrupted line at " << lineNo << " skipped.\n";
        }
    }

    file.close();

    // Final results
    cout << "\n----- RESULT -----\n";
    cout << "Valid lines: " << validCount << endl;
    cout << "Invalid lines: " << invalidCount << endl;

    if (validCount > 0) {
        cout << "Sum = " << sum << endl;
        cout << "Average = " << sum / validCount << endl;
    }

    // Error log display
    cout << "\n----- ERROR LOG -----\n";
    for (int i = 0; i < errorIndex; i++) {
        cout << errorLog[i] << endl;
    }

    return 0;
}