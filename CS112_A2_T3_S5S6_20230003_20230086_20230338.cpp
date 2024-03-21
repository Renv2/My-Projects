// ===================================================================================== //
// FCAI – Structured Programming – 2024 - Assignment
// File:    CS112_A2_T3_S5S6_20230003_20230086_20230338.cpp
// Purpose: This program implements a Fraction Calculator that can perform basic
//          arithmetic operations (addition, subtraction, multiplication, division) on
//          rational numbers and integer.
// Author:  Ibrahim Mohamed Saad Mohamed_S6_20230003
//          Badr eldeen khaled ghareeb_S5_20230086
//          Mohamed Renven Mohamed_S6_20230338
// Emails:  hes93314@gmail.com
//          badrkhaledghareeb@gmail.com
//          modyrenven535@gmail.com
// TA name: Rana Abdelkader
// Date:    3/15/2024
// Version: 4.0
// ===================================================================================== //

#include <bits/stdc++.h>
#include <iostream>
#define ll long long

using namespace std;

// Struct to store numerator and denominator of a fraction
struct {
    ll num, deno;
    char op;
} num1, num2;

// Function to find the greatest common divisor of two numbers
ll common_divisor(ll result1, ll result2){
    if(result2 == 0)
        return result1;
    return common_divisor(result2, result1 % result2);
}

// Function to simplify a fraction
void simplify_result(ll result1, ll result2, ll divisor){
    result1 /= divisor;
    result2 /= divisor;

    // Handle negative fractions
    if(result2 < 0 && result1 > 0){
        result2 *= -1;
        result1 *= -1;
    }

    // Display the simplified result
    if(result2 == 1)
        cout << "\n" << "The result is: " << result1 << "\n\n";
    else
        cout << "\n" << "The result is: " << result1 << '/' << result2  << "\n\n";
}

// Function to perform multiplication of two fractions
void multiplication(ll numerator1, ll denominator1, ll numerator2, ll denominator2){
    if(numerator1 == 0 || numerator2 == 0){
        cout << "\n" << "The result is: " << 0 << "\n\n";
    }
    else {
        // Calculate the result of multiplication
        ll result1 = numerator1 * numerator2;
        ll result2 = denominator1 * denominator2;
        ll divisor = common_divisor(result1, result2);  // Find the GCD
        simplify_result(result1, result2, divisor);      // Simplify and display the result
    }
}

// Function to perform addition of two fractions
void addition(ll numerator1, ll denominator1, ll numerator2, ll denominator2){
    // Calculate the result of addition
    ll result1 = numerator1 * denominator2 + denominator1 * numerator2;
    ll result2 = denominator1 * denominator2;
    ll divisor = common_divisor(result1, result2);  // Find the GCD
    simplify_result(result1, result2, divisor);      // Simplify and display the result
}

// Function to perform subtraction of two fractions
void subtraction(ll numerator1, ll denominator1, ll numerator2, ll denominator2) {
    // Calculate the result of subtraction
    ll result1 = numerator1 * denominator2 - denominator1 * numerator2;
    ll result2 = denominator1 * denominator2;
    ll divisor = common_divisor(result1, result2);  // Find the GCD
    simplify_result(result1, result2, divisor);      // Simplify and display the result
}

// Function to perform division of two fractions
void division(ll numerator1, ll denominator1, ll numerator2, ll denominator2){
    if(numerator1 == 0){
        cout << "\n" << "The result is: " << 0 << "\n\n";
    }
    else {
        // Calculate the result of division
        ll result1 = numerator1 * denominator2;
        ll result2 = denominator1 * numerator2;
        ll divisor = common_divisor(result1, result2);  // Find the GCD
        simplify_result(result1, result2, divisor);      // Simplify and display the result
    }
}

int main() {

    cout << "|------------ Welcome to Fraction Calculator Program -------------|\n"
         << "|   In this application, you can enter two rational numbers and   |\n"
         << "|   perform an operation on them. The program handles negative    |\n"
         << "|   numbers and numerators without denominators. You must write   |\n"
         << "|   spaces before and after the arithmetic sign, and do not       |\n"
         << "|   write spaces in the fraction.                                 |\n"
         << "|-----------------------------------------------------------------|\n";
    while (true) {

        // initial variables
        char op;
        string rational_number, new_number = "";
        cout << "Please enter a rational number operations (or exit by enter 0): ";
        getline(cin, rational_number);

        // Regular expressions to parse the input string
        regex pattern1(R"((\+|-)?\d+/\-?\d+\s+[+\-*/]\s+(\+|-)?\d+/\-?\d+)");
        regex pattern2(R"(([+-]?\d+/[+-]?\d+)\s+([-+*/])\s+([+-]?\d+))");
        regex pattern3(R"(([+-]?\d+)\s+[+\-*/]\s+([+-]?\d+)(?:/(\d+))?)");
        regex pattern4(R"(([+-]?\d+)\s+[+\-*/]\s+([+-]?\d+))");

        // Remove spaces from input
        for(auto n_char : rational_number){
            if(!isspace(n_char)){
                new_number += n_char;
            }
        }
        // if user enter 0 exit from program
        if(new_number == "exit"){
            cout << "\n------------------------------------------------\n"
                 << " Thank you for using rational number calculator\n"
                 << "------------------------------------------------\n";
            break;
        }

        // parse each elements in specific variables
        stringstream check(new_number);

        // Match the input string with the regular expressions
        if(regex_match(rational_number, pattern1)){
            check >> num1.num >> num1.op >> num1.deno >> op >> num2.num >> num2.op >> num2.deno;

            if(num1.deno == 0 || num2.deno == 0 || num1.op != '/' || num2.op != '/'){
                cout << "\n------------------------ Invalid input ------------------------\n";
                continue;
            }
            // Perform the specified operation
            if(op == '*')
                multiplication(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '+')
                addition(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '-')
                subtraction(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '/')
                division(num1.num, num1.deno, num2.num, num2.deno);
        }

        else if(regex_match(rational_number, pattern2)){
            check >> num1.num >> num1.op >> num1.deno >> op >> num2.num;
            num2.deno = 1;
            if(num1.deno == 0 || num1.op != '/'){
                cout << "\n------------------------ Invalid input ------------------------\n";
                continue;
            }
            // Perform the specified operation
            if(op == '*')
                multiplication(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '+')
                addition(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '-')
                subtraction(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '/')
                division(num1.num, num1.deno, num2.num, num2.deno);
        }

        else if(regex_match(rational_number, pattern4)){
            check >> num1.num >> op >> num2.num;
            num1.deno = 1;
            num2.deno = 1;

            // Perform the specified operation
            if(op == '*')
                multiplication(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '+')
                addition(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '-')
                subtraction(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '/')
                division(num1.num, num1.deno, num2.num, num2.deno);
        }

        else if(regex_match(rational_number, pattern3)){
            check >> num1.num >> op >> num2.num >> num2.op >> num2.deno;
            num1.deno = 1;
            if(num2.deno == 0 || num2.op != '/'){
                cout << "\n------------------------ Invalid input ------------------------\n";
                continue;
            }
            // Perform the specified operation
            if(op == '*')
                multiplication(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '+')
                addition(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '-')
                subtraction(num1.num, num1.deno, num2.num, num2.deno);
            else if(op == '/')
                division(num1.num, num1.deno, num2.num, num2.deno);
        }

        else{
            cout << "\n------------------------ Invalid input ------------------------\n";
            continue;
        }
    }
}