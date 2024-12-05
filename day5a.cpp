#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

bool followsRules(const std::vector<int>& ordering, const std::vector<std::pair<int, int>>& rules) {
    for (const auto& rule : rules) {
        int X = rule.first;
        int Y = rule.second;

        // Find positions of X and Y in the list
        auto posX = std::find(ordering.begin(), ordering.end(), X);
        auto posY = std::find(ordering.begin(), ordering.end(), Y);

        // Check if both X and Y are present and that X comes before Y
        if (posX != ordering.end() && posY != ordering.end() && posX > posY) {
            return false; // Rule violated: X comes after Y
        }
    }
    return true; // All rules satisfied
}

int main() {
    // File path to the text file
    std::string filePath = "inputsday5.txt";

    // Input file stream
    std::ifstream inputFile(filePath);

    std::vector<std::string> lines;
    std::vector<std::pair<int,int>> rules;
    std::vector<std::vector<int>> updates;

    std::string line;
    while (std::getline(inputFile, line)) {   
        if (line.size() == 5) {
            int firstNumber = std::stoi(line.substr(0, 2));
            int secondNumber = std::stoi(line.substr(3, 5));
            rules.push_back(std::make_pair(firstNumber,secondNumber));
        } else if (line.size() > 5) {
            std::vector<int> numbers;          // Temporary vector for the current line
            std::stringstream ss(line);       // Use stringstream to parse the line
            std::string number;

            // Parse numbers separated by commas
            while (std::getline(ss, number, ',')) {
                numbers.push_back(std::stoi(number)); // Convert string to int and add to vector
            }
            updates.push_back(numbers); // Add parsed numbers to the main list of lists
        }
    }
    
    // Close the file
    inputFile.close();

    int count = 0;

    // Check each ordering
    for (size_t i = 0; i < updates.size(); ++i) {
        if (followsRules(updates[i], rules)) {
            count += updates[i][floor((updates[i].size())/2)];
        }
    }
    std::cout << count;
}