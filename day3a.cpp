#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype> // For std::isdigit

int main() {
    std::string filename = "inputsday3.txt";

    std::ifstream file(filename); // Open the file

    // Read the entire file content into a single string
    std::string fullContent((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
    file.close(); // Close the file

    int numsToAdd = 0;

    // Loop through the string and find "mul("
    for (size_t i = 0; i + 2 < fullContent.size(); ++i) {
        if (fullContent.substr(i, 4) == "mul(") {
                     
             // Temporary variables to collect digits
            std::string dBuffer1;
            std::string dBuffer2;

            bool allDigits = true; // Flag to ensure all characters are digits

            // Check for digits after "mul(" until a comma
            size_t j = i + 4; // Start checking after "mul("
            while (j < fullContent.size() && fullContent[j] != ',') {
                if (std::isdigit(fullContent[j])) {
                    dBuffer1 += fullContent[j]; // Append digit to buffer
                } else {
                    allDigits = false; // Found a non-digit character
                }
                ++j;
            }
            int commaIndex = 0;
            if (j < fullContent.size() && fullContent[j] == ',') {
                commaIndex = j;
            }

            // If all characters are digits, convert to an integer and store
            if (allDigits && !dBuffer1.empty()) {
                int num1 = std::stoi(dBuffer1); // Convert to integer
                

                // Check for digits after comma until a ")"
                size_t k = commaIndex + 1; // Start checking after comma
                
                while (k < fullContent.size() && fullContent[k] != ')') {
                    if (std::isdigit(fullContent[k])) {
                        dBuffer2 += fullContent[k]; // Append digit to buffer
                    } else {
                        allDigits = false; // Found a non-digit character
                    }
                    ++k;
                }
                if (allDigits && !dBuffer2.empty()) {
                    int num2 = std::stoi(dBuffer2); // Convert to integer
                    
                    numsToAdd += (num1 * num2);
                }
            }
        }
    }
    std::cout << numsToAdd;
    
    
}