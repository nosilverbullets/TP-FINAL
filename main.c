#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "Termino.h"
#include "nodoT.h"
#include "nodoA.h"

int main()
{


    setlocale(LC_ALL, "spanish");


    // Abre el archivo 1 y lo pasa al archivo diccionario

    int vali=strlen(generarStringTxt("prueba.bin")); //Hacer una funcion aparte para no llamar dos veces generarStringtxt (PENSAR)
    char *texto = (char*)malloc(sizeof(char)*vali);  ///Hacer con malloc
    strcpy(texto, generarStringTxt("prueba.bin"));
    printf("%d\n", vali);
    printf("%s", texto);

    int cant = contarCantidadPalabras(texto, vali);
    printf("%d\n", cant);
    Termino palabrasTexto1[cant];
    textoToArregloTermino(texto, vali, palabrasTexto1, cant, 1);
    guardarTextoEnArchivoDic("diccionario.bin", palabrasTexto1, cant);
    mostrarArregloTermino(palabrasTexto1, cant);
    ///Texto 1 y arreglo de terminos del texto 1
    ///------------------------------------------------------------- TEXTO1



    /*int vali2=strlen(generarStringTxt("prueba2.bin"));
    char texto2[vali2];
    strcpy(texto2, generarStringTxt("prueba2.bin"));
    printf("%s", texto2);


    int cant2 = contarCantidadPalabras(texto2, vali2);
    Termino palabrasTexto2[cant2];
    textoToArregloTermino(texto2, vali2, palabrasTexto2, cant2, 2);
    guardarTextoEnArchivoDic("diccionario.bin", palabrasTexto2, cant2);
    ///------------------------------------------------------------- TEXTO2*/


    /*nodoA *arbol = crearArbolDiccionario("diccionario.bin");

    char palabra[40];
    printf("\n Ingrese la palabra: ");
    fflush(stdin);
    gets(palabra);
    buscarPalabra(arbol, palabra);*/








    /* Prueba STRTOK
    char cadena[200];
    char *token;
    char sep;

    printf("\nIntroduce cadena de texto: ");
    gets(cadena);
    token = strtok(cadena, " ");
    while (token){
        printf("\n %s", token);
        token = strtok(NULL, " ");
    }
    */

    return 0;
}
