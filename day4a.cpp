#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Function which returns all coordinates within the valid range around an origin
std::vector<std::pair<int,int>> searchAround (std::pair<int,int> orig) {
    int ii = orig.first;
    int jj = orig.second;
    std::vector<std::pair<int,int>> toSearch;
    if ((ii < 3) && (jj < 3)) { // top left corner
        toSearch = {std::make_pair(ii,jj+1), std::make_pair(ii+1,jj), std::make_pair(ii+1,jj+1)};
    } else if ((ii < 3) && (jj > 136)) {  // top right corner
        toSearch = {std::make_pair(ii,jj-1), std::make_pair(ii+1,jj-1), std::make_pair(ii+1,jj)};
    } else if ((ii > 136) && (jj < 3)) { // bottom left corner
        toSearch = {std::make_pair(ii-1,jj), std::make_pair(ii-1,jj+1), std::make_pair(ii,jj+1)};
    } else if ((ii > 136) && (jj > 136)) { // bottom right corner
        toSearch = {std::make_pair(ii,jj-1), std::make_pair(ii-1,jj-1), std::make_pair(ii-1,jj)};
    } else if (ii < 3) { // top edge middle
        toSearch = {std::make_pair(ii,jj-1), std::make_pair(ii+1,jj-1), std::make_pair(ii+1,jj), std::make_pair(ii+1,jj+1), std::make_pair(ii,jj+1)};
    } else if (ii > 136) { // bottom edge middle
        toSearch = {std::make_pair(ii,jj-1), std::make_pair(ii-1,jj-1), std::make_pair(ii-1,jj), std::make_pair(ii-1,jj+1), std::make_pair(ii,jj+1)};
    } else if (jj < 3) { // left edge middle
        toSearch = {std::make_pair(ii-1,jj), std::make_pair(ii-1,jj+1), std::make_pair(ii,jj+1), std::make_pair(ii+1,jj+1), std::make_pair(ii+1,jj)};
    } else if (jj > 136) { // right edge middle
        toSearch = {std::make_pair(ii-1,jj), std::make_pair(ii-1,jj-1), std::make_pair(ii,jj-1), std::make_pair(ii+1,jj-1), std::make_pair(ii+1,jj)};
    } else { // middle
        toSearch = {std::make_pair(ii-1,jj-1), std::make_pair(ii-1,jj), std::make_pair(ii-1,jj+1), std::make_pair(ii,jj+1), std::make_pair(ii+1,jj+1), std::make_pair(ii+1,jj), std::make_pair(ii+1,jj-1), std::make_pair(ii,jj-1)};
    }
    return toSearch;
}

// Function to search for a valid branch when an "M" is found adjacent to an "X"
int findRest(std::pair<int,int> orig, std::vector<std::pair<int,int>> further1, std::vector<std::string> lines, std::vector<char> xmas) {
    int ii = orig.first;
    int jj = orig.second;
    int branches = 0;
    for (int sl2 = 0; sl2 < further1.size(); ++sl2) {
        if ((((further1[sl2].first == ii-1) && (further1[sl2].second == jj-1)) && (lines[ii-2][jj-2] == xmas[2]) && (lines[ii-3][jj-3] == xmas[3])) // top left
        || (((further1[sl2].first == ii-1) && (further1[sl2].second == jj)) && (lines[ii-2][jj] == xmas[2]) && (lines[ii-3][jj] == xmas[3])) // top middle
        || (((further1[sl2].first == ii-1) && (further1[sl2].second == jj+1)) && (lines[ii-2][jj+2] == xmas[2]) && (lines[ii-3][jj+3] == xmas[3])) // top right
        || (((further1[sl2].first == ii) && (further1[sl2].second == jj+1)) && (lines[ii][jj+2] == xmas[2]) && (lines[ii][jj+3] == xmas[3])) // middle right
        || (((further1[sl2].first == ii+1) && (further1[sl2].second == jj+1)) && (lines[ii+2][jj+2] == xmas[2]) && (lines[ii+3][jj+3] == xmas[3])) // bottom right
        || (((further1[sl2].first == ii+1) && (further1[sl2].second == jj)) && (lines[ii+2][jj] == xmas[2]) && (lines[ii+3][jj] == xmas[3])) // botttom middle
        || (((further1[sl2].first == ii+1) && (further1[sl2].second == jj-1)) && (lines[ii+2][jj-2] == xmas[2]) && (lines[ii+3][jj-3] == xmas[3])) // bottom left
        || (((further1[sl2].first == ii) && (further1[sl2].second == jj-1)) && (lines[ii][jj-2] == xmas[2]) && (lines[ii][jj-3] == xmas[3])) ) { // middle left
            branches++;
        }
    }
    return branches;
 }


int main() {
    // File path to the text file
    std::string filePath = "inputsday4.txt";

    // Input file stream
    std::ifstream inputFile(filePath);

    // Vectors to store the file and target string
    std::vector<std::string> lines;
    std::vector<char> xmas = {'X','M','A','S'};

    std::string line;
    while (std::getline(inputFile, line)) {       
        std::string sub = line.substr(0, 140); 
        lines.push_back(sub);
    }

    int count = 0;
    std::vector<std::pair<int,int>> further1;

    // Search for "XMAS" pattern
    for (int i = 0; i < 140; ++i) {
        for (int j = 0; j < 140; ++j) {
            if (lines[i][j] == xmas[0]){
                std::vector<std::pair<int,int>> searchList = searchAround(std::make_pair(i,j)); 
                std::vector<std::pair<int,int>> further1 = {};
                for (int sl1 = 0; sl1 < searchList.size(); ++sl1) {
                    if (lines[(searchList[sl1].first)][(searchList[sl1].second)] == xmas[1]){
                        further1.push_back(searchList[sl1]);
                    }  
                }
                count += (findRest(std::make_pair(i,j), further1, lines, xmas));
            }
        }
    }    


    // Close the file
    inputFile.close();
    std::cout << count;
}