#include "nodoFrase.h"

nodoFrase *crearNodoFrase(char* palabra){
    nodoFrase* nuevo = (nodoFrase*)malloc(sizeof(nodoFrase));
    strcpy(nuevo->palabra, palabra);
    nuevo->idDOC = -1;
    nuevo->pos = -1;
    nuevo->sig = NULL;

    return nuevo;
}

///INSERCION AL FINAL DE LA LISTA
void insertarNodoFrase(nodoFrase** lista, char* palabra){

    if(*lista){
        insertarNodoFrase(&((*lista)->sig), palabra);
    } else {
       *lista = crearNodoFrase(palabra);
    }
}

void mostrarNodoFrase(nodoFrase* nodo){
    printf("\n");
    printf("[ palabra: %s\n", nodo->palabra);
    printf("[ idDOC: %i\n", nodo->idDOC);
    printf("[ pos: %i\n", nodo->pos);

}

void mostrarListaFrase(nodoFrase* lista){
    if(lista){
        mostrarNodoFrase(lista);
        mostrarListaFrase(lista->sig);
    }
}

void mostrarFraseEncontrada(nodoFrase* lista){
    printf("Frase encontrada en el idDOC: %i\n", lista->idDOC);
    while(lista){
        printf("Palabra: \'%s\' ---> ", lista->palabra);
        printf("Pos: %i \n", lista->pos);
        lista = lista->sig;
    }

}

/**
 *  Funcion que valida una palabra, y le agrega el '\0' al final.
 *  Se considera válida una palabra que no contiene caracteres especiales. Si los contiene, la trunca hasta que aparece
 *  dicho caracter.
 */
char* validarPalabra(char* palabra, int dim){
    char* palabraValida = (char*)malloc(sizeof(char)*dim);
    int j = 0;

    for (int i = 0; i < dim; i++){
        if(validaChar(palabra[i]) == 1){
            palabraValida[j] = palabra[i];
            j++;
        }
    }
    palabraValida[j] = '\0';

    return palabraValida;
}

/**
 *  Lee una palabra char por char, hasta que se ingrese un espacio o un enter y retorna su tamaño.
 *  El enter se contempla en caso de que dicha palabra sea la última ingresada por el usuario.
 */
int leerPalabra(char *palabra){
    int i = 0;

    do{
        fflush(stdin);
        palabra[i] = getche(); ///getche() para escribir un caracter al lado de otro como si ingresara un string
        i++;
    }while(i < LONG_WORD-1 && palabra[i-1] != ' ' && palabra[i-1] != '\r');

    return i; /// Retorna los válidos
}

/**
 *  Función que lee una frase, palabra a palabra, hasta que se ingrese un enter, la valida y almacena en una lista.
 */
void ingresarFrase(nodoFrase** lista){
    char palabraFrase[LONG_WORD];
    int exitFlag = 0, dim;

    //Leo palabra por palabra y voy agregando a la lista hasta que se presione un enter.
    do{
        dim = leerPalabra(palabraFrase);

        if (palabraFrase[dim-1] == '\r'){   //Si se agregó un enter se terminó la frase.
            exitFlag = 1;
        }

        //Inserto en la lista una frase validada en el parámetro.
        insertarNodoFrase(lista, validarPalabra(palabraFrase, dim));

    }while(exitFlag != 1);

    printf("\n");   //Imprimo un enter para que por consola se vea el salto de línea.
}

/**
 *  Retorna una lista de nodoT con las ocurrencias de una palabra pasada por parámetro hallada en el árbol.
 */
nodoT* buscarListaOcurrenciasPalabra(nodoA *arbol, char *palabra){
    nodoT* res = NULL;
    nodoA *nodoArbol = existeNodo(arbol, palabra);

    if (nodoArbol){     //Si lo encuentra.
        res = nodoArbol->ocurrencias;
    }

    return res;
}
///Inciso 3 funcion auxiliar
int _buscaPalabrasMismoDoc(int idDOC, nodoFrase* listaP, nodoA* arbol){
    int encontrado = 0;
    int exitFlag = 0;

    //Recorro la lista con la frase a encontrar.
    while (listaP && exitFlag == 0){

        // Seteo encontrado en 0 aca, para cada nueva busqueda
        encontrado = 0;
        //Busco la lista de ocurrencias de la palabra actual en el arbol.
        nodoT* nodoPalabra = buscarListaOcurrenciasPalabra(arbol, listaP->palabra);

        //Comparo si de esa lista, alguna de las ocurrencias matchean con el id y la posición contigua.
        while(nodoPalabra && nodoPalabra->idDOC < idDOC){ // Si el idDOC de la lista se mantiene menor al del parametro
                                                          // avanzo en la lista de ocurrencias
                nodoPalabra = nodoPalabra->sig;
        }

        if(nodoPalabra && idDOC == nodoPalabra->idDOC){ // Significa que hubo match
                //Guardo en la lista los datos del match.
                listaP->idDOC = nodoPalabra->idDOC;
                listaP->pos = nodoPalabra->pos;

                encontrado = 1;
        }

        //De no encontrar un match, corto el while con el exitFlag.
        if (encontrado == 0){
            exitFlag = 1;
        } else {
            //Si no, avanzo en la lista hacia la siguiente palabra de la frase.
            listaP = listaP->sig;

        }
    }

    return encontrado;
}
/**
 *  Función auxiliar que se utiliza en la función buscarFrase() para hallar desde la segunda palabra en adelante
 *  si la frase existe en el diccionario. Recibe el idDOC y pos de la primer palabra, la lista que contiene
 *  la frase (sin la primer palabra) y el arbol para buscar.
 */
int _buscarFrase(int idDOC, int pos, nodoFrase* listaF, nodoA* arbol){
    int encontrado = 0;
    int exitFlag = 0;

    //Recorro la lista con la frase a encontrar.
    while (listaF && exitFlag == 0){

        // Seteo encontrado en 0 aca, para cada nueva busqueda
        encontrado = 0;
        //Busco la lista de ocurrencias de la palabra actual en el arbol.
        nodoT* nodoPalabra = buscarListaOcurrenciasPalabra(arbol, listaF->palabra);

        //Comparo si de esa lista, alguna de las ocurrencias matchean con el id y la posición contigua.
        while(nodoPalabra && nodoPalabra->idDOC < idDOC){ // Si el idDOC de la lista se mantiene menor al del parametro
                                                          // avanzo en la lista de ocurrencias
                nodoPalabra = nodoPalabra->sig;
        }

        while(nodoPalabra && idDOC == nodoPalabra->idDOC && nodoPalabra->pos < pos){

                nodoPalabra = nodoPalabra->sig;
        }
        if(nodoPalabra && idDOC == nodoPalabra->idDOC && nodoPalabra->pos == pos + 1){ // Significa que hubo match
                //Guardo en la lista los datos del match.
                listaF->idDOC = nodoPalabra->idDOC;
                listaF->pos = nodoPalabra->pos;

                encontrado = 1;
        }

        //De no encontrar un match, corto el while con el exitFlag.
        if (encontrado == 0){
            exitFlag = 1;
        } else {
            //Si no, avanzo en la lista hacia la siguiente palabra de la frase.
            listaF = listaF->sig;

            //Aumento la posición para que la siguiente palabra buscada sea contigua a esta.
            pos++;
        }
    }

    return encontrado;
}
