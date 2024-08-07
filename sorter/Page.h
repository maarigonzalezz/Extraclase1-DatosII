//
// Created by gonza on 04/08/2024.
//

#ifndef PAGE_H
#define PAGE_H
#include <iostream>
#include <filesystem>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>
#include <random>
#include <direct.h> // para _chdir
#include <cerrno>

const int PAGE_SIZE = 512; // Tamaño de página en enteros
const int NUM_PAGES = 4;   // Número de páginas en memoria

using namespace std;
class Page {
public:
    string inputFile;
    string outputFile;
    int a[PAGE_SIZE];
    int id;
    bool ready = false;
    //Constructor
    Page() = default;
    Page(string input, string output){
        inputFile = move(input);
        outputFile = move(output);
    }

    void uploadContent(const string &inputFile);
    void downloadContent(const string &outputFile);

    // Destructor
    ~Page() {
        delete[] a; // Libera la memoria del array
    }

};



#endif //PAGE_H
