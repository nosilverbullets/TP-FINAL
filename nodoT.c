#include <stdio.h>
#include <stdlib.h>
#include "nodoT.h"

/// Funciones lista de nodoT, idDoc y pos

nodoT *crearNodoT(int idDoc, int pos){
    nodoT *nuevo = (nodoT*)malloc(sizeof(nodoT));
    nuevo->idDOC = idDoc;
    nuevo->pos = pos;
    nuevo->sig = NULL;
    return nuevo;
}

nodoT *insertarNodoT(nodoT *lista, nodoT *nuevo){
    if(lista){
        if(lista->idDOC < nuevo->idDOC)
            lista->sig = insertarNodoT(lista->sig, nuevo);
        else if (lista->pos < nuevo->pos)
            lista->sig = insertarNodoT(lista->sig, nuevo);
        else{
            nuevo->sig = lista;
            lista = nuevo;
        }
    }
    else
        lista = nuevo;
    return lista;
}

void mostrarNodoT(nodoT dato){
    printf("  |Id Documento: %i", dato.idDOC);
    printf(" Posicion: %i|", dato.pos);
}

void mostrarListaNodoT(nodoT *lista){
    if(lista){
        mostrarNodoT(*lista);
        mostrarListaNodoT(lista->sig);
    }
}
