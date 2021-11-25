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
#include "menu.h"
#define DICCIONARIO "diccionario.bin"
#define NOMBRESTEXTOS "infoTexto.bin"

//typedef struct PalabraFrecuente {
//    char palabra[20];
//    int frecuencia;
//    int idDoc;
//} PalabraFrecuente;
//
//// Punto 5
//void palabraMayorFrecuencia(nodoA *a, int idDoc, PalabraFrecuente *res) {
//    res->idDoc = idDoc;
//    char *aux = (char*)malloc(sizeof(char)*20);
//    if (a != NULL) {
//        palabraMayorFrecuencia(a->izq, idDoc, res);
//        palabraMayorFrecuencia(a->der, idDoc, res);
//        strcpy(aux, a->palabra);
//        if (compararOcurrencias(a->ocurrencias, res)) {
//            strcpy(res->palabra, aux);
//        }
//    }
//    free(aux);
//}
//
///*
//    Retorna 1 si la palabra es mas frecuente que la del valor del parametro, además modifica la estructura.
//    Retorna 0 si la palabra es menos frecuente que la del valor del parametro. No se ve alterada la estructura.
//*/
//int compararOcurrencias(nodoT *ocurrencia, PalabraFrecuente *res) {
//    int contadorAuxiliar = 0;
//    while (ocurrencia != NULL) {
//        if (ocurrencia->idDOC == res->idDoc) {
//            contadorAuxiliar++;
//        }
//        ocurrencia = ocurrencia->sig;
//    }
//    if (res->frecuencia < contadorAuxiliar) {
//        res->frecuencia = contadorAuxiliar;
//        return 1;
//    }
//    return 0;
//}

int main()
{
    setlocale(LC_ALL, "spanish"); // Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); // Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252); // Cambiar STDOUT - Para máquinas Windows


    menuUsuario();

//    nodoA *arbol = NULL;
//    crearArbolDiccionario(&arbol,"diccionario.bin");
//    mostrarArbolInOrder(arbol);
//    int id = 0;
//    nodoA* mayorFrecuencia;
//    printf("Ingrese el IDDoc que quiera buscar.\n");
//    fflush(stdin);
//    scanf("%d", &id);
//    mayorFrecuencia = mayorFrecuenciaPalabra(arbol, id);
//    mostrarNodoA(mayorFrecuencia);

//    nodoA *arbol = NULL;

//    PalabraFrecuente p;
//    p.frecuencia = 0;
//
//    palabraMayorFrecuencia(arbol, 3, &p);
//
//    printf("%s\n", p.palabra);
//    printf("%i\n", p.frecuencia);
//    printf("%i\n", p.idDoc);



    return 0;
}

