#ifndef NODOA_H_INCLUDED
#define NODOA_H_INCLUDED
#include "nodoT.h"
#include "Termino.h"

typedef struct nodoA
{
   char palabra[20];
   int frecuencia; //representa la cantidad de nodos de la lista
   struct nodoA *der;
   struct nodoA *izq;
   nodoT *ocurrencias; //ordenada por idDOC, luego por pos
}nodoA;

nodoA *crearNodoA(char palabra[]);
nodoA *insertarNodoA(nodoA *arbol, Termino nuevo);
nodoA *crearArbolDiccionario(char diccionario[]);
void mostrarNodoA(nodoA arbol);
void mostrarNodoAPreOrder(nodoA *arbol);
nodoA *existeNodo(nodoA *arbol, char palabra[]);
void buscarPalabra(nodoA *arbol, char palabra[]);

#endif // NODOA_H_INCLUDED
