#include <iostream>

using namespace std;
int main()
{
    string comando;

    cout << "Bienvenido al sorter de archivos binarios,\n";
    cout << "Para crear tu archivo usa: $> sorter –input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>";
    getline(cin, comando);

    return 0;
}
