#ifndef NODOT_H_INCLUDED
#define NODOT_H_INCLUDED

typedef struct nodoT
{
    int idDOC;
    int pos;
    struct nodoT* sig;
}nodoT;

nodoT *crearNodoT(int idDoc, int pos);
void insertarNodoT(nodoT** lista, nodoT* nuevo);
void mostrarNodoT(nodoT* dato);
void mostrarListaNodoT(nodoT *lista);

#endif // NODOT_H_INCLUDED

///    hola como estas   ///


/*  1    2   3
hola todo bien
4        5
estamos bien
6     7   8  9
hola como te va
 10   11    12
hola como estas
1      7  xx
6      12  xx
10     14      12
hola   como    estas*/
