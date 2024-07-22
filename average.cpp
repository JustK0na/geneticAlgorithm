#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char **argv){

    std::string filename=argv[1];
    std::ifstream file(filename);

     if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }
    int number;
    int sum = 0;
    int count = 0;
    // Read integers from the file
    while (file >> number) {
        sum += number;
        count++;
    }

    file.close();

    // Calculate and display the average
    if (count > 0) {
        double average = static_cast<double>(sum) / count;
        std::cout << "Average: " << average << std::endl;
    } else {
        std::cout << "No valid integers found in the file." << std::endl;
    }
    return 0;
}