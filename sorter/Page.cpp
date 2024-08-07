//
// Created by gonza on 04/08/2024.
//

#include "Page.h"

void Page::uploadContent(const string &inputFile) {
    std::ifstream archivo(inputFile, std::ios::binary); // Abre el archivo en modo binario

    // Mover el puntero a la posición deseada dentro del archivo
    archivo.seekg((id - 1) * PAGE_SIZE * sizeof(int), std::ios::beg);

    int i = 0;
    while (i < PAGE_SIZE) {
        archivo.read(reinterpret_cast<char*>(&a[i]), sizeof(int));
        i++;
    }
    ready = true;
    archivo.close(); // Cierra el archivo
}

void Page::downloadContent(const string &outputFile) {
    // Abrir el archivo en modo binario para escritura
    std::ofstream archivo(outputFile, std::ios::binary | std::ios::in | std::ios::out);

    // Mover el puntero a la posición deseada dentro del archivo
    archivo.seekp((id - 1) * PAGE_SIZE * sizeof(int), std::ios::beg);

    int i = 0;
    while (i < PAGE_SIZE) {
        // Escribir los datos en el archivo binario
        archivo.write(reinterpret_cast<const char *>(&a[i]), sizeof(int));
        i++;
    }
    archivo.close(); // Cierra el archivo
}


