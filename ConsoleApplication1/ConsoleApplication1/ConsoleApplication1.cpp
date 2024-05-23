#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Function to create a text file
void createTextFile(const std::string& fileName) {
    std::ofstream outFile(fileName);
    if (!outFile) {
        std::cerr << "Error creating file." << std::endl;
        return;
    }
    std::cout << "Enter text to save to the file (enter 'END' to finish input):" << std::endl;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "END") break;
        outFile << line << std::endl;
    }
    outFile.close();
}

// Function to create a copy of the file
void copyFile(const std::string& sourceFileName, const std::string& destFileName) {
    std::ifstream inFile(sourceFileName);
    std::ofstream outFile(destFileName);
    if (!inFile || !outFile) {
        std::cerr << "Error copying file." << std::endl;
        return;
    }
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    outFile << buffer.str();
    inFile.close();
    outFile.close();
}

// Function to replace a word in the file
void replaceWordInFile(const std::string& fileName, const std::string& oldWord, const std::string& newWord) {
    std::ifstream inFile(fileName);
    if (!inFile) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string content = buffer.str();
    size_t pos = 0;
    while ((pos = content.find(oldWord, pos)) != std::string::npos) {
        content.replace(pos, oldWord.length(), newWord);
        pos += newWord.length();
    }
    inFile.close();
    std::ofstream outFile(fileName);
    if (!outFile) {
        std::cerr << "Error writing to file." << std::endl;
        return;
    }
    outFile << content;
    outFile.close();
}

// Function to display the menu
void displayMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Create a text file\n";
    std::cout << "2. Make a copy of the file\n";
    std::cout << "3. Replace a word in the file\n";
    std::cout << "4. Exit\n";
}

// Function to handle user input errors
int getValidatedChoice() {
    int choice;
    while (true) {
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid choice. Please try again.\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return choice;
}

int main() {
    std::string fileName;
    std::string copyFileName;
    std::string oldWord, newWord;
    while (true) {
        displayMenu();
        int choice = getValidatedChoice();
        switch (choice) {
        case 1:
            std::cout << "Enter the name of the file to create: ";
            std::getline(std::cin, fileName);
            createTextFile(fileName);
            break;
        case 2:
            std::cout << "Enter the name of the source file: ";
            std::getline(std::cin, fileName);
            std::cout << "Enter the name of the copy file: ";
            std::getline(std::cin, copyFileName);
            copyFile(fileName, copyFileName);
            break;
        case 3:
            std::cout << "Enter the name of the file: ";
            std::getline(std::cin, fileName);
            std::cout << "Enter the word to replace: ";
            std::getline(std::cin, oldWord);
            std::cout << "Enter the new word: ";
            std::getline(std::cin, newWord);
            replaceWordInFile(fileName, oldWord, newWord);
            break;
        case 4:
            std::cout << "Exiting the program." << std::endl;
            return 0;
        default:
            std::cerr << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}
