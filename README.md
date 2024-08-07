# Extraclase1-DatosII
El extraclase de arreglos paginados se divide en dos partes:

## Generator

Este programa se basa en crear archivos binarios grandes, el cual va a recibir siguiente comando: $> generator –size <SIZE> -output <OUTPUT FILE PATH>
El programa recibe este comando y lo parsea, dependiendo del tamaño del archivo se hace una división para saber cuantos enteros se deben de escribir.
Además de que se cambia de directorio para la ubicación de este archivo. 

## Sorter

Este programa se basa en ordenar archivos binarios grandes. El programa al ejecutarse va a recibir un comando: $> sorter –input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -
alg <ALGORITMO>
El programa recibe el comando y lo parsea, luego copia el archivo al path del output y carga este archivo usando la logica de paginación de PagedArray.
Siguiendo ordena los datos de output.bin utilizando el algoritmo seleccionado por el usuario y por ultimo imprime el tiempo de ejecución, los page falts y los page hits durante la operación.

*Importante* A LA HORA DE ESCRIBIR LOS DIRECTORIOS USAR //
