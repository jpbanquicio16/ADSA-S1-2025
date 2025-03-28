#include <iostream>
#include <string>
#include <algorithm>

std::string addBaseB(const std::string& num1, const std::string& num2, int base) {
    std::string n1 = num1, n2 = num2;

    // Accounting when one of the values has a different length to the other number 

    while (n1.length() < n2.length()) {
        n1 = n1 + '0'; 
    }

    while (n2.length() < n1.length()) {
        n2 = n2 + '0';
    }

    // Initialise result and carry

    std::string result = "";
    int carry = 0;

    // Performing Addition 

    for (int i = n1.length() - 1; i >= 0; i--) {
        // ASCII conversion
        int n1Digit = n1[i] - '0';
        int n2Digit = n2[i] - '0';

        // Calculating Result
        int sum = n1Digit + n2Digit + carry;
        carry = sum / base;
        sum %= base; 

        result = std::to_string(sum) + result;
    }
    // Acount for carry 
    if (carry > 0) {
        result = std::to_string(carry) + result;
    }

return result;
}

std::string subBaseB(const std::string& num1, const std::string& num2, int base) {
    std::string n1 = num1, n2 = num2; 

    while(n1.length() < n2.length()) {
        n1 = n1 + '0';
    }
    
    while (n2.length() < n1.length()) {
        n2 = n2 + '0';
    }

    std::string result = ""; 
    int borrow = 0; 

    for (int i = n1.length() - 1; i >=0; i--) {
        int n1Digit = n1[i] - '0';
        int n2Digit = n2[i] - '0';

        int diff = n1Digit - n2Digit - borrow;

        if (diff < 0) {
            diff += base;
            borrow = 1;
        } else {
            borrow = 0;
        }
         result =  std::to_string(diff) + result;
    }

    while (n1.length() > 1 && result[0] == '0') {
        result = result.substr(1);
    }
   
   return result;

}


int main() {
    int val1 = 0;
    int val2 = 0; 
    int base = 0;

    std::cout << "Enter Value 1: " << std::endl;
    std::cin >> val1;
    std::cout << "Enter Value 2: " << std::endl;
    std::cin >> val2; 
    std::cout << "Enter Base: " << std::endl;
    std::cin >> base;

    std::cout << "School addition result: " << addBaseB(std::to_string(val1), std::to_string(val2), base) << std::endl;
    std::cout << "Substraction result: " << subBaseB(std::to_string(val1), std::to_string(val2), base) << std::endl;

}

