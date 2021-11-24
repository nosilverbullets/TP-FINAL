
#include "funcionesUsuario.h"

/// INCISO 1) Buscar el termino en alguno de los docs. (muestra tanto si esta en uno solo ó en todos).
void buscarPalabra(nodoA *arbol, char palabra[]){
    nodoA *palabraNodo = existeNodo(arbol, palabra);
    if(palabraNodo)
        mostrarNodoA(palabraNodo);
    else
        printf("\n La palabra no se encuentra en el diccionario!\n");
}
/// INCISO 2) Buscar todas las apariciones de un término en un documento y otro  (operacion and).
void buscarPalabraPorAnd (nodoA* arbol, char palabra[], int idDoc1, int idDoc2)
{
    nodoA* palabraNodo = existeNodo(arbol, palabra);
    if (palabraNodo)
    {
        nodoT* ocurrencias = palabraNodo->ocurrencias;
        while (ocurrencias)
        {
            if (ocurrencias.idDOC ==)

        }
    }
}
int buscarIdOcurrencias (nodoT* ocurrencias, int idDoc)
{
    while (ocurrencias && ocurrencias.idDOC <= idDoc)
    {
        ocurrencias = ocurrencias->sig;
        if (ocurrencias.idDOC == idDoc)
        {

        }
    }
}
/**
 *  Busca una frase en un árbol, pasándole una lista con dicha frase. Retorna si encontró o no la frase. La lista
 *  queda setteado con los valores donde fueron hallados.
 */
int buscarFrase(nodoA* arbol, nodoFrase* lista){
    if (!lista || !arbol){  //Si la lista con la frase o el árbol están vacíos, salgo.
       return 0;
    }
    int encontrado = 0, idPrimero, posPrimero;

    //Busco la primer palabra
    char *primerPalabra = lista->palabra;
    nodoT* listaPalabra = buscarListaOcurrenciasPalabra(arbol, primerPalabra);  //Busco la lista de ocurrencias de la primer palabra en el arbol.

    if (listaPalabra){ //Si encuentra la primer palabra.

        //Guardo en la lista los valores donde se encontró la primer palabra.
        lista->idDOC = listaPalabra->idDOC;
        lista->pos = listaPalabra->pos;

        if (lista->sig == NULL){    //La frase era una sola palabra y la encontró.
            encontrado = 1;
        } else {
            nodoFrase* primero = lista;
            lista = lista->sig; //Actualizo lista a la segunda palabra.

            //Busco con cada ocurrencia de la primer palabra, si hay match con el resto de las palabras y sus ocurrencias.
            while(listaPalabra && encontrado == 0){
                encontrado = _buscarFrase(listaPalabra->idDOC, listaPalabra->pos, lista, arbol);

                if (encontrado == 1){   //Si encuentra un match, setteo los valores de la primer palabra.
                    primero->idDOC = listaPalabra->idDOC;
                    primero->pos = listaPalabra->pos;
                }
                //Si no hubo match, voy a pasar a buscar un match con la siguiente ocurrencia de la primer palabra.
                listaPalabra = listaPalabra->sig;
            }
        }
    }

    return encontrado;
}
