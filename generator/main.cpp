#include <iostream>
#include "generator.h"


using namespace std;
int main()
{
    string comando;

    cout << "Bienvenido al generador de archivos binarios,\n";
    cout << "Para crear tu archivo usa: $> generator -size <SIZE> -output <OUTPUT FILE PATH> \n";
    getline(cin, comando);

    Generator generator;
    generator.auxiliar("SMALL","C://Users//gonza//OneDrive - Estudiantes ITCR" );
    return 0;
}
