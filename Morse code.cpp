#include <iostream>
#include <map>
#include <limits>

using namespace std;
map<string, char> morse_to_alpha;
map<char, string> alpha_to_morse;

bool is_dot_or_dash(string cipher_text) {
    for (char c: cipher_text) {
        if (!isspace(c) && c != '-' && c != '.') {
            return false;
        }
    }
    return true;
}

bool is_in_map(string plain_text) {
    for (char c: plain_text) {
        if (isspace(c)){
            continue;
        }
        else if (!alpha_to_morse.count(c)) {
            return false;
        }
    }
    return true;
}

void morse_map() {
    morse_to_alpha[".-"] = 'A';
    morse_to_alpha[".-"] = 'a';
    morse_to_alpha["-..."] = 'B';
    morse_to_alpha["-..."] = 'b';
    morse_to_alpha["-.-."] = 'C';
    morse_to_alpha["-.-."] = 'c';
    morse_to_alpha["-.."] = 'D';
    morse_to_alpha["-.."] = 'd';
    morse_to_alpha["."] = 'E';
    morse_to_alpha["."] = 'e';
    morse_to_alpha["..-."] = 'F';
    morse_to_alpha["..-."] = 'f';
    morse_to_alpha["--."] = 'G';
    morse_to_alpha["--."] = 'g';
    morse_to_alpha["...."] = 'H';
    morse_to_alpha["...."] = 'h';
    morse_to_alpha[".."] = 'I';
    morse_to_alpha[".."] = 'i';
    morse_to_alpha[".---"] = 'J';
    morse_to_alpha[".---"] = 'j';
    morse_to_alpha["-.-"] = 'K';
    morse_to_alpha["-.-"] = 'k';
    morse_to_alpha[".-.."] = 'L';
    morse_to_alpha[".-.."] = 'l';
    morse_to_alpha["--"] = 'M';
    morse_to_alpha["--"] = 'm';
    morse_to_alpha["-."] = 'N';
    morse_to_alpha["-."] = 'n';
    morse_to_alpha["---"] = 'O';
    morse_to_alpha["---"] = 'o';
    morse_to_alpha[".--."] = 'P';
    morse_to_alpha[".--."] = 'p';
    morse_to_alpha["--.-"] = 'Q';
    morse_to_alpha["--.-"] = 'q';
    morse_to_alpha[".-."] = 'R';
    morse_to_alpha[".-."] = 'r';
    morse_to_alpha["..."] = 'S';
    morse_to_alpha["..."] = 's';
    morse_to_alpha["-"] = 'T';
    morse_to_alpha["-"] = 't';
    morse_to_alpha["..-"] = 'U';
    morse_to_alpha["..-"] = 'u';
    morse_to_alpha["...-"] = 'V';
    morse_to_alpha["...-"] = 'v';
    morse_to_alpha[".--"] = 'W';
    morse_to_alpha[".--"] = 'w';
    morse_to_alpha["-..-"] = 'X';
    morse_to_alpha["-..-"] = 'x';
    morse_to_alpha["-.--"] = 'Y';
    morse_to_alpha["-.--"] = 'y';
    morse_to_alpha["--.."] = 'Z';
    morse_to_alpha["--.."] = 'z';
    morse_to_alpha["-----"] = '0';
    morse_to_alpha[".----"] = '1';
    morse_to_alpha["..---"] = '2';
    morse_to_alpha["...--"] = '3';
    morse_to_alpha["....-"] = '4';
    morse_to_alpha["....."] = '5';
    morse_to_alpha["-...."] = '6';
    morse_to_alpha["--..."] = '7';
    morse_to_alpha["---.."] = '8';
    morse_to_alpha["----."] = '9';
    morse_to_alpha["..--.."] = '?';
    morse_to_alpha["-.-.--"] = '!';
    morse_to_alpha[".-.-.-"] = '.';
    morse_to_alpha["--..--"] = ',';
    morse_to_alpha["-.-.-."] = ';';
    morse_to_alpha["---..."] = ':';
    morse_to_alpha[".-.-"] = '+';
    morse_to_alpha["-....-"] = '-';
    morse_to_alpha["-..-."] = '/';
    morse_to_alpha["-...-"] = '=';
    morse_to_alpha["..--.-"] = '_';
    morse_to_alpha[".--.-."] = '@';

    alpha_to_morse['A'] = ".-";
    alpha_to_morse['a'] = ".-";
    alpha_to_morse['B'] = "-...";
    alpha_to_morse['b'] = "-...";
    alpha_to_morse['C'] = "-.-.";
    alpha_to_morse['c'] = "-.-.";
    alpha_to_morse['D'] = "-..";
    alpha_to_morse['d'] = "-..";
    alpha_to_morse['E'] = ".";
    alpha_to_morse['e'] = ".";
    alpha_to_morse['F'] = "..-.";
    alpha_to_morse['f'] = "..-.";
    alpha_to_morse['G'] = "--.";
    alpha_to_morse['g'] = "--.";
    alpha_to_morse['H'] = "....";
    alpha_to_morse['h'] = "....";
    alpha_to_morse['I'] = "..";
    alpha_to_morse['i'] = "..";
    alpha_to_morse['J'] = ".---";
    alpha_to_morse['j'] = ".---";
    alpha_to_morse['K'] = "-.-";
    alpha_to_morse['k'] = "-.-";
    alpha_to_morse['L'] = ".-..";
    alpha_to_morse['l'] = ".-..";
    alpha_to_morse['M'] = "--";
    alpha_to_morse['m'] = "--";
    alpha_to_morse['N'] = "-.";
    alpha_to_morse['n'] = "-.";
    alpha_to_morse['O'] = "---";
    alpha_to_morse['o'] = "---";
    alpha_to_morse['P'] = ".--.";
    alpha_to_morse['p'] = ".--.";
    alpha_to_morse['Q'] = "--.-";
    alpha_to_morse['q'] = "--.-";
    alpha_to_morse['R'] = ".-.";
    alpha_to_morse['r'] = ".-.";
    alpha_to_morse['S'] = "...";
    alpha_to_morse['s'] = "...";
    alpha_to_morse['T'] = "-";
    alpha_to_morse['t'] = "-";
    alpha_to_morse['U'] = "..-";
    alpha_to_morse['u'] = "..-";
    alpha_to_morse['V'] = "...-";
    alpha_to_morse['v'] = "...-";
    alpha_to_morse['W'] = ".--";
    alpha_to_morse['w'] = ".--";
    alpha_to_morse['X'] = "-..-";
    alpha_to_morse['x'] = "-..-";
    alpha_to_morse['Y'] = "-.--";
    alpha_to_morse['y'] = "-.--";
    alpha_to_morse['Z'] = "--..";
    alpha_to_morse['z'] = "--..";
    alpha_to_morse['0'] = "-----";
    alpha_to_morse['1'] = ".----";
    alpha_to_morse['2'] = "..---";
    alpha_to_morse['3'] = "...--";
    alpha_to_morse['4'] = "....-";
    alpha_to_morse['5'] = ".....";
    alpha_to_morse['6'] = "-....";
    alpha_to_morse['7'] = "--...";
    alpha_to_morse['8'] = "---..";
    alpha_to_morse['9'] = "----.";
    alpha_to_morse['?'] = "..--..";
    alpha_to_morse['!'] = "-.-.--";
    alpha_to_morse['.'] = ".-.-.-";
    alpha_to_morse[','] = "--..--";
    alpha_to_morse[';'] = "-.-.-.";
    alpha_to_morse[':'] = "---...";
    alpha_to_morse['+'] = ".-.-";
    alpha_to_morse['-'] = "-....-";
    alpha_to_morse['/'] = "-..-.";
    alpha_to_morse['='] = "-...-";
    alpha_to_morse['_'] = "..--.-";
    alpha_to_morse['@'] = ".--.-.";
}

void morse_cipher() {
    string plain_text;

    while (true){
        getline(cin, plain_text);

        if (is_in_map(plain_text)){
            break;
        }
        cout << "Please enter valid text\n";
    }

    string cipher_text;
    cout << "cipher text is: ";
    for (char c: plain_text) {
        if (!isspace(c)) {
            cout << alpha_to_morse[c] << " ";
        } else if (isspace(c)) {
            cout << "  ";
        }
    }
}

void morse_decipher() {
    string cipher_text;

    while (true) {
        getline(cin, cipher_text);

        if (is_dot_or_dash(cipher_text)) {
            break;
        }
        cout << "Please enter a valid morse code\n";
    }

    string slice;

    cout << "The text is: ";
    int space_count = 0;
    for (char c: cipher_text) {
        if (isspace(c)) {
            space_count += 1;
        } else if (!isspace(c)) {
            space_count = 0;
        }
        if (space_count == 0) {
            slice += c;
        }
        if (space_count == 1) {
            cout << morse_to_alpha[slice];
            slice.clear();
        } else if (space_count == 3) {
            cout << " ";
            space_count = 0;
        }
    }
    if (!slice.empty()) {
        cout << morse_to_alpha[slice];
    }

}


int main() {

    morse_map();
    morse_cipher();

    morse_decipher();
    return 0;
}
