#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodoA.h"

nodoA *crearNodoA(char palabra[]){
    nodoA *nuevo = (nodoA*)malloc(sizeof(nodoA));
    strcpy(nuevo->palabra, palabra);
    nuevo->frecuencia = 1;
    nuevo->ocurrencias = NULL;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

void insertarNodoA(nodoA** arbol, Termino nuevo){
    if(*arbol){
        switch(strcmp((*arbol)->palabra, nuevo.palabra)){
        case 1:
            insertarNodoA(&((*arbol)->izq), nuevo);
            break;
        case -1:
            insertarNodoA(&((*arbol)->der), nuevo);
            break;
        case 0:
            (*arbol)->frecuencia++;
            insertarNodoT(&((*arbol)->ocurrencias), crearNodoT(nuevo.idDOC, nuevo.pos));
            break;
        }
    }
    else{
        *arbol = crearNodoA(nuevo.palabra);
        (*arbol)->ocurrencias = crearNodoT(nuevo.idDOC, nuevo.pos);
    }
}

void crearArbolDiccionario(nodoA** arbol, char diccionario[]){
    FILE *arch = fopen(diccionario, "rb");

    if(arch){
        Termino leido;

        while(fread(&leido, sizeof(Termino), 1, arch)>0)
        {
            insertarNodoA(arbol, leido);
        }

        if(fclose(arch) != 0)
            printf("\n Error al cerrar el archivo!...\n");
    }
    else
        printf("\n Error al abrir el archivo!...\n");
}

void mostrarNodoA(nodoA* arbol){
    printf("\n\n Palabra: %s", arbol->palabra);
    printf("\n Frecuencia: %i", arbol->frecuencia);
    printf("\n Ocurrencias: ");
    mostrarListaNodoT(arbol->ocurrencias);
}

void mostrarArbolInOrder(nodoA *arbol){
    if(arbol){
        mostrarArbolInOrder(arbol->izq);
        mostrarNodoA(arbol);
        mostrarArbolInOrder(arbol->der);
    }
}

nodoA *existeNodo(nodoA *arbol, char palabra[]){
    nodoA *aRetornar = NULL;
    if(arbol){
        switch(strcmp(arbol->palabra, palabra)){
        case 1:
            aRetornar = existeNodo(arbol->izq, palabra);
            break;
        case -1:
            aRetornar = existeNodo(arbol->der, palabra);
            break;
        case 0:
            aRetornar = arbol;
            break;
        }
    }
    return aRetornar;
}

void buscarPalabra(nodoA *arbol, char palabra[]){
    nodoA *palabraNodo = existeNodo(arbol, palabra);
    if(palabraNodo)
        mostrarNodoA(palabraNodo);
    else
        printf("\n La palabra no se encuentra en el diccionario!\n");
}

//void mostrarTextoUnico
