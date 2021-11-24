#ifndef FUNCIONESUSUARIO_H_INCLUDED
#define FUNCIONESUSUARIO_H_INCLUDED
#include "nodoA.h"
#include "nodoFrase.h"

void buscarPalabra(nodoA *arbol, char palabra[]);
int buscarFrase(nodoA* arbol, nodoFrase* lista);

#endif // FUNCIONESUSUARIO_H_INCLUDED
