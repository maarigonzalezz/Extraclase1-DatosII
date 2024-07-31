#ifndef GENERATOR_H
#define GENERATOR_H
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>
#include <random>
#include <direct.h> // para _chdir
#include <cerrno>   // para errno

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

        const char* path = outputFile.c_str();

        if (_chdir(path) == 0) {
            std::cout << "Directorio cambiado exitosamente a: " << path << std::endl;
        } else {
            std::cerr << "Error al cambiar de directorio: " << strerror(errno) << std::endl;
        }

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
        size_t sizeStart = command.find("<") + 1;
        size_t sizeEnd = command.find(">");
        size = command.substr(sizeStart, sizeEnd - sizeStart);
        cout<< size<< endl;

        size_t outputFileStart = command.find("<", sizeEnd) + 1;
        size_t outputFileEnd = command.find(">", outputFileStart);
        outputFile = command.substr(outputFileStart, outputFileEnd - outputFileStart);
        cout<< outputFile;

        filegenerator(size, outputFile);
    }

    void auxiliar(const string& s, const string& j)
    {
        filegenerator(s,j);
    }

};


#endif //GENERATOR_H
