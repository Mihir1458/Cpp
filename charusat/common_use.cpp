// p 5.1
#include <iostream>
#include <string>
#include <cctype>   // for tolower()

using namespace std;

int main()
{
    string paragraph;
    cout << "Enter a paragraph:\n";
    getline(cin, paragraph);   // 1. Read full paragraph

    string words[100];         // store words
    int freq[100] = {0};       // frequency array
    int wordCount = 0;

    string temp = "";

    // 2. Extract words manually
    for (int i = 0; i <= paragraph.length(); i++)
    {
        char ch = paragraph[i];

        if (isalpha(ch))   // only letters
        {
            temp += tolower(ch);  // convert to lowercase
        }
        else
        {
            if (temp != "")
            {
                // 3. Check if word already exists
                int found = -1;
                for (int j = 0; j < wordCount; j++)
                {
                    if (words[j] == temp)
                    {
                        found = j;
                        break;
                    }
                }

                if (found == -1)
                {
                    words[wordCount] = temp;
                    freq[wordCount] = 1;
                    wordCount++;
                }
                else
                {
                    freq[found]++;
                }

                temp = "";
            }
        }
    }

    // 4. Output extracted words
    cout << "\nExtracted Words:\n";
    for (int i = 0; i < wordCount; i++)
    {
        cout << words[i] << " ";
    }

    // 5. Output frequencies
    cout << "\n\nWord Frequencies:\n";
    for (int i = 0; i < wordCount; i++)
    {
        cout << words[i] << " : " << freq[i] << endl;
    }

    return 0;
}