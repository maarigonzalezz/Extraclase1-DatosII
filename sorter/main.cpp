#include <iostream>
#include "Parser.h"
using namespace std;
int main()
{
    string comando;
    //$> sorter -input "C://Users//gonza//OneDrive - Estudiantes ITCR//Extraclase1-DatosII" -output "C://Users//gonza//OneDrive - Estudiantes ITCR//Documentos" -alg BS
    //C:\Users\gonza\OneDrive - Estudiantes ITCR\Extraclase1-DatosII\binary.bin

    cout << "Bienvenido al sorter de archivos binarios,\n";
    cout << "Para crear tu archivo usa: $> sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO> \n";
    getline(cin, comando);

    Parser parser;
    parser.parseCommand(comando);

    return 0;
}
