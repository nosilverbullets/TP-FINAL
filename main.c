#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "Termino.h"
#include "nodoT.h"
#include "nodoA.h"
#include "windows.h"
#include <conio.h>
#define LONG_WORD 20        //Longitud máxima de palabra
#include "nodoFrase.h"
#include "funcionesUsuario.h"


int main()
{
    setlocale(LC_ALL, "spanish"); // Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); // Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252); // Cambiar STDOUT - Para máquinas Windows




// Abre el archivo 1 y lo pasa al archivo diccionario
//
    char nomTexto [100];
    pedirNomTexto(nomTexto);
    guardarNomTextArchivo(nomTexto, "archNomText.bin");
    strcat(nomTexto, ".bin");
    int vali=dimensionArchivo(nomTexto);
    char *texto = (char*)malloc(sizeof(char)*vali);
    strcpy(texto, generarStringTxt(nomTexto, vali));
    printf("%s", texto);

    int cant = contarCantidadPalabras(texto, vali);
    Termino* palabrasTexto1 = (Termino*)malloc(sizeof(Termino)*cant);
    int idDoc = contarCantIdDoc("archNomText.bin");
    textoToArregloTermino(texto, vali, palabrasTexto1, cant, idDoc);
    guardarTextoEnArchivoDic("diccionario.bin", palabrasTexto1, cant);
    mostrarArregloTermino(palabrasTexto1, cant);

    ///Texto 1 y arreglo de terminos del texto 1
    ///------------------------------------------------------------- TEXTO1

    /*
    //    int vali=dimensionArchivo("prueba.bin"); //Hacer una funcion aparte para no llamar dos veces generarStringtxt (PENSAR)
    //    char *texto = (char*)malloc(sizeof(char)*vali);
    //    strcpy(texto, generarStringTxt("prueba.bin", vali));
    //    printf("%d\n", vali);
    //    printf("%s\n", texto);
    //    int cant = contarCantidadPalabras(texto, vali);
    //    printf("%d\n", cant);
    //    Termino* palabrasTexto1 = (Termino*)malloc(sizeof(Termino)*cant);
    //
    //    textoToArregloTermino(texto, vali, palabrasTexto1, cant, 2);
    //    guardarTextoEnArchivoDic("diccionario.bin", palabrasTexto1, cant);
    //    mostrarArregloTermino(palabrasTexto1, cant);
    //    */
//    ///------------------------------------------------------------- TEXTO2*/

//    nodoA *arbol = NULL;
//    crearArbolDiccionario(&arbol,"diccionario.bin");
//    mostrarArbolInOrder(arbol);
//    char palabra[20];
//    printf("\n Ingrese la palabra: ");
//    fflush(stdin);
//    gets(palabra);
//    buscarPalabra(arbol, palabra);

    nodoFrase* lista = NULL;
    nodoA* arbol = NULL;
    crearArbolDiccionario(&arbol,"diccionario.bin");
    mostrarArbolInOrder(arbol);
    recorrerArch("archNomText.bin");
    printf("Ingrese la frase a buscar:\n");
    ingresarFrase(&lista);

    int fraseEncontrada = buscarFrase(arbol, lista);
    if (fraseEncontrada)
    {
        mostrarFraseEncontrada(lista);
    }

    return 0;
}

