//
// Created by gonza on 30/07/2024.
//

#include "PagedArray.h"

PagedArray::PagedArray(const std::string& inputFilePath, const std::string& outputFilePath)
    : pageFaults(0), pageHits(0) {
    // Verificar si el archivo de entrada existe
    std::ifstream src(inputFilePath, std::ios::binary);
    if (!src.is_open()) {
        throw std::runtime_error("Error al abrir el archivo de entrada: " + inputFilePath);
    }

    // Crear el archivo de salida
    const char* path = outputFilePath.c_str();

    if (_chdir(path) == 0) {
        std::cout << "Directorio cambiado exitosamente a: " << path << std::endl;
    } else {
        std::cerr << "Error al cambiar de directorio: " << strerror(errno) << std::endl;
    }
    std::ofstream dst("sorted.bin", std::ios::binary);
    if (!dst.is_open()) {
        throw std::runtime_error("Error al crear el archivo de salida: " + outputFilePath);
    }

    // Copiar el contenido del archivo de entrada al archivo de salida
    dst << src.rdbuf();
    src.close();
    dst.close();

    // Abrir el archivo de salida para lectura/escritura
    filePath = (outputFilePath + "//sorted.bin");
    cout << filePath;
    const char* path_def = filePath.c_str();
    file.open(path_def, std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Error al abrir el archivo de salida: " + filePath);
    }

    cout << "llego aqui";
    // Inicializar las páginas
    for (int i = 0; i < NUM_PAGES; ++i) {
        pages[i] = new int[PAGE_SIZE];
        pageIndices[i] = -1;
        pageLoaded[i] = false;
        cout << "alo";
    }
}

PagedArray::~PagedArray() {
    // Guardar todas las páginas cargadas antes de cerrar el archivo
    for (int i = 0; i < NUM_PAGES; ++i) {
        if (pageLoaded[i]) {
            savePage(i);
        }
        delete[] pages[i];
    }
    file.close();
}

int& PagedArray::operator[](int index) {
    int pageIndex = getPageIndex(index);
    int offset = getOffset(index);

    // Verificar si la página ya está cargada
    for (int i = 0; i < NUM_PAGES; ++i) {
        if (pageLoaded[i] && pageIndices[i] == pageIndex) {
            ++pageHits;
            cout << "pasa algo?";
            return pages[i][offset];
        }
    }

    // Si la página no está cargada, cargarla
    ++pageFaults;
    loadPage(pageIndex);

    // Buscar la página cargada y retornar el valor
    for (int i = 0; i < NUM_PAGES; ++i) {
        if (pageLoaded[i] && pageIndices[i] == pageIndex) {
            return pages[i][offset];
        }
    }

    // Esto no debería ocurrir
    throw std::runtime_error("Error al acceder a la página.");
}

void PagedArray::loadPage(int pageIndex) {
    // Encontrar una página libre o elegir una al azar para reemplazar
    int pageSlot = -1;
    for (int i = 0; i < NUM_PAGES; ++i) {
        if (!pageLoaded[i]) {
            pageSlot = i;
            break;
        }
    }

    if (pageSlot == -1) {
        pageSlot = std::rand() % NUM_PAGES;
        savePage(pageSlot);
    }

    // Cargar la página desde el archivo
    file.seekg(pageIndex * PAGE_SIZE * sizeof(int), std::ios::beg);
    file.read(reinterpret_cast<char*>(pages[pageSlot]), PAGE_SIZE * sizeof(int));
    pageIndices[pageSlot] = pageIndex;
    pageLoaded[pageSlot] = true;
}

void PagedArray::savePage(int pageSlot) {
    if (pageLoaded[pageSlot]) {
        file.seekp(pageIndices[pageSlot] * PAGE_SIZE * sizeof(int), std::ios::beg);
        file.write(reinterpret_cast<char*>(pages[pageSlot]), PAGE_SIZE * sizeof(int));
    }
}

int PagedArray::getPageFaults() const {
    return pageFaults;
}

int PagedArray::getPageHits() const {
    return pageHits;
}

int PagedArray::getFileSize() const {
    std::ifstream inFile(filePath, std::ios::binary | std::ios::ate);
    int fileSize = inFile.tellg();
    return fileSize / sizeof(int); // Devolver el número de enteros en el archivo
}

int PagedArray::getPageIndex(int index) const {
    return index / PAGE_SIZE;
}

int PagedArray::getOffset(int index) const {
    return index % PAGE_SIZE;
}
