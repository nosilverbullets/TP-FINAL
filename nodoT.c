#include <stdio.h>
#include <stdlib.h>
#include "nodoT.h"

/// Funciones lista de nodoT, idDoc y pos.

nodoT *crearNodoT(int idDoc, int pos){
    nodoT *nuevo = (nodoT*)malloc(sizeof(nodoT));
    nuevo->idDOC = idDoc;
    nuevo->pos = pos;
    nuevo->sig = NULL;
    return nuevo;
}

void insertarNodoT(nodoT** lista, nodoT* nuevo){
    if(*lista){
        if((*lista)->idDOC < nuevo->idDOC)
            insertarNodoT(&((*lista)->sig), nuevo);
        else if ((*lista)->pos < nuevo->pos)
            insertarNodoT(&((*lista)->sig), nuevo);
        else{
            nuevo->sig = *lista;
            *lista = nuevo;
        }
    }
    else
        *lista = nuevo;
}
///Aux de prints del nodoT
void mostrarNodoT(nodoT* dato){
    printf("\n");
    printf("\t    [Id Documento: %i", dato->idDOC);
    printf(" Posicion: %i]", dato->pos);
}
///Funci�n recursiva de muestra de una lista de nodoT
void mostrarListaNodoT(nodoT *lista){
    if(lista){
        mostrarNodoT(lista);
        mostrarListaNodoT(lista->sig);
    }
}
