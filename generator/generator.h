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
    const long long largeSize = 2LL * 1024 * 1024 * 1024; // 2 GB



    void filegenerator(const string& size, const string& outputFile) const {
        cout << "alo";
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, numeric_limits<int>::max());

        const char* path = outputFile.c_str();

        if (_chdir(path) == 0) {
            std::cout << "Directorio cambiado exitosamente a: " << path << std::endl;
        } else {
            std::cerr << "Error al cambiar de directorio: " << strerror(errno) << std::endl;
        }

        ofstream file("test.bin", ios::binary);

        long long a = 0;
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

        for (long long i = 0; i < a; ++i) {
            int p = dis(gen);
            file.write(reinterpret_cast<char*>(&p), 4);
        }

        cout << "listovv";
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
        istringstream iss(command);
        string token;
        vector<std::string> tokens;

        while (iss >> token) {
            tokens.push_back(token);
        }

        // Recorremos los tokens para encontrar -size y -output
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "-size" && i + 1 < tokens.size()) {
                size = tokens[i + 1];
            }
            if (tokens[i] == "-output" && i + 1 < tokens.size()) {
                outputFile = tokens[i + 1];
                for (size_t j = i + 2; j < tokens.size(); ++j) {
                    outputFile += " " + tokens[j];
                }
                break; // Ya encontramos y procesamos el output, podemos salir del bucle
            }
        }

        filegenerator(size, outputFile);
    }

    void auxiliar(const string& s, const string& j)
    {
        filegenerator(s,j);
    }

};


#endif //GENERATOR_H
