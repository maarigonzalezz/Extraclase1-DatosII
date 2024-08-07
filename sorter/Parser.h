//
// Created by gonza on 03/08/2024.
//

#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <vector>
#include <sstream>
#include <regex>
#include "PagedArray.h"
#include "Sorters.h"

using namespace std;
class Parser {
public:
    string inputFile;
    string alg;
    string outputFile;

    Parser() = default;

    void parseCommand(const string& comando);

};



#endif //PARSER_H
