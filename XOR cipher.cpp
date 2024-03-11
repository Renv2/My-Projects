#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

// encryption function
void encryption(string plain_text, string secret_key) {

    string encrypted_text = "";

    // duplicate the secret key until it is bigger than the text so that
    // each character in the text XOR with the character opposite to it in the secret key
    while (plain_text.length() > secret_key.length()) {
        secret_key += secret_key;
    }

    // XOR each character in the text with the character
    // opposite to it in the secret key
    if (plain_text.length() <= secret_key.length()) {
        for (int i = 0; i < plain_text.length(); i++) {
            encrypted_text += (char) (plain_text[i] ^ secret_key[i]);
        }
    }
    // print the encrypted text as text and hexa numbers
    cout << "encrypted text is: " << encrypted_text << endl;
    cout << "encrypted text in hexa is: ";

    cout.fill('0'); // Set fill character to '0'

    // setw(2) is to Print each byte with leading zeros
    // such that if one of the characters is zero it will be printed
    for (char c: encrypted_text) {
        cout << hex << setw(2) << int(c) << " ";
    }
}

// decryption function
void decryption(string hexa, string secret_key) {

    string plain_text = "";

    // duplicate the secret key until it is bigger than the hexa so that
    // each character in the hexa XOR with the character opposite to it in the secret key
    while (hexa.length() > secret_key.length()) {
        secret_key += secret_key;
    }

    for (int i = 0; i < hexa.length(); i += 3) {
        // separate every 2 hexa numbers to XOR with the secret key
        string hexa_byte = hexa.substr(i, 2);

        // convert the separated hex characters to integer value
        int hexa_value = stoi(hexa_byte, nullptr, 16);

        // XOR the integer value with the character opposite to it in the secret key
        plain_text += (char) (hexa_value ^ secret_key[i / 3]); // [i/3] because i increases by 3 every cycle
    }

    // print the decrypted text
    cout << "Decrypted text is: " << plain_text;
}
// Check if the input of the user is hexadecimal number
bool is_hexadecimal(string hexa) {
    for (char c: hexa) {
        if (!isxdigit(int(c))) {
            return false;
        }
    }
    return true;
}

// Check if the input of the user is integer number
int is_integer(int num) {
    for (char a: to_string(num)) {
        if (!isdigit(a)) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            return false;
        }
    }
    cin.clear(); // Clear error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    return num;
}


int main() {
    // Welcome message and menu
    cout << "\nWelcome to XOR cipher\n";
    cout << "This cipher takes a message and a secret key\n";
    cout << "every character in the message XOR with\n";
    cout << "the character corresponding to it in the secret key\n";
    cout << "then prints the ciphered message as text and hexadecimal\n\n";
    cout << "Enter <1> if you want to encrypt a message.\n";
    cout << "Enter <2> if you want to decrypt a message.\n";
    cout << "Enter <3> if you want to exit.\n";
    while (true) {
        int choice;
        cin >> choice;
        while (!is_integer(choice)) {
            cout << "Please enter a valid choice.\n";

            cin >> choice; // Ask for input again
        }

        while (choice == 1 || choice == 2) {
            if (choice == 1) {

                cout << "Enter the text you want to encrypt:";
                string plain_text;
                getline(cin, plain_text);

                cout << "Enter the secret key:";
                string secret_key;
                getline(cin, secret_key);

                encryption(plain_text, secret_key);
                choice = 3; // set choice to 3 to exit the game after the user finishes

            }
            else if (choice == 2) {
                cout << "Enter the encrypted text in hexadecimal:";
                string hexa;
                getline(cin, hexa);

                while (!is_hexadecimal(hexa)) {
                    cout << "Please enter a valid hexadecimal number.\n";
                    getline(cin, hexa);
                }

                cout << "Enter the secret key:";
                string secret_key;
                getline(cin, secret_key);

                decryption(hexa, secret_key);
                choice = 3; // set choice to 3 to exit the game after the user finishes
            }
        }
        if (choice == 3)
            break; // exit the game

        else {
            cout << "Please enter a valid choice.\n";
            continue;
        }
    }
    return 0;
}

