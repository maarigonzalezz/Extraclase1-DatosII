#ifndef GENERATOR_H
#define GENERATOR_H
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>

using namespace std;
class Generator{
private:
    string size, outputFile;

    void filegenerator(const string& size, const string& outputfile){
        ofstream file(outputFile, ios::binary);

        if (size == "<SMALL>"){

        } else if (size == "<MEDIUM>"){

        }else if (size == "<LARGE>"){

        } else{
            cout << "No existe archivo de ese tamaño";
        }

        int p = 1010;
        file.write((char*)&p, 4);

        file.close();
    }
public:
    Generator() = default;
    Generator(string  size, string  outputFile)
    : size(std::move(size)), outputFile(std::move(outputFile)) {}

    // Métodos para obtener los valores de los atributos
    [[nodiscard]] string getSize() const { return size; }
    [[nodiscard]] string getOutputFile() const { return outputFile; }

    // Métodos para establecer los valores de los atributos
    void setSize(const string& newSize){
        size = newSize;
    }
    void setOutputFile(const string& newOutputFile){
        outputFile = newOutputFile;
    }

    // Método para parsear el comando
    void parseCommand(const string& command) {
        istringstream stream(command);
        string token;

        while (stream >> token) {
            if (token == "-size") {
                stream >> size;
                cout << size;
            } else if (token == "-output") {
                stream >> outputFile;
                cout << outputFile;
            }
            filegenerator(size, outputFile);
        }
    }
};


#endif //GENERATOR_H
