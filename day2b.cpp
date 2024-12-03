#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>     // For std::abs

// Function to check if a report is safe
bool isSafe(const std::vector<int>& report) {
    if (report.size() < 2) {
        return false; // Reports must have at least two levels to evaluate
    }

    bool increasing = true;
    bool decreasing = true;
    int probCount = 0;
    int temp = 0;

    for (size_t i = 1; i < report.size(); ++i) {
        int diff = report[i] - report[i - 1];

        // Check if the difference is out of range
        if (std::abs(diff) < 1 || std::abs(diff) > 3) {
            return false;
        }

        // Check if the sequence is not consistently increasing or decreasing
        if (diff > 0) {
            decreasing = false; // It's increasing
        } else if (diff < 0) {
            increasing = false; // It's decreasing
        } else if (diff == 0) {
            return false; // It has no difference and therefore unsafe
        }
    }

    // Report is safe if it is either fully increasing or fully decreasing
    return increasing || decreasing;
}

// Function to simulate element removal and return states
std::vector<std::vector<int>> simulateRemovals(const std::vector<int>& inputVector) {
    std::vector<std::vector<int>> results;

    for (size_t i = 0; i < inputVector.size(); ++i) {
        // Make a copy of the original vector
        std::vector<int> modifiedVector = inputVector;

        // Remove the element at index i
        modifiedVector.erase(modifiedVector.begin() + i);

        // Store the resulting vector
        results.push_back(modifiedVector);
    }

    return results;
}

int main() {
    // File path for input data
    std::string filePath = "inputsday2new.txt";

    // Open the file
    std::ifstream inputFile(filePath);

    // Parse the reports
    std::vector<std::vector<int>> reports;
    std::string line;
    int safeCount = 0;
    while (std::getline(inputFile, line)) {
        std::vector<int> report;
        std::stringstream ss(line);
        int level;

        while (ss >> level) {
            report.push_back(level);
        }
        bool safe = false;
        if (isSafe(report)) {
            safe = true;
        } else {
            std::vector<std::vector<int>> removedCases = simulateRemovals(report);
            
            for (size_t i = 0; i < removedCases.size(); ++i) {
                if (isSafe(removedCases[i])){
                    safe = true;
                }
            
            }
        }
        if (safe == true){
            safeCount ++;
        }
    }
        
    inputFile.close();

    std::cout << safeCount;
}
