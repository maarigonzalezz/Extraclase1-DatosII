//
// Created by gonza on 31/07/2024.
//

#ifndef SORTERS_H
#define SORTERS_H

#include <iostream>
#include <vector>
#include "PagedArray.h"


class Sorters {
public:
    Sorters() = default;

    Sorters(PagedArray* arr, const std::string& alg) {
        int n = arr->getFileSize();
        if (alg == "QS") {
            quickSort(arr, 0, n - 1);
        } else if (alg == "IS") {
            insertionSort(arr, n);
        } else if (alg == "BS") {
            bubbleSort(arr, n);
        } else {
            std::cerr << "Algoritmo no identificado" << std::endl;
        }
    }

    // Quick Sort
    void quickSort(PagedArray* arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    // Insertion Sort
    void insertionSort(PagedArray* arr, int size) {
        for (int i = 1; i < size; ++i) {
            int key = (*arr)[i];
            int j = i - 1;
            while (j >= 0 && (*arr)[j] > key) {
                (*arr)[j + 1] = (*arr)[j];
                j = j - 1;
            }
            (*arr)[j + 1] = key;
        }
    }

    // Bubble Sort
    void bubbleSort(PagedArray* arr, int size) {
        bool swapped;
        for (int i = 0; i < size - 1; ++i) {
            swapped = false;
            for (int j = 0; j < size - i - 1; ++j) {
                if ((*arr)[j] > (*arr)[j + 1]) {
                    std::swap((*arr)[j], (*arr)[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }
    }

private:
    int partition(PagedArray* arr, int low, int high) {
        int pivot = (*arr)[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; ++j) {
            if ((*arr)[j] <= pivot) {
                i++;
                std::swap((*arr)[i], (*arr)[j]);
            }
        }
        std::swap((*arr)[i + 1], (*arr)[high]);
        return (i + 1);
    }
};




#endif //SORTERS_H
