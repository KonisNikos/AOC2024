#include <algorithm>
#include <cmath>
#include <iostream>
#include <istream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace Part1{
    bool isVectorValid(std::vector<int>& vector){
        if(vector[1] == vector[0]){
            return false;
        } 
        bool isDecreasing = vector[1] < vector[0];
        for(auto it = vector.begin() + 1; it != vector.end(); ++it){
            int number = *it;
            int previousNumber = *(it - 1);
            int difference = (number - previousNumber) * pow(-1, isDecreasing);
            if(difference < 1 || difference > 3){
                return false;
            }
        }
        return true;
    }
    int countValidVectors(std::vector<std::vector<int>>& matrix){
        int count = 0;
        for(std::vector<int>& vector : matrix){
            if(isVectorValid(vector)){
                count++;
            }
        }
        return count; 
    }
}
namespace Part2 {
    bool isVectorValid(std::vector<int>& vector){
        if(vector[1] == vector[0]){
            vector.erase(vector.begin());
            return Part1::isVectorValid(vector);
        } 
        bool isDecreasing = vector[1] < vector[0];
        for(auto it = vector.begin() + 1; it != vector.end(); ++it){
            int number = *it;
            int previousNumber = *(it - 1);
            int difference = (number - previousNumber) * pow(-1, isDecreasing);
            if(difference == 1 || difference == 2 || difference == 3){
                continue;
            }
            bool isCopiedVectorValid;
            std::vector<int> copyVector;
            copyVector.reserve(vector.size());

            std::copy(vector.begin(), it-1, std::back_inserter(copyVector));
            auto copyIt = copyVector.end();
            std::copy(it, vector.end(), std::back_inserter(copyVector));

            isCopiedVectorValid = Part1::isVectorValid(copyVector);

            *copyIt = previousNumber;
            isCopiedVectorValid |= Part1::isVectorValid(copyVector);

            copyVector.insert(copyIt+1, number);
            copyVector.erase(copyVector.begin());

            isCopiedVectorValid |= Part1::isVectorValid(copyVector);
            return isCopiedVectorValid;
        }
        return true;
    }

    int countValidVectors(std::vector<std::vector<int>>& matrix){
        int count = 0;
        for(std::vector<int>& vector : matrix){
            if(isVectorValid(vector)){
                count++;
            }
        }
        return count; 
    }
}

int main(){
    std::vector<std::vector<int>> matrix;
    std::string line;
    while(true){
        std::vector<int> vector;
        std::getline(std::cin, line);
        if(line.empty()){
            break;
        }
        std::istringstream lineStream(line);
        int number;
        while(lineStream >> number){
            vector.push_back(number);
        }
        matrix.push_back(vector);
        line.erase();
    }
    int validVectors = Part1::countValidVectors(matrix); 
    std::cout << validVectors << "\n";
    return 0;
}