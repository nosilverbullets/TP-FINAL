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
    printf("\t[Palabra: %s\n", nodo->palabra);
    printf("\t[IdDOC: %i\n", nodo->idDOC);
    printf("\t[Pos: %i\n", nodo->pos);

}

void mostrarListaFrase(nodoFrase* lista){
    if(lista){
        mostrarNodoFrase(lista);
        mostrarListaFrase(lista->sig);
    }
}

void mostrarFraseEncontrada(nodoFrase* lista){
    printf("Frase o palabras encontradas en el idDOC: %i\n", lista->idDOC);
    while(lista){
        printf("\tPalabra: \'%s\' ---> ", lista->palabra);
        printf("\tPos: %i \n", lista->pos);
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

///Función que lee una frase, palabra a palabra, hasta que se ingrese un enter, la valida y almacena en una lista.
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

///Retorna una lista de nodoT con las ocurrencias de una palabra pasada por parámetro hallada en el árbol.
nodoT* buscarListaOcurrenciasPalabra(nodoA *arbol, char *palabra){
    nodoT* res = NULL;
    nodoA *nodoArbol = existeNodo(arbol, palabra);

    if (nodoArbol){     //Si lo encuentra.
        res = nodoArbol->ocurrencias;
    }

    return res;
}
///Funcion para liberar una frase luego de ser utilizada
void liberarFrase(nodoFrase** lista){
    nodoFrase* aux;

    while(*lista){
        aux = *lista;
        *lista = (*lista)->sig;
        free(aux);
    }
}
