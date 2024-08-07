//
// Created by gonza on 30/07/2024.
//

#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H
#include <iostream>
#include "Page.h"
#include <fstream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>

#define PAGE_SIZE 256 // Tamaño de cada página (número de enteros)
#define NUM_PAGES 4   // Número máximo de páginas en memoria

using namespace std;
class PagedArray {
public:
    PagedArray(const std::string& inputFilePath, const std::string& outputFilePath);
    ~PagedArray();

    int& operator[](int index);
    int getPageFaults() const;
    int getPageHits() const;
    int getFileSize() const;

private:
    std::string filePath;
    std::fstream file;
    int* pages[NUM_PAGES];
    int pageIndices[NUM_PAGES];
    bool pageLoaded[NUM_PAGES];
    int pageFaults;
    int pageHits;

    void loadPage(int pageIndex);
    void savePage(int pageSlot);
    int getPageIndex(int index) const;
    int getOffset(int index) const;
};




#endif //PAGEDARRAY_H
