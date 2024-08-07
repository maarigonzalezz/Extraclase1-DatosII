//
// Created by gonza on 03/08/2024.
//

#include "Parser.h"


void Parser::parseCommand(const std::string& comando) {
    std::regex token_regex(R"((\"[^\"]+\"|\S+))");
    auto tokens_begin = std::sregex_iterator(comando.begin(), comando.end(), token_regex);
    auto tokens_end = std::sregex_iterator();

    std::vector<std::string> tokens;
    for (auto it = tokens_begin; it != tokens_end; ++it) {
        tokens.push_back(it->str());
    }

    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i] == "-input" && i + 1 < tokens.size()) {
            inputFile = tokens[i + 1];
            inputFile.erase(std::remove(inputFile.begin(), inputFile.end(), '\"'), inputFile.end());
        }
        if (tokens[i] == "-output" && i + 1 < tokens.size()) {
            outputFile = tokens[i + 1];
            outputFile.erase(std::remove(outputFile.begin(), outputFile.end(), '\"'), outputFile.end());
        }
        if (tokens[i] == "-alg" && i + 1 < tokens.size()) {
            alg = tokens[i + 1];
        }
    }

    std::cout << "el input es: " << inputFile << " el output es " << outputFile << " algo: " << alg << std::endl;

    PagedArray arr(inputFile, outputFile);
    Sorters sorters(&arr, alg);
    cout << arr[1];

    std::cout << "Page Hits: " << arr.getPageHits() << std::endl;
    std::cout << "Page Faults: " << arr.getPageFaults() << std::endl;
}