#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // For std::sort
#include <cmath>     // For std::abs
#include <numeric>   // For std::accumulate

int main() {
    // File path to the text file
    std::string filePath = "inputsday1.txt";

    // Input file stream
    std::ifstream inputFile(filePath);

    // Vectors to store the numbers
    std::vector<int> firstNumbers;
    std::vector<int> secondNumbers;

    std::string line;
    while (std::getline(inputFile, line)) {
        // Parse the two numbers from the line
        if (line.length() >= 13) { // Ensure the line is long enough
            int firstNumber = std::stoi(line.substr(0, 5));  // First 5 digits
            int secondNumber = std::stoi(line.substr(8, 5)); // Second 5 digits (after 3 spaces)
            
            // Add the numbers to the respective lists
            firstNumbers.push_back(firstNumber);
            secondNumbers.push_back(secondNumber);
        }
    }

    // Close the file
    inputFile.close();

    // Sort both lists
    std::sort(firstNumbers.begin(), firstNumbers.end());
    std::sort(secondNumbers.begin(), secondNumbers.end());

    // Compute differences and store in a third list
    std::vector<int> differences;
    for (size_t i = 0; i < firstNumbers.size(); ++i) {
        int diff = std::abs(firstNumbers[i] - secondNumbers[i]);
        differences.push_back(diff);
    }

    // Sum up all differences
    int totalDifference = std::accumulate(differences.begin(), differences.end(), 0);

    // Print the total difference
    std::cout << "Total Difference: " << totalDifference << std::endl;

    return 0;
}