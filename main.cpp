#include <iostream>
#include <string>
#include <algorithm>

std::string addBaseB(const std::string& num1, const std::string& num2, int base) {
    std::string n1 = num1, n2 = num2;

    // Accounting when one of the values has a different length to the other number 

    while (n1.length() < n2.length()) {
        n1 = '0' + n1; 
    }

    while (n2.length() < n1.length()) {
        n2 = '0' + n2;
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

   while (n1.length() < n2.length()) {
        n1 = '0' + n1; 
    }

    while (n2.length() < n1.length()) {
        n2 = '0' + n2;
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

std::string karatsuba(std::string num1, std::string num2, int base) {
  size_t n = std::max(num1.size(), num2.size());
  if (n == 1) {
    int mul = (num1[0] - '0') * (num2[0] - '0');
    if (mul < base)
      return std::to_string(mul);
    else {
      // Handle the case where multiplication results in a number >= base
      int secondDigit = mul % base;
      int firstDigit = mul / base;
      return std::to_string(firstDigit) + std::to_string(secondDigit);
    }
  }
  while (num1.size() < n) num1.insert(0, "0");
  while (num2.size() < n) num2.insert(0, "0");
  std::string a = num1.substr(0, n / 2);
  std::string b = num1.substr(n / 2, n - n / 2);
  std::string c = num2.substr(0, n / 2);
  std::string d = num2.substr(n / 2, n - n / 2);
  std::string ac = karatsuba(a, c, base);
  std::string bd = karatsuba(b, d, base);
  std::string abcd =
      karatsuba(addBaseB(a, b, base), addBaseB(c, d, base), base);
  abcd = subBaseB(abcd, addBaseB(ac, bd, base), base);
  size_t k = n - n / 2;
  for (size_t i = 0; i < 2 * k; i++) ac += "0";  // Multiply ac by B^2k
  for (size_t i = 0; i < k; i++) abcd += "0";    // Multiply abcd by B^k
  std::string result = addBaseB(addBaseB(ac, abcd, base), bd, base);

  // Remove leading zeros from result
  size_t startpos = result.find_first_not_of("0");
  if (startpos != std::string::npos) result = result.substr(startpos);
  return result.empty() ? "0" : result;
}


int main() {
    std::string n1,n2;
    int base;
    std::cin >> n1 >> n2 >>  base;

    std::cout << addBaseB(n1, n2, base) << std::endl;
    std::cout << subBaseB(n1, n2, base) << std::endl;
    std::cout << karatsuba(n1, n2, base) << std:: endl;

}

