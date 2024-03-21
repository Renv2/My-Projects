#include <iostream>
#include <limits>

using namespace std;


int main() {
    cout << "Welcome to Atbash cipher\n";
    cout << "Enter (1) for the original cipher\n";
    cout << "Enter (2) for the divide into two halves\n";
    int choice;
    cin >> choice;
    if (choice == 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        string text;
        cout << "enter the text\n";
        getline(cin, text);

        string ciphered_text;
        for (char c: text) {
            if (isalpha(c)) {
                ciphered_text += ('Z' - toupper(c)) + 'A';
            } else {
                ciphered_text += c;
            }
        }
        cout << "ciphered text is: " << ciphered_text << endl;

    } else if (choice == 2) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        string text;
        cout << "enter the text\n";
        getline(cin, text);

        string ciphered_text;
        for (char c: text) {
            if (!isalpha(c)) {
                ciphered_text += c;
                continue;
            }
            if ('A' <= toupper(c) && toupper(c) <= 'M') {
                ciphered_text += ('M' - toupper(c)) + 'A';
            } else if ('N' <= toupper(c) && toupper(c) <= 'Z') {
                ciphered_text += ('Z' - toupper(c)) + 'N';
            }
        }
        cout << "ciphered text is: " << ciphered_text << endl;
    }

}