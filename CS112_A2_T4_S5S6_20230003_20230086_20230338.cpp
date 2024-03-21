// ===================================================================================== //
// FCAI – Structured Programming – 2024 - Assignment
// File:    CS112_A2_T4_S5S6_20230003_20230086_20230338.cpp
// Purpose: Cipher algorithms are very important to encrypt private data and
//          protect them from hackers. Armies use complex algorithms to protect
//          their communications from the enemies. in this program we applied
//          some cipher method
// Author:  Ibrahim Mohamed Saad Mohamed_S6_20230003 => problem 1, 4, 5
//          Badr eldeen khaled ghareeb_S5_20230086 => problem 2, 6, 7
//          Mohamed Renven Mohamed_S6_20230338 => problem 3, 8, 9
//          problem 10 => Teamwork
// Emails:  hes93314@gmail.com
//          badrkhaledghareeb@gmail.com
//          modyrenven535@gmail.com
// TA name: Rana Abdelkader
// Date:    3/18/2024
// Version: 6.0
// ===================================================================================== //

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// check message and keyword length
bool check_length_for_vignere(string input , int length){

    if(input.length() > length || input.length() == 0) {
        return true;
    }
    return false;
}


// convert each character to uppercase in message and keyword
string to_upper(string &input){
    for (auto &i : input) {
        if(isalpha(i) && islower(i)) i = char((int(i) - 32));
        else continue;

    }
    return input;
}

// Check whether condition a and c are met in the cipher and decipher affine function or not
bool check_for_affine_cipher( string b, string a = "5", string c = "21"){

    try {
        int a_int = stoi(a);
        int c_int = stoi(c);
        if ((a_int * c_int) % 26 != 1) {
            return true;
        }
    } catch (invalid_argument& e) {
        return true;
    }

    return false;
}

// Global variable for the cipher map
map <char, string> cipher_baconian{
        {'A', "aaaaa"}, {'B', "aaaab"}, {'C', "aaaba"}, {'D', "aaabb"}, {'E', "aabaa"},
        {'F', "aabab"}, {'G', "aabba"}, {'H', "aabbb"}, {'I', "abaaa"}, {'J', "abaab"},
        {'K', "ababa"}, {'L', "ababb"}, {'M', "abbaa"}, {'N', "abbab"}, {'O', "abbba"},
        {'P', "abbbb"}, {'Q', "baaaa"}, {'R', "baaab"}, {'S', "baaba"}, {'T', "baabb"},
        {'U', "babaa"}, {'V', "babab"}, {'W', "babba"}, {'X', "babbb"}, {'Y', "bbaaa"},
        {'Z', "bbaab"}
};

// Global variable for the decipher map
map <string, char> decipher_baconian{
        {"AAAAA", 'A'}, {"AAAAB", 'B'}, {"AAABA", 'C'}, {"AAABB", 'D'}, {"AABAA", 'E'},
        {"AABAB", 'F'}, {"AABBA", 'G'}, {"AABBB", 'H'}, {"ABAAA", 'I'}, {"ABAAB", 'J'},
        {"ABABA", 'K'}, {"ABABB", 'L'}, {"ABBAA", 'M'}, {"ABBAB", 'N'}, {"ABBBA", 'O'},
        {"ABBBB", 'P'}, {"BAAAA", 'Q'}, {"BAAAB", 'R'}, {"BAABA", 'S'}, {"BAABB", 'T'},
        {"BABAA", 'U'}, {"BABAB", 'V'}, {"BABBA", 'W'}, {"BABBB", 'X'}, {"BBAAA", 'Y'},
        {"BBAAB", 'Z'}
};

// Maps for Morse code conversion
map <string, string> morse_to_alpha{
        // Mapping Morse code to alphanumeric characters
        {"-----", "0"}, {".----", "1"}, {"..---", "2"}, {"...--", "3"}, {"....-", "4"},
        {".....", "5"}, {"-....", "6"}, {"--...", "7"}, {"---..", "8"}, {"----.", "9"},
        {"..--..", "?"}, {"-.-.--", "!"}, {".-.-.-", "."}, {"--..--", ","}, {"-.-.-.", ";"},
        {"---...", ":"}, {".-.-", "+"}, {"-....-", "-"}, {"-..-.", "/"}, {"-...-", "="},
        {"..--.-", "_"}, {".--.-.", "@"},
        // Mapping alphanumeric characters to Morse code
        {".-", "A"}, {"-...", "B"}, {"-.-.", "C"}, {"-..", "D"}, {".", "E"},
        {"..-.", "F"}, {"--.", "G"}, {"....", "H"}, {"..", "I"}, {".---", "J"},
        {"-.-", "K"}, {".-..", "L"}, {"--", "M"}, {"-.", "N"}, {"---", "O"},
        {".--.", "P"}, {"--.-", "Q"}, {".-.", "R"}, {"...", "S"}, {"-", "T"},
        {"..-", "U"}, {"...-", "V"}, {".--", "W"}, {"-..-", "X"}, {"-.--", "Y"},
        {"--..", "Z"}
};

// Mapping alphanumeric characters to Morse code
map <char, string> alpha_to_morse{
        {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
        {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."},
        {'?', "..--.."}, {'!', "-.-.--"}, {'.', ".-.-.-"}, {',', "--..--"}, {';', "-.-.-."},
        {':', "---..."}, {'+', ".-.-"}, {'-', "-....-"}, {'/', "-..-."}, {'=', "-...-"},
        {'_', "..--.-"}, {'@', ".--.-."}, {'A', ".-"}, {'B', "-..."}, {'C', "-.-."},{'D', "-.."},
        {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
        {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
        {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"}, {'U', "..-"}, {'V', "...-"},
        {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"}, {'Z', "--.."}
};


// Function to check if a message is valid for Baconian cipher
bool check_for_Baconian_cipher(string message) {
    if (message.length() % 5 != 0) {
        return true; // Message length must be a multiple of 5
    }
    for (auto n_char : message) {
        if (n_char != 'a' && n_char != 'b' && n_char != 'A' && n_char != 'B') {
            return true; // Invalid characters in the message. Only 'a' and 'b' (case_insensitive) are allowed.
        }
    }
    return false;
}

// global 2D array to matrix for Polybius Square Cipher and Decipher
char matrix1 [6][6];
void matrix_for_polybius_square() {
    // first element (( not important ))
    matrix1[0][0] = '0';
    while (true){
        cout << "Please enter your key : ";
        string key = "";
        string fixed_key = "";
        cin >> key;
        // to ignore any input not digit
        for ( char check : key ){
            if ( isdigit( check )){
                fixed_key += check ;
            }
        }

        // to make sure the key length is equal to 5
        if ( fixed_key.size() != 5 ){
            cout << "( Enter a valid key [ size ] )" << endl ;
            continue ;
        }
        // to check if key digits is between 1 ~ 5 or not
        int int_key_digt [ 5 ] ;
        bool end_while_1 = true ;
        for ( int i = 0 ; i < fixed_key.size() ; i ++ ){
            int_key_digt [i] = int ( fixed_key[i] ) - 48  ;
            if ( int_key_digt [i] > 5 || int_key_digt [i] < 1 ){
                cout << " ( Enter a valid key [ range ] )" << endl ;
                end_while_1 = false ;
                break;
            }
        }
        bool end_while_2 = true ;
        for ( int i = 0 ; i < 5 ; i ++ ){
            if ( int_key_digt[i] == int_key_digt[i+1] ){
                cout << " ( Enter a valid key [ contain all digits 1 ~ 5 ] )" << endl ;
                end_while_2 = false ;
                break;
            }
        }

        if ( end_while_1 == true && end_while_2 == true ) {
            // to fill the key in the matrix
            int dig_key = 0;
            for (int i = 1; i <= 5; i++) {
                matrix1[0][i] = matrix1[i][0] = fixed_key[dig_key];
                dig_key++;
            }
            //  fill the alphabet letters
            int ascii = 0;
            for (int i = 1; i <= 5; i++) {
                for (int j = 1; j <= 5; j++) {
                    matrix1[i][j] = char(65 + ascii);
                    if (matrix1[i][j] == 'J') {
                        ascii++;
                        matrix1[i][j] = char(65 + ascii);
                    }
                    ascii++;
                }
            }
            cout << "\n";
            break;
        }
        else
            continue ;
    }
}

char matrix2 [2][26];
void matrix_for_simple_Substitution() {
    while (true) {

        for (int i = 0; i < 26; i++) {                    // the first line in matrix (( alpha letters from a to z ))
            matrix2[0][i] = char(97 + i);
        }

        string key_str;             // convert the key from string to array
        string fixed_key ;
        cout << "Please enter the key: ";
        cin >> key_str;

        for ( char check : key_str ){
            if ( isalpha(check) ) {
                check = tolower(check);
                fixed_key += check;
            }
        }                                                           // to check the key
        if ( fixed_key.size() != 5 ){
            cout << "(( The key size must equal 5 ))" << endl;
            continue;
        }
        cout << endl;

        char key[fixed_key.size()];
        for (int i = 0; i < fixed_key.size(); i++) {
            key[i] = fixed_key[i];
        }
        // put the key in the start of second line
        for (int i = 0; i < fixed_key.size(); i++) {
            matrix2[1][i] = key[i];
        }
        // fill the remaining spaces in the second line with characters from the alphabet not in the key
        int n = 0;
        for (int i = fixed_key.size(); i < 26; i++) {
            char current_char = char(97 + n);
            if (fixed_key.find(current_char) == string::npos) {
                matrix2[1][i] = char(97 + n);
                i++;
            }
            n++;
            i--;

        }
        break ;
    }
}

// Check if the input of the user is hexadecimal number
bool check_hexadecimal_for_xor_cipher(string hexa) {
    for (char c: hexa) {
        if(isspace(int(c)))
            continue;
        if (!isxdigit(int(c)))
            return false;
    }
    return true;
}

string fix_the_message_for_route() {
    string message;
    string fixed_message;
    while (true) {                   // to fix the message
        cout << " Enter the message: ";
        getline(cin, message);
        for ( auto check: message ) {
            if (isalpha(check)) {
                check = toupper(check);
                fixed_message += check;
            }
        }
        if ( fixed_message == "") {
            cout << "(( Enter a valid message ))" << endl;
            continue;
        }
        break;
    }
    return fixed_message ;
}


int fix_the_key_for_route(){
    int columns ;
    while (true){
        // the key is number of columns (( key = columns ))
        cout << " Enter the key: ";
        cin >> columns ;
        if (cin.fail() || columns <= 0  ) {         // to check if key is integer or not
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " (( Enter a valid key ))" << endl;
            continue;
        }
        break ;
    }
    return columns ;        // wallahi key is equal to columns
}


int row_calc_for_route( string & fixed_message , int & columns) {     // to calculate the correct number of rows
    int size = fixed_message.size() ;
    int rows ;
    if ( size % columns == 0 ){
        rows = size / columns ;
    }
    else
        rows = ( size / columns ) + 1 ;
    return rows ;
}


void affine_cipher() {

    // Display welcome message and explain program
    cout << "\n|---------- Welcome to Affine Cipher program ------------|\n"
         << "In affine cipher each letter in an alphabet is mapped ---|\n"
         << "to its numeric equivalent x, encrypted using a simple ---|\n"
         << "mathematical function, and converted back to a letter. --|\n"
         << "Letter A is given number 0 and letter Z is given number -|\n"
         << "25. Each letter is encrypted with the function (5x + 8) -|\n"
         << "mod 26. The decryption function is 21(y − 8) mod 26. ----|\n";

    int arr[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                   'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    string a, b, c;
    string encrypted_message, message;

    // Take a message from user
    cout << "Please enter your message: ";
    getline(cin, message);

    // convert each character in message to uppercase
    to_upper(message);

    // Take 3 parameter a,b and c and check if digit and met a condition ((a * c) mod 26 = 1) or not
    do {
        cout << "please enter the first parameter [A]: ";
        getline(cin, a);
        cout << "please enter the second parameter [B]: ";
        getline(cin, b);
        cout << "please enter the third parameter [C]: ";
        getline(cin, c);
    } while (check_for_affine_cipher(b, a, c));

    // for loop to apply affine cipher method
    for (int i = 0; i < message.length(); ++i) {
        for (int j = 0; j < 26; ++j) {
            if (message[i] == arr[j] && isalpha(message[i])) {
                encrypted_message.push_back(arr[((stoi(a) * j) + stoi(b)) % 26]);
                break;
            } else if (isspace(message[i])) {
                encrypted_message.push_back(' ');
                break;
            }
        }
    }

    cout << "\n" << "-------------------" << setw(encrypted_message.size() + 2) << setfill('-') << "-" << endl
         << "Your message is: [ ";
    for (auto i: encrypted_message) {
        cout << i;
    }
    cout << " ]" << "\n" << "-------------------" << setw(encrypted_message.size() + 2) << setfill('-') << "-"
         << "\n\n";
    encrypted_message.clear();

}


void affine_decipher() {

    // Display welcome message and explain program
    cout << "\n|---------- Welcome to Affine Decipher program -----------|\n"
         << "In affine cipher each letter in an alphabet is mapped ---|\n"
         << "to its numeric equivalent x, encrypted using a simple ---|\n"
         << "mathematical function, and converted back to a letter. --|\n"
         << "Letter A is given number 0 and letter Z is given number -|\n"
         << "25. Each letter is encrypted with the function (5x + 8) -|\n"
         << "mod 26. The decryption function is 21(y − 8) mod 26. ----|\n";

    int arr[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                   'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    string a, b, c;
    string encrypted_message, message;

    // Take a message from user
    cout << "Please enter your message: ";
    getline(cin, message);

    // convert each character in message to uppercase
    to_upper(message);

    // Take 3 parameter a,b and c and check if digit and met a condition ((a * c) mod 26 = 1) or not
    do {
        cout << "please enter the first parameter [A]: ";
        getline(cin, a);
        cout << "please enter the second parameter [B]: ";
        getline(cin, b);
        cout << "please enter the third parameter [C]: ";
        getline(cin, c);
    } while (check_for_affine_cipher(b, a, c));

    // for loop to apply affine decipher method
    for (int i = 0; i < message.length(); ++i) {
        for (int j = 0; j < 26; ++j) {
            if (message[i] == arr[j] && isalpha(message[i])) {
                encrypted_message.push_back(arr[((stoi(c) * (j - stoi(b))) % 26 + 26) % 26]);
                break;
            } else if (isspace(message[i])) {
                encrypted_message.push_back(' ');
                break;
            }
        }
    }
    cout << "\n" << "-------------------" << setw(encrypted_message.size() + 2) << setfill('-') << "-" << endl
         << "Your message is: [ ";
    for (auto i: encrypted_message) {
        cout << i;
    }
    cout << " ]" << "\n" << "-------------------" << setw(encrypted_message.size() + 2) << setfill('-') << "-"
         << "\n\n";
    encrypted_message.clear();
}

// purpose functions
void route_cipher(){        // Do not forget (( the columns is equal to the key ))

    // Display welcome message and explain program
    cout << "\n|------------------------- Welcome to Route Cipher program ------------------------|\n"
         << "Route Cipher is one of the simplest and most widely known encryption --------------|\n"
         << "techniques. In this cipher, a secret integer key is used to create a --------------|\n"
         << "matrix whose number of columns is equal to the key and then the message -----------|\n"
         << "is written in as many rows as needed in this matrix. Then the encrypted -----------|\n"
         << "message is collected by going in a spiral path starting from the top right corner -|\n";

    // call functions
    string fixed_message = fix_the_message_for_route() ;
    int columns = fix_the_key_for_route() ;
    int rows = row_calc_for_route(  fixed_message ,  columns ) ;

    int size = fixed_message.size() ;
    //  to fill the matrix
    int count = 0 ;
    char matrix [rows][columns] ;
    for ( int i = 0 ; i < rows ; i++ ){
        for ( int j = 0 ; j < columns ; j ++){
            matrix [i][j] = fixed_message[count];
            count ++;
            if ( count == size + 1 ){          // to fill the x
                for ( int g = j ; g < columns ; g ++ ){
                    matrix [i][g] = 'X' ;
                }
                break ;
            }
        }
    }
    int mat_size = 0 ;
    for ( int i = 0 ; i < rows ; i++ ){                   // check the matrix and calculate matrix size
        for ( int j = 0 ; j < columns ; j ++) {
            cout << matrix [i][j] << " " ;
            mat_size ++ ;
        }
        cout << endl ;
    }
    cout << endl ;

    string ciphered_message ;
    int counter_1 = 0 ;
    int counter_2 = 0 ;
    for ( int i = 0 ; rows >= 0 || columns >= 0 ; i ++){
        int j = counter_2 ;
        for (  ; j < rows ; j ++){                              // to  the first column in clockwise
            ciphered_message += matrix [j][columns - 1] ;
            counter_1 ++ ;
        }
        if ( counter_1 == mat_size){
            break ;
        }
        // to the last row in matrix
        j = columns - 2 ;                   // note : ( j = columns - 2 ) not  (( - 1 )) as the first element already taken in the last for loop
        for (  ; j >= counter_2 ; j -- ){
            ciphered_message += matrix [rows - 1][j] ;
            counter_1 ++ ;
        }
        if ( counter_1 == mat_size){
            break ;
        }
        j = rows - 2 ;                      // note : ( j = rows - 2 ) not  (( - 1 )) as the first element already taken in the last for loop
        for (  ; j >= counter_2 ; j -- ){                     // to the first column
            ciphered_message += matrix [j][counter_2] ;
            counter_1 ++ ;
        }
        if ( counter_1 == mat_size){
            break ;
        }
        // to the top row
        j = counter_2 + 1 ;                            // note : j = 1  not 0  as the first element already taken in the last for loop
        for ( ; j < columns - 1 ; j++ ){
            ciphered_message += matrix [counter_2][j] ;
            counter_1 ++ ;
        }
        if ( counter_1 == mat_size){
            break ;
        }
        rows = rows - 1 ;
        columns = columns - 1 ;
        counter_2 ++ ;
    }
    cout << "The ciphered message is : " << ciphered_message << " " << endl << endl;

    cin.ignore();
}

void route_decipher(){

    // Display welcome message and explain program
    cout << "\n|------------------------- Welcome to Route Decipher program ----------------------|\n"
         << "Route Cipher is one of the simplest and most widely known encryption --------------|\n"
         << "techniques. In this cipher, a secret integer key is used to create a --------------|\n"
         << "matrix whose number of columns is equal to the key and then the message -----------|\n"
         << "is written in as many rows as needed in this matrix. Then the encrypted -----------|\n"
         << "message is collected by going in a spiral path starting from the top right corner -|\n";

    // call functions
    string fixed_message = fix_the_message_for_route() ;
    int columns = fix_the_key_for_route() ;
    int rows = row_calc_for_route( fixed_message , columns ) ;

    //  to fill the matrix
    char matrix [rows][columns] ;
    int mat_size = rows * columns ;
    int size = fixed_message.size() ;
    // to fill the message with x
    if ( size < mat_size ){
        for ( int i = 0 ; i < (mat_size - size)  ; i ++){
            fixed_message += 'X' ;
        }
    }

    string deciphered_message ;
    // to store the value of rows and columns
    int temp_r = rows ;
    int temp_c = columns ;

    int counter_1 = 0 ;
    int counter_2 = 0 ;
    for ( int i = 0 ; rows >= 0 || columns >= 0 ; i ++){
        int j = counter_2 ;
        for (  ; j < rows ; j ++){                              // to  the first column in clockwise
            matrix [j][columns - 1] = fixed_message[ counter_1 ] ;
            counter_1 ++ ;
        }
        if ( counter_1 == fixed_message.size()){
            break ;
        }

        // to the last row in matrix
        j = columns - 2 ;                   // note : ( j = columns - 2 ) not  (( - 1 )) as the first element already taken in the last for loop (( in first iterate ))
        for (  ; j >= counter_2 ; j -- ){
            matrix [rows - 1][j] = fixed_message[ counter_1 ];
            counter_1 ++ ;
        }
        if ( counter_1 == fixed_message.size()){
            break ;
        }

        j = rows - 2 ;                      // note : ( j = rows - 2 ) not  (( - 1 )) as the first element already taken in the last for loop  (( in first iterate ))
        for (  ; j >= counter_2 ; j -- ){                     // to the first column
            matrix [j][counter_2] = fixed_message[ counter_1 ] ;
            counter_1 ++ ;
        }
        if ( counter_1 == fixed_message.size()){
            break ;
        }

        // to the top row
        j = counter_2 + 1 ;                            // note : j = 1  not 0  as the first element already taken in the last for loop    (( in first iterate ))
        for ( ; j < columns - 1 ; j++ ){
            matrix [counter_2][j] = fixed_message[ counter_1 ] ;
            counter_1 ++ ;
        }
        if ( counter_1 == fixed_message.size()){
            break ;
        }

        rows = rows - 1 ;
        columns = columns - 1 ;
        counter_2 ++ ;
    }
    for ( int i = 0 ; i < temp_r ; i ++){
        for ( int j = 0 ; j < temp_c ; j ++){
            cout << matrix[i][j] << " " ;
            deciphered_message += matrix [i][j] ;
        }
        cout << endl ;
    }
    cout << endl << " The ciphered message is : " << deciphered_message << endl << endl;
    cin.ignore();
}


void atbash_cipher_decipher(){

    // Display welcome message and explain program
    cout << "\n|--------- Welcome to Atbash Cipher & Decipher program ---------|\n"
         << "The Atbash cipher is a very common, simple cipher. Basically, --|\n"
         << "when encoded, an A becomes a Z, B turns into Y, etc. another ---|\n"
         << "version that divides the alphabet into 2 halves and does the ---|\n"
         << "same thing on each half separate. ------------------------------|\n"
         << "\n|- Which Cipher do you like to choose? -|\n"
         << "1) the original cipher -----------------|\n"
         << "2) the divide into two halves ----------|\n";

    string choice;
    cout << "Please enter your choice: ";
    getline(cin, choice);
    while(true){
        if(choice != "1" && choice != "2"){
            cout << "Please enter your choice: ";
            getline(cin, choice);
        }
        else
            break;
    }
    cout << "\n";

    if (choice[0] == '1') {

        string text;
        cout << "please enter your message: ";
        getline(cin, text);

        string ciphered_text;
        for (char c: text) {
            if (isalpha(c)) {
                ciphered_text += ('Z' - toupper(c)) + 'A';
            } else {
                ciphered_text += c;
            }
        }
        cout << "\n" << "your message is: " << ciphered_text << "\n\n";

    }
    else if (choice[0] == '2') {

        string text;
        cout << "please enter your message: ";
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
        cout << "\n" << "Your message is: " << ciphered_text << "\n\n";
    }
}


void vignere_cipher() {

    // Display welcome message and explain program
    cout << "\n|------------ Welcome to Vignere Cipher program ------------|\n"
         << "In this method, a keyword is repeatedly added character ----|\n"
         << "by character to each alphabetic letter in the original -----|\n"
         << "message. The addition is carried out using the ASCII -------|\n"
         << "codes for each of the characters, modulo 26 (the number ----|\n"
         << "of letters in the alphabet), and the result is added to ----|\n"
         << "the code for the letter 'A' in the ASCII code sequence -----|\n";

    // Initial variable and empty vector
    int index = 0, n = 0;
    string message, keyword;
    vector <char> new_message;
    bool isAlpha = true;
    // Take a message from user
    cout << "Please enter a message of no more than 80 Characters: ";
    getline(cin, message);

    // pass the message to check length function
    while (check_length_for_vignere(message, 80)) {
        cout << "Please enter a message of no more than 80 Characters: ";
        getline(cin, message);
    }
    // convert each character in message to uppercase
    to_upper(message);

    // check each character in keyword is alphabetic and less than or equal to 8 or not
    do {
        cout << "Please enter a Keyword only alphabetic characters and no more than 8 characters: ";
        getline(cin, keyword);

        isAlpha = true;
        for (int i = 0 ; i < keyword.length() ; i++) {
            if (!isalpha(keyword[i])) {
                isAlpha = false;
                break;
            }
        }
    } while (!isAlpha || check_length_for_vignere(keyword, 8));

    // convert each character in keyword to uppercase
    to_upper(keyword);
    n = keyword.length()-1;

    // for loop to encrypt message with Vignere Cipher method
    for (auto n_char: message) {
        if (isalpha(n_char))
            new_message.push_back(char((n_char + keyword[index]) % 26 + 65));
        else if (isspace(n_char))
            new_message.push_back(' ');
        else if (isdigit(n_char))
            new_message.push_back(n_char);
        else if (ispunct(n_char))
            new_message.push_back(n_char);

        // Update index
        if (index < n)
            index++;
        // if keyword finished start from the beginning
        else
            index = 0;
    }

    cout << "\n" << "-------------------" << setw(new_message.size() + 2) << setfill('-') << "-" << endl << "Your message is: [ ";
    for (auto i: new_message) {
        cout << i;
    }
    cout << " ]" << "\n" << "-------------------" << setw(new_message.size() + 2) << setfill('-') << "-" << "\n\n";
    new_message.clear();

}


void vignere_decipher() {

    // Display welcome message and explain program
    cout << "\n|----------- Welcome to Vignere Decipher program -----------|\n"
         << "In this method, a keyword is repeatedly added character ----|\n"
         << "by character to each alphabetic letter in the original -----|\n"
         << "message. The addition is carried out using the ASCII -------|\n"
         << "codes for each of the characters, modulo 26 (the number ----|\n"
         << "of letters in the alphabet), and the result is added to ----|\n"
         << "the code for the letter 'A' in the ASCII code sequence -----|\n";

    // Initial variable and empty vector
    int index = 0, n = 0;
    string message, keyword;
    vector <char> new_message;
    bool isAlpha = true;

    // Take a message from user
    cout << "Please enter a message of no more than 80 Characters: ";
    getline(cin, message);

    // pass the message to check length function
    while (check_length_for_vignere(message, 80)) {
        cout << "Please enter a message of no more than 80 Characters: ";
        getline(cin, message);
    }
    // convert each character in message to uppercase
    to_upper(message);

    // check each character in keyword is alphabetic and less than or equal to 8 or not
    do {
        cout << "Please enter a Keyword only alphabetic characters and no more than 8 characters: ";
        getline(cin, keyword);

        isAlpha = true;
        for (int i = 0 ; i < keyword.length() ; i++) {
            if (!isalpha(keyword[i])) {
                isAlpha = false;
                break;
            }
        }
    } while (!isAlpha || check_length_for_vignere(keyword, 8));

    // convert each character in keyword to uppercase
    to_upper(keyword);
    n = keyword.length() - 1;

    // for loop to decrypt message with Vignere Cipher method
    for (auto n_char: message) {
        if (isalpha(n_char))
            new_message.push_back(char((n_char - 65 - (keyword[index] - 65) + 26) % 26 + 65));
        else if (isspace(n_char))
            new_message.push_back(' ');
        else if (isdigit(n_char))
            new_message.push_back(n_char);
        else if (ispunct(n_char))
            new_message.push_back(n_char);

        // Update index
        if (index < n)
            index++;
            // if keyword finished start from the beginning
        else
            index = 0;
    }
    cout << "\n" << "-------------------" << setw(new_message.size() + 2) << setfill('-') << "-" << endl
         << "Your message is: [ ";
    for (auto i: new_message) {
        cout << i;
    }
    cout << " ]" << "\n" << "-------------------" << setw(new_message.size() + 2) << setfill('-') << "-" << "\n\n";
    new_message.clear();

}

// Cipher function to encode a message using Baconian cipher
void baconian_cipher() {

    // Display welcome message and explain program
    cout << "\n|----------- Welcome to Baconian Cipher program -----------|\n"
         << "To encode a message, each letter of the plaintext is ------|\n"
            "replaced by a group of five of the letters 'A' or 'B' -----|\n"
            "This replacement is a binary encoding. For example, SAMY --|\n"
            " will be baaba aaaaa abbaa bbaaa. -------------------------|\n";

    // initial variables
    bool isValid = false;
    string message, new_message = "";
    while (true) {
        cout << "Please enter your message: ";
        getline(cin, message);

        for (auto n_char : message) {
            if (!isalpha(n_char) && !isspace(n_char)){
                isValid = true;
                break;
            }
        }
        if (!isValid)
            break;
        else
            isValid = false;
    }

    to_upper(message); // Convert the message to uppercase

    for (char c : message) {
        if (cipher_baconian.count(c)) {
            new_message += cipher_baconian[c];
        }
        else if(isspace(c)){
            new_message += ' ';
        }
    }

    cout << "\n" << "-------------------" << setw(new_message.size() + 2) << setfill('-') << "-" << endl
         << "Your message is: [ ";
    for (auto i: new_message) {
        cout << i;
    }
    cout << " ]" << "\n" << "-------------------" << setw(new_message.size() + 2) << setfill('-') << "-" << "\n\n";
    new_message.clear();
}

// Decipher function to decode an encoded message using Baconian cipher
void baconian_decipher() {

    // Display welcome message and explain program
    cout << "\n|---------- Welcome to Baconian Decipher program ----------|\n"
         << "To encode a message, each letter of the plaintext is ------|\n"
            "replaced by a group of five of the letters 'A' or 'B' -----|\n"
            "This replacement is a binary encoding. For example, SAMY --|\n"
            " will be baaba aaaaa abbaa bbaaa. -------------------------|\n";

    // initial variables
    string message, main_message = "";
    cout << "Please enter your message without spaces: ";
    getline(cin, message);
    while (check_for_Baconian_cipher(message)) {
        cout << "Please enter a valid message without spaces: ";
        getline(cin, message);
    }

    to_upper(message); // Convert the message to uppercase

    for (int i = 0; i < message.length(); i += 5) {
        string five_elements = message.substr(i, 5);
        if (decipher_baconian.count(five_elements)) {
            main_message += decipher_baconian[five_elements];
        }
    }
    cout << "\n" << "-------------------" << setw(main_message.size() + 2) << setfill('-') << "-" << endl
         << "Your message is: [ ";
    for (auto i: main_message) {
        cout << i;
    }
    cout << " ]" << "\n" << "-------------------" << setw(main_message.size() + 2) << setfill('-') << "-" << "\n\n";
    main_message.clear();
}

void simple_substitution_cipher() {

    // Display welcome message and explain program
    cout << "\n|--------- Welcome to Simple Substitution Decipher program ----------|\n"
         << "In this cipher, a replacement alphabet is used to replace each -----|\n"
         << "letter by another one. the cipher alphabet using a given key of ----|\n"
         << "5 unique letters. The user enters the key to cipher a message ------|\n"
         << "and the same key to decipher the message. The cipher alphabet is ---|\n"
         << "built by adding the remaining 21 letters (excluding the 5 letters --|\n"
         << "entered) in order after the key letters ----------------------------|\n";

    while (true) {
        // to fix the message
        string message;
        string fixed_message;
        cout << "please enter your message: ";
        getline(cin, message);
        for (char check: message) {
            if (isalpha(check)) {
                check = tolower(check);
                fixed_message += check;
            }
        }                                                       // to check for invalid message
        if ( fixed_message == ""){
            cout << " The fixed message is: Nothing "<< endl;
            cout << " (( Invalid message ))" << endl ;
            continue ;
        }

        matrix_for_simple_Substitution();                            // to cipher the message
        string ciphered_message;
        for (int i = 0; i < fixed_message.size(); i++) {
            for (int j = 0; j < 26; j++) {
                if (fixed_message[i] == matrix2[0][j]) {
                    ciphered_message += matrix2[1][j];
                }
            }
        }
        cout << "\n" << "Your message is: " << ciphered_message << endl;
        cout << "====================================================="  << "\n\n" ;
        break;
    }
    cin.ignore();
}

void simple_substitution_decipher() {

    // Display welcome message and explain program
    cout << "\n|---------- Welcome to Simple Substitution Cipher program ----------|\n"
         << "In this cipher, a replacement alphabet is used to replace each -----|\n"
         << "letter by another one. the cipher alphabet using a given key of ----|\n"
         << "5 unique letters. The user enters the key to cipher a message ------|\n"
         << "and the same key to decipher the message. The cipher alphabet is ---|\n"
         << "built by adding the remaining 21 letters (excluding the 5 letters --|\n"
         << "entered) in order after the key letters ----------------------------|\n";

    while (true) {
        string message;                         // to check the input
        string fixed_message;
        cout << "Please enter your message: ";
        getline(cin, message);
        for (char check: message) {
            check = tolower(check);
            fixed_message += check;
        }
        if ( fixed_message == ""){                      // to check for invalid input
            cout << " The fixed message is: Nothing " << endl;
            cout << " (( Invalid message ))" << endl ;
            continue ;
        }
        matrix_for_simple_Substitution();                       // to decipher the message
        string deciphered_message;
        for (int i = 0; i < fixed_message.size(); i++) {
            for (int j = 0; j < 26; j++) {
                if (fixed_message[i] == matrix2[1][j]) {
                    deciphered_message += matrix2[0][j];
                }
            }
        }
        cout << "\n" << "Your message is: " << deciphered_message << endl;
        cout << "====================================================="  << "\n\n";
        break ;
    }
    cin.ignore();
}


void polybius_square_cipher() {

    // Display welcome message and explain program
    cout << "\n|----------- Welcome to Polybius Square Cipher program ------------|\n"
         << "The Polybius Square Cipher is a simple yet effective way to -------|\n"
         << "encrypt text Each letter in the alphabet is represented by a ------|\n"
         << "pair of numbers, which correspond to the row and column of the ----|\n"
         << "letter in a 5x5 grid To encrypt a message, you find the row and ---|\n"
         << "column numbers for each letter in the grid and write them out as --|\n"
         << "a sequence of numbers To decrypt a message, you use the same grid -|\n"
         << "and pair up the numbers to find the corresponding letters. --------|\n"
         << "Please enter your message: ";

    while (true){

        // initial variables
        string message;
        string fixed_message;
        getline(cin, message);
        for (char check: message) {
            check = toupper(check);
            if (check == 'J') {         //  convert the J letter to I
                check = 'I';
            }
            if (isalpha(check)) {               // fill the fixed message
                fixed_message += check;
            }
        }

        if ( fixed_message == "" ){
            cout << "( Please Enter a valid message [ letters ] ) " << endl ;
            continue ;
        }
        else {
            cout << "\n";
            matrix_for_polybius_square() ;
            int len = fixed_message.size() ;
            string cipher_message = "" ;
            string  cipher_unit  = "" ;

            for ( int i = 0 ; i < len ; i ++ ) {                // to check all digit in the message
                for (int row = 1; row < 6; row++) {             // to check current digit in the message if in the current row or not
                    for (int col = 1; col < 6; col++) {         // to check current digit in the message if in the current row and col or not
                        if (fixed_message[i] == matrix1[row][col]) {
                            cipher_unit = matrix1[row][0] ;
                            cipher_unit += matrix1[0][col];
                            cipher_message += cipher_unit + " ";
                        }
                    }
                }
            }

            cout << "------------------" << setw(cipher_message.size() + 2) << setfill('-') << "-" << endl
                 << "Your message is: [ ";
            for (int i = 0 ; i < cipher_message.length() -1; i++) {
                cout << cipher_message[i];
            }
            cout << " ]" << "\n" << "------------------" << setw(cipher_message.size() + 2) << setfill('-') << "-" << "\n\n";
        }
        // Discard invalid input
        cin.ignore();
        break;
    }
}

void polybius_square_decipher() {

    // Display welcome message and explain program
    cout << "\n|---------- Welcome to Polybius Square Decipher program -----------|\n"
         << "The Polybius Square Cipher is a simple yet effective way to -------|\n"
         << "encrypt text Each letter in the alphabet is represented by a ------|\n"
         << "pair of numbers, which correspond to the row and column of the ----|\n"
         << "letter in a 5x5 grid To encrypt a message, you find the row and ---|\n"
         << "column numbers for each letter in the grid and write them out as --|\n"
         << "a sequence of numbers To decrypt a message, you use the same grid -|\n"
         << "and pair up the numbers to find the corresponding letters. --------|\n"
         << "Please enter your message: ";

    while (true) {

        // initial variables
        string message = "";
        string fixed_message = "";
        getline(cin, message);

        for (char check: message) {                   // to fix the message and ignore any input not digit
            if (isdigit(check)) {
                fixed_message += check;
            }
        }
        if ( fixed_message == "" ) {
            cout << "( Please Enter a valid message [ integers ] )" << endl;
            continue;
        }
        if (fixed_message.size() % 2 != 0) {                          // to make sure the message digits is even number
            cout << " ( Please the number of message digits must be even ) " << endl ;
            continue;
        }
        else{
            cout << "\n";
            matrix_for_polybius_square();
            int len = fixed_message.size();
            string rows;
            string cols;
            for (int i = 0; i < len; i += 2) {
                rows += fixed_message[i];
                cols += fixed_message[i + 1];
            }

            int row_digts[len / 2];
            for (int i = 0; i < (len / 2); i++) {
                for (int j = 0; j <= 5; j++) {            // j is equal to  matrix[i][0] that is the key
                    if (rows[i] == matrix1[j][0]) {
                        row_digts[i] = j;                        // to store the digit of the key that represent element in message
                        break;
                    }
                }
            }

            int col_digts[len / 2];
            for (int i = 0; i < (len / 2); i++) {
                for (int j = 0; j <= 5; j++) {            // j is equal to  matrix[0][i] that is the key
                    if (cols[i] == matrix1[0][j]) {
                        col_digts[i] = j;                        // to store the digit of the key that represent element in message
                        break;
                    }
                }
            }

            string deciphered_unit = "";
            string deciphered_message = "";
            for (int i = 0; i < (len / 2); i++) {
                deciphered_unit = matrix1[row_digts[i]][col_digts[i]];
                deciphered_message += deciphered_unit;
            }

            cout << "-------------------" << setw(deciphered_message.size() + 2) << setfill('-') << "-" << endl
                 << "Your message is: [ ";
            for (auto i: deciphered_message) {
                cout << i;
            }
            cout << " ]" << "\n" << "-------------------" << setw(deciphered_message.size() + 2) << setfill('-') << "-" << "\n\n";

            // Discard invalid input
            cin.ignore();
            break ;
        }
        break;
    }
}


void morse_cipher() {

    // Display welcome message and explain program
    cout << "\n|---------- Welcome to Morse Cipher program ----------|\n"
         << "It is a code consisting of two symbols dot and dash --|\n"
         << "and used to in the telegraph system in the past and --|\n"
         << "also communicate messages in primitive ways. ---------|\n";

    // initial variables
    string plain_text, cipher_text;
    cout << "Please enter your message: ";
    getline(cin, plain_text);
    cout << "\nYour message is: [ ";
    for (char c: plain_text) {
        if (!isspace(c)) {
            c = toupper(c);
            cout << alpha_to_morse[c] << " ";
        } else if (isspace(c)) {
            cout << "  ";
        }
    }
    cout << "]" << "\n\n";
}

void morse_decipher() {

    // Display welcome message and explain program
    cout << "\n|--------- Welcome to Morse Decipher program ---------|\n"
         << "It is a code consisting of two symbols dot and dash --|\n"
         << "and used to in the telegraph system in the past and --|\n"
         << "also communicate messages in primitive ways. ---------|\n";

    // initial variables
    string cipher_text, slice;
    cout << "Please enter your message: ";
    getline(cin, cipher_text);
    cout << "\nYour message is: [ ";
    int space_count = 0;
    for (char c: cipher_text) {
        if (isspace(c)) {
            space_count += 1;
        }
        else if(!isspace(c)){
            space_count = 0;
        }
        if (space_count == 0) {
            slice += c;
        }
        if (space_count == 1) {
            cout << morse_to_alpha[slice];
            slice.clear();
        }
        else if (space_count == 3) {
            cout << " ";
            space_count = 0;
        }
    }
    if (!slice.empty()){
        cout << morse_to_alpha[slice];
    }
    cout << "]" << "\n\n";
}

// encryption function for xor cipher
void xor_cipher() {

    // Display welcome message and explain program
    cout << "\n|------------------------ Welcome to Xor Cipher program -------------------------|\n"
         << "In this cipher, a secret key consisting of one letter (or more) is given --------|\n"
         << "from the sender to the receiver. Key can be any number of letters. Then each ----|\n"
         << "letter of the message goes through XOR operation with one of the secret letters -|\n"
         << "in order. The output is printed in text and hexadecimal. The original message ---|\n"
         << "can be recovered from the encrypted message by the same algorithm, XOR  with ----|\n"
         << "the secret letter ---------------------------------------------------------------|\n";

    cout << "Please enter the text you want to encrypt: ";
    string plain_text;
    getline(cin, plain_text);

    cout << "Please enter the secret key: ";
    string secret_key;
    getline(cin, secret_key);

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
    cout << endl << endl;
}

// decryption function for xor decipher
void xor_decipher() {

    // Display welcome message and explain program
    cout << "\n|----------------------- Welcome to Xor Decipher program ------------------------|\n"
         << "In this cipher, a secret key consisting of one letter (or more) is given --------|\n"
         << "from the sender to the receiver. Key can be any number of letters. Then each ----|\n"
         << "letter of the message goes through XOR operation with one of the secret letters -|\n"
         << "in order. The output is printed in text and hexadecimal. The original message ---|\n"
         << "can be recovered from the encrypted message by the same algorithm, XOR  with ----|\n"
         << "the secret letter ---------------------------------------------------------------|\n";

    cout << "Please enter the encrypted text in hexadecimal: ";
    string hexa;
    getline(cin, hexa);

    while (!check_hexadecimal_for_xor_cipher(hexa)) {
        cout << "Please enter a valid hexadecimal number.\n";
        getline(cin, hexa);
    }

    cout << "Please enter the secret key: ";
    string secret_key;
    getline(cin, secret_key);

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
    cout << endl << endl;
}

void rail_fence_cipher() {

    // initial variables
    int j = 0;
    bool flag = false, isValid = false;
    string message, new_message = "", final_message = "", key;

    // Display welcome message and explain program
    cout << "\n|-------------- Welcome to Rail Fence cipher program --------------|\n"
         << "The rail fence cipher is a very simple, easy to crack cipher. -----|\n"
         << "It is a transposition cipher that follows a simple rule for -------|\n"
         << "mixing up the characters in the plaintext to form the ciphertext. -|\n"
         << "and it will be shown that it can be easily broken even by hand. ---|\n";
    cout << "Please enter your message english letters only otherwise it is ignored: ";
    getline(cin, message);

    // take english letters only from message
    for (auto n_char: message) {
        if (isalpha(n_char)) {
            new_message += n_char;
        }
    }
    while(true) {
        if (new_message.empty()) {
            cout << "Please enter your message english letters only otherwise it is ignored: ";
            getline(cin, message);
            for (auto n_char: message) {
                if (isalpha(n_char)) {
                    new_message += n_char;
                }
            }
        }
        else
           break;
    }

    cout << "please choose the key 3 or 4: ";
    getline(cin, key);

    // check if key is valid or not
    while (true) {
        if (key != "3" && key != "4") {
            cout << "please choose the key 3 or 4: ";
            getline(cin, key);
        } else {
            break;
        }
    }

    int key1 = stoi(key);

    // do matrix and fill each elements with dot
    char array[key1][new_message.length()];
    for (int i = 0; i < key1; ++i) {
        for (int k = 0; k < new_message.length(); ++k) {
            array[i][k] = '.';
        }
    }

    // fill zegzage elements by alphabetic
    for (int i = 0; i < new_message.length(); ++i) {
        array[j][i] = new_message[i];
        if (flag)
            j--;
        else
            j++;
        if (j == key1 - 1)
            flag = true;
        else if (j == -1) {
            flag = false;
            j += 2;
        }
    }
    cout << endl;

    // display matrix
    for (int i = 0; i < key1; ++i) {
        for (int k = 0; k < new_message.length(); ++k) {
            cout << array[i][k] << " ";
        }
        cout << endl;
    }
    cout << "\n";

    // display the encrypted message
    for (int i = 0; i < key1; ++i) {
        for (int k = 0; k < new_message.length(); ++k) {
            if (isalpha(array[i][k]))
                final_message += array[i][k];
        }
    }
    cout << "Your message is: "<< final_message << endl << endl;
}

void rail_fence_decipher() {

    // initial variables
    int j = 0;
    bool flag = false, isValid = false;
    string message, new_message = "", final_message = "", key;

    // Display welcome message and explain program
    cout << "\n|-------------- Welcome to Rail Fence cipher program --------------|\n"
         << "The rail fence cipher is a very simple, easy to crack cipher. -----|\n"
         << "It is a transposition cipher that follows a simple rule for -------|\n"
         << "mixing up the characters in the plaintext to form the ciphertext. -|\n"
         << "and it will be shown that it can be easily broken even by hand. ---|\n";
    cout << "Please enter your message english letters only otherwise it is ignored: ";
    getline(cin, message);

    // take english letters only from message
    for (auto n_char: message) {
        if (isalpha(n_char)) {
            new_message += n_char;
        }
    }

    while(true) {
        if (new_message.empty()) {
            cout << "Please enter your message english letters only otherwise it is ignored: ";
            getline(cin, message);
            for (auto n_char: message) {
                if (isalpha(n_char)) {
                    new_message += n_char;
                }
            }
        }
        else
            break;
    }
    cout << "please choose the key 3 or 4: ";
    getline(cin, key);

    // check if key is valid or not
    while (true) {
        if (key != "3" && key != "4") {
            cout << "please choose the key 3 or 4: ";
            getline(cin, key);
        } else {
            break;
        }
    }
    int key1 = stoi(key);
    char array[key1][new_message.length()];

    // do matrix and fill each elements with dot
    for (int i = 0; i < key1; ++i) {
        for (int k = 0; k < new_message.length(); ++k) {
            array[i][k] = '.';
        }
    }

    // fill zegzage elements by alphabetic
    for (int i = 0; i < new_message.length() ; ++i){
        if(isalpha(new_message[j])){
            array[j][i] = new_message[j];
            for (int k = j+1; k < key1; ++k) {
                array[k][i] = '.';
            }
        }
        if (flag)
            j--;
        else
            j++;
        if (j == key1 - 1)
            flag = true;
        else if (j == -1) {
            flag = false;
            j += 2;
        }

    }

    // fill matrix with the main message
    int n_char = 0;
    for (int i = 0; i < key1 ; ++i){
        for (int k = 0; k < new_message.length(); ++k) {
            if(isalpha(array[i][k])){
                array[i][k] = new_message[n_char];
                n_char++;
            }
        }
    }
    cout << endl;

    // display matrix
    for (int i = 0; i < key1; ++i) {
        for (int k = 0; k < new_message.length(); ++k) {
            cout << array[i][k] << " ";
        }
        cout << endl;
    }
    cout << "\n";

    // display the encrypted message
    for (int i = 0; i < new_message.length() ; ++i){
        for (int k = 0; k < key1 ; ++k) {
            if(isalpha(array[k][i])){
                final_message += array[k][i];
            }
        }
    }
    cout << "Your message is: " << final_message << endl << endl;
}


int main() {
    while (true) {

        // Initial variables
        string message, keyword, choice_from_menu1, choice_from_menu2;

        // Display message and Menu_1
        cout << "|---- Ahlan ya user ya habibi ----|\n"
             << "|- What do you like to do today? -|\n"
             << "1) Cipher a message --------------|\n"
             << "2) Decipher a message ------------|\n"
             << "3) End ---------------------------|\n";
        cout << "Please choose a number from the list [1, 2, 3]: ";
        getline(cin, choice_from_menu1);

        // while loop to check if input in Menu_1 or not
        while (true) {
            if (choice_from_menu1 != "1" && choice_from_menu1 != "2" && choice_from_menu1 != "3"){
                cout << "Please choose a number from the list [1, 2, 3]: ";
                getline(cin, choice_from_menu1);
            }
            else break;
        }

        // if user chosen 3 exit from program and display goodbye message
        if (choice_from_menu1 == "3") {
            cout << "\n--------------------------------------\n"
                 << "Thank you, I hope you have a good time\n"
                 << "--------------------------------------\n\n";
            break;
        }

        // Display Menu_2 and asking user which cipher does he like to choose for encrypt or decrypt a message
        cout << "\n|- Which Cipher do you like to choose? -|\n"
             << "1) Affine Cipher -----------------------|\n"
             << "2) Route Cipher ------------------------|\n"
             << "3) Atbash Cipher -----------------------|\n"
             << "4) Vignere Cipher ----------------------|\n"
             << "5) Baconian cipher ---------------------|\n"
             << "6) Simple Substitution cipher ----------|\n"
             << "7) Polybius Square Cipher --------------|\n"
             << "8) Morse Cipher ------------------------|\n"
             << "9) Xor Cipher --------------------------|\n"
             << "10) Rail Fence Cipher ------------------|\n"
             << "11) Return -----------------------------|\n";
        cout << "Please choose a number from the list [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]: ";
        getline(cin, choice_from_menu2);

        // while loop to check if input in Menu_2 or not
        while (true) {
            if (choice_from_menu2 != "1" && choice_from_menu2 != "2" && choice_from_menu2 != "3" && choice_from_menu2 != "4" && choice_from_menu2 != "5" && choice_from_menu2 != "6" && choice_from_menu2 != "7" && choice_from_menu2 != "8" && choice_from_menu2 != "9" && choice_from_menu2 != "10" && choice_from_menu2 != "11") {
                cout << "Please choose a number from the list [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]: ";
                getline(cin, choice_from_menu2);
            }
            else break;
        }
        // The following conditions to enter a function from the user's choice
        if(choice_from_menu1 == "1" && choice_from_menu2 == "1")
            affine_cipher();
        else if(choice_from_menu1 == "2" && choice_from_menu2 == "1")
            affine_decipher();
        else if(choice_from_menu1 == "1" && choice_from_menu2 == "2")
            route_cipher();
        else if(choice_from_menu1 == "2" && choice_from_menu2 == "2")
            route_decipher();
        else if(choice_from_menu1 == "1" && choice_from_menu2 == "3")
            atbash_cipher_decipher();
        else if(choice_from_menu1 == "2" && choice_from_menu2 == "3")
            atbash_cipher_decipher();
        else if(choice_from_menu1 == "1" && choice_from_menu2 == "4")
            vignere_cipher();
        else if(choice_from_menu1 == "2" && choice_from_menu2 == "4")
            vignere_decipher();
        else if(choice_from_menu1 == "1" && choice_from_menu2 == "5")
            baconian_cipher();
        else if(choice_from_menu1 == "2" && choice_from_menu2 == "5")
            baconian_decipher();
        else if(choice_from_menu1 == "1" && choice_from_menu2 == "6")
            simple_substitution_cipher();
        else if(choice_from_menu1 == "2" && choice_from_menu2 == "6")
            simple_substitution_decipher();
        else if(choice_from_menu1 == "1" && choice_from_menu2 == "7")
            polybius_square_cipher();
        else if(choice_from_menu1 == "2" && choice_from_menu2 == "7")
            polybius_square_decipher();
        else if(choice_from_menu1 == "1" && choice_from_menu2 == "8")
            morse_cipher();
        else if(choice_from_menu1 == "2" && choice_from_menu2 == "8")
            morse_decipher();
        else if(choice_from_menu1 == "1" && choice_from_menu2 == "9")
            xor_cipher();
        else if(choice_from_menu1 == "2" && choice_from_menu2 == "9")
            xor_decipher();
        else if(choice_from_menu1 == "1" && choice_from_menu2 == "10")
            rail_fence_cipher();
        else if(choice_from_menu1 == "2" && choice_from_menu2 == "10")
            rail_fence_decipher();

            // if user want to Replay Menu_1
        else{
            cout << endl;
            continue;
        }

        // Clear error flags
        cin.clear();
    }
}