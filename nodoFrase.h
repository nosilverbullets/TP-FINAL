#ifndef NODOFRASE_H_INCLUDED
#define NODOFRASE_H_INCLUDED
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "Termino.h"
#include "nodoT.h"
#include "nodoA.h"
#include "windows.h"
#include <conio.h>
#define LONG_WORD 20

///COMENTAR PARA QUÉ SIRVE ESTA ESTRUCTURA
typedef struct nodoFrase
{
    char palabra[20];
    int idDOC;
    int pos;
    struct nodoFrase* sig;
}nodoFrase;

nodoFrase *crearNodoFrase(char* palabra);
void insertarNodoFrase(nodoFrase** lista, char* palabra);
void mostrarNodoFrase(nodoFrase* nodo);
void mostrarListaFrase(nodoFrase *lista);
void mostrarFraseEncontrada(nodoFrase* lista);
char* validarPalabra(char* palabra, int dim);
int leerPalabra(char *palabra);
void ingresarFrase(nodoFrase** lista);
nodoT* buscarListaOcurrenciasPalabra(nodoA *arbol, char *palabra);
int _buscarFrase(int idDOC, int pos, nodoFrase* lista, nodoA* arbol);
#endif // NODOFRASE_H_INCLUDED
