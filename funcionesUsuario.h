#ifndef FUNCIONESUSUARIO_H_INCLUDED
#define FUNCIONESUSUARIO_H_INCLUDED
#include "nodoA.h"
#include "nodoFrase.h"
#define DICCIONARIO "diccionario.bin"
#define NOMBRESTEXTOS "infoTexto.bin"

void buscarPalabra(nodoA *arbol, char palabra[]);
void verificarIdIngresado (int* idBusqueda1, int* idBusqueda2);
void buscarPalabraPorAnd (nodoA* arbol, char palabra[], int idDoc1, int idDoc2);
int buscarIdOcurrencias (nodoT* ocurrencias, int idDoc);
void mostrarNodoAAND(nodoA* arbol, int id1, int id2);
void mostrarListaNodoTAND(nodoT *lista, int id1, int id2);
int buscaPalabrasMismoDoc(nodoA* arbol, nodoFrase* listaP);
int buscarFrase(nodoA* arbol, nodoFrase* lista);
void mayorFrecuenciaDoc(nodoA* arbol, int idDoc, int* frecuencia, nodoA* mayorFrec);
int cuentaFrecuenciaOcurrencias (nodoT* ocurrencias, int idDoc);
int Minimo (int a, int b, int c);
int Levenshtein(char *s1,char *s2);
void sugierePalabrasSimilares (nodoA* arbol, char* palabra);

#endif // FUNCIONESUSUARIO_H_INCLUDED
