#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Function which returns all diagonal coordinates within the valid range around an origin ("A")
std::vector<std::pair<int,int>> searchAround (std::pair<int,int> orig) {
    int ii = orig.first;
    int jj = orig.second;
    std::vector<std::pair<int,int>> toSearch;
    if ((ii > 0) && (ii < 139) && (jj > 0) && (jj < 139)) {
        toSearch = {std::make_pair(ii-1,jj-1), std::make_pair(ii-1,jj+1), std::make_pair(ii+1,jj+1), std::make_pair(ii+1,jj-1)};
    }
    return toSearch;
}

int main() {
    // File path to the text file
    std::string filePath = "inputsday4.txt";

    // Input file stream
    std::ifstream inputFile(filePath);

    // Vectors to store the file and target string
    std::vector<std::string> lines;
    std::vector<char> xmas = {'M','A','S'};

    std::string line;
    while (std::getline(inputFile, line)) {       
        std::string sub = line.substr(0, 140); 
        lines.push_back(sub);
    }

    int count = 0;
    std::vector<std::pair<int,int>> further1;
    

    // Search for "X-MAS" pattern
    for (int i = 0; i < 140; ++i) {
        for (int j = 0; j < 140; ++j) {
            if (lines[i][j] == xmas[1]){ // if an "A" is found
                std::vector<std::pair<int,int>> searchList = searchAround(std::make_pair(i,j)); 
                std::vector<std::pair<int,int>> further1 = {};
                bool isItXmas = false;
                for (int sl1 = 0; sl1 < searchList.size(); ++sl1) {
                    if ((lines[(searchList[sl1].first)][(searchList[sl1].second)] == xmas[0])
                    && (lines[(searchList[(sl1 + 2) % 4].first)][(searchList[(sl1 + 2) % 4].second)] == xmas[2])
                    && (((lines[(searchList[(sl1 + 1) % 4].first)][(searchList[(sl1 + 1) % 4].second)] == xmas[0]) && (lines[(searchList[(sl1 + 3) % 4].first)][(searchList[(sl1 + 3) % 4].second)] == xmas[2]))
                    || ((lines[(searchList[(sl1 + 1) % 4].first)][(searchList[(sl1 + 1) % 4].second)] == xmas[2]) && (lines[(searchList[(sl1 + 3) % 4].first)][(searchList[(sl1 + 3) % 4].second)] == xmas[0]))) ) {
                        isItXmas = true;
                    }  
                }
                count += isItXmas ? 1 : 0;
                
            }
        }
    }    

    // Close the file
    inputFile.close();
    std::cout << count;
}