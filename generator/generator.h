#ifndef GENERATOR_H
#define GENERATOR_H
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>
#include <random>

using namespace std;

class Generator {
private:
    string size, outputFile;

    const int smallSize = 512 * 1024 * 1024; // 512 MB
    const int mediumSize = 1024 * 1024 * 1024; // 1 GB
    const int largeSize = 2 * 1024 * 1024 * 1024; // 2 GB

    int nums[16] = {0b0000, 0b0001, 0b0010, 0b0011, 0b0100, 0b0101, 0b0110, 0b0111,
                    0b1000, 0b1001, 0b1010, 0b1011, 0b1100, 0b1101, 0b1110, 0b1111};

    void filegenerator(const string& size, const string& outputFile) {
        cout << "alo";
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 15);
        ofstream file("test.bin", ios::binary);

        int a = 0;
        if (size == "SMALL") {
            a = smallSize / 4;
        } else if (size == "MEDIUM") {
            a = mediumSize / 4;
        } else if (size == "LARGE") {
            a = largeSize / 4;
        } else {
            cerr << "No existe archivo de ese tamaño" << endl;
            return;
        }

        for (int i = 0; i < a; ++i) {
            int p = nums[dis(gen)];
            file.write(reinterpret_cast<char*>(&p), 4);
        }

        file.close();
    }

public:
    Generator() = default;
    Generator(string size, string outputFile)
        : size(std::move(size)), outputFile(std::move(outputFile)) {}

    [[nodiscard]] string getSize() const { return size; }
    [[nodiscard]] string getOutputFile() const { return outputFile; }

    void setSize(const string& newSize) {
        size = newSize;
    }

    void setOutputFile(const string& newOutputFile) {
        outputFile = newOutputFile;
    }

    void parseCommand(const string& command) {
        istringstream stream(command);
        string token;
        string size;
        string outputFile;

        while (stream >> token) {
            if (token == "-size") {
                stream >> token;
                size = extractValue(token);
                cout << "Size: " << size << endl;
            } else if (token == "-output") {
                stream >> token;
                outputFile = extractValue(token);
                cout << "Output File: " << outputFile << endl;
            }
        }

        // Trim spaces from extracted values
        size = trim(size);
        outputFile = trim(outputFile);

        if (!size.empty() && !outputFile.empty()) {
            filegenerator(size, outputFile);
            cout << "llego aquu";
        } else {
            cerr << "Error: Invalid size or output file." << endl;
        }
    }

    static string extractValue(const string& token) {
        size_t start = token.find('<');
        size_t end = token.find('>');

        if (start != string::npos && end != string::npos && start < end) {
            return token.substr(start + 1, end - start - 1);
        } else {
            return "";
        }
    }

    static string trim(const string& str) {
        size_t start = str.find_first_not_of(' ');
        size_t end = str.find_last_not_of(' ');

        if (start == string::npos) return ""; // no content

        return str.substr(start, end - start + 1);
    }
};


#endif //GENERATOR_H
