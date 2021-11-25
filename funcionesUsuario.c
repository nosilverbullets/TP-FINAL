
#include "funcionesUsuario.h"

/// INCISO 1) Buscar el termino en alguno de los docs. (muestra tanto si esta en uno solo � en todos).
void buscarPalabra(nodoA *arbol, char palabra[])
{
    nodoA *palabraNodo = existeNodo(arbol, palabra);
    if(palabraNodo)
        mostrarNodoA(palabraNodo);
    else
        printf("\n La palabra no se encuentra en el diccionario!\n");
}
/// INCISO 2) Buscar todas las apariciones de un t�rmino en un documento y otro  (operacion and).
void verificarIdIngresado (int* idBusqueda1, int* idBusqueda2)
{
    int flag = 0;
    do
    {
        flag = 0;
        printf("Primer idDoc\n");
        scanf("%d", idBusqueda1);
        if (*idBusqueda1 <=0 && *idBusqueda1 > contarCantIdDoc(NOMBRESTEXTOS))
        {
            printf("ID NO VALIDO!\n");
            printf("Vuelva a ingresarlo.\n");
            flag = 1;
        }
    } while (flag!=0);

    do
    {
        flag = 0;
        printf("Segundo idDoc\n");
        scanf("%d", idBusqueda2);
        if (*idBusqueda2 < 1 && *idBusqueda2 > contarCantIdDoc(NOMBRESTEXTOS))
        {
            printf("ID NO VALIDO!\n");
            printf("Vuelva a ingresarlo.\n");
            flag = 1;
        }
    } while (flag!=0);

}
void buscarPalabraPorAnd (nodoA* arbol, char palabra[], int idDoc1, int idDoc2)
{
    nodoA* palabraNodo = existeNodo(arbol, palabra);
    if (palabraNodo)
    {
        nodoT* ocurrencias = palabraNodo->ocurrencias;

        int encontradoId1 = buscarIdOcurrencias(ocurrencias, idDoc1);
        printf("AAA %d\n", encontradoId1);
        int encontradoId2 = buscarIdOcurrencias(ocurrencias, idDoc2);
        printf("BBB %d\n", encontradoId2);
        if (encontradoId1 == 1 && encontradoId2 == 1)
        {
            mostrarNodoAAND(palabraNodo, idDoc1, idDoc2);
        }
        else
        {
            printf("\nLa palabra no se encuentra en los dos documentos!\n");
        }
    }
}
int buscarIdOcurrencias (nodoT* ocurrencias, int idDoc)
{
    int flag = 0;
    while (ocurrencias && ocurrencias->idDOC < idDoc)
    {
        ocurrencias = ocurrencias->sig;
    }
    if (ocurrencias && ocurrencias->idDOC == idDoc)
    {
        flag = 1;
    }
    return flag;
}
void mostrarNodoAAND(nodoA* arbol, int id1, int id2)
{
    printf("\n\n Palabra: %s", arbol->palabra);
    //printf("\n Frecuencia: %i", arbol->frecuencia);  //VER COMO MOSTRAR SOLO LA FRECUENCIA ENTRE LOS DOS DOCUMENTOS
    printf("\n Ocurrencias: ");
    mostrarListaNodoTAND(arbol->ocurrencias, id1, id2);
}

void mostrarListaNodoTAND(nodoT *lista, int id1, int id2)
{
    if(lista)
    {
        if (lista->idDOC == id1 || lista->idDOC == id2)
        {
            mostrarNodoT(lista);
        }
        mostrarListaNodoTAND(lista->sig, id1, id2);
    }
}
/// INCISO 3 : Buscar la aparici�n de m�s de un t�rmino en el mismo documento.



int buscaPalabrasMismoDoc(nodoA* arbol, nodoFrase* listaP)
{

    int encontrado = 0;

    if (listaP && arbol)  //Si la lista con la frase o el �rbol est�n vac�os, salgo.
    {
        //Busco la primer palabra en el arbol y retorna la lista de ocurrencias de dicha palabra o un NULL.
        nodoT* listaPalabra = buscarListaOcurrenciasPalabra(arbol, listaP->palabra);

        if (listaPalabra)  //Si encuentro la primer palabra.
        {

            if (listaP->sig == NULL)     //La frase era una sola palabra y la encontr�.
            {
                encontrado = 1;
            }
            else
            {
                nodoFrase* primero = listaP; // guardo el primer nodo de la frase antes de avanzar para setear los valores luego

                //Busco con cada ocurrencia de la primer palabra, si hay match con el resto de las palabras y sus ocurrencias.
                while(listaPalabra && encontrado == 0)
                {
                    encontrado = _buscaPalabrasMismoDoc(listaPalabra->idDOC, listaP->sig, arbol);

                    if (encontrado == 1)    //Si encuentra un match, setteo los valores de la primer palabra.
                    {
                        primero->idDOC = listaPalabra->idDOC;
                        primero->pos = listaPalabra->pos;
                    }
                    //Si no hubo match, voy a pasar a buscar un match con la siguiente ocurrencia de la primer palabra.
                    listaPalabra = listaPalabra->sig;
                }
            }
        }
    }

    return encontrado;
}
/**
 *  INCISO 4: Busca una frase en un �rbol, pas�ndole una lista con dicha frase. Retorna si encontr� o no la frase. La lista
 *  queda setteado con los valores donde fueron hallados.
 */
int buscarFrase(nodoA* arbol, nodoFrase* listaF)
{

    int encontrado = 0;

    if (listaF && arbol)  //Si la lista con la frase o el �rbol est�n vac�os, salgo.
    {
        //Busco la primer palabra en el arbol y retorna la lista de ocurrencias de dicha palabra o un NULL.
        nodoT* listaPalabra = buscarListaOcurrenciasPalabra(arbol, listaF->palabra);

        if (listaPalabra)  //Si encuentro la primer palabra.
        {

            if (listaF->sig == NULL)     //La frase era una sola palabra y la encontr�.
            {
                encontrado = 1;
            }
            else
            {
                nodoFrase* primero = listaF; // guardo el primer nodo de la frase antes de avanzar para setear los valores luego

                //Busco con cada ocurrencia de la primer palabra, si hay match con el resto de las palabras y sus ocurrencias.
                while(listaPalabra && encontrado == 0)
                {
                    encontrado = _buscarFrase(listaPalabra->idDOC, listaPalabra->pos, listaF->sig, arbol);

                    if (encontrado == 1)    //Si encuentra un match, setteo los valores de la primer palabra.
                    {
                        primero->idDOC = listaPalabra->idDOC;
                        primero->pos = listaPalabra->pos;
                    }
                    //Si no hubo match, voy a pasar a buscar un match con la siguiente ocurrencia de la primer palabra.
                    listaPalabra = listaPalabra->sig;
                }
            }
        }
    }

    return encontrado;
}

///Inciso 5: Buscar la palabra de más frecuencia que aparece en alguno de los docs.

void mayorFrecuenciaDoc(nodoA* arbol, int idDoc, int* frecuencia, nodoA* mayorFrec)
{
    int mayor;
    //nodoA* nodoFrecuente;
    if(arbol)
    {

        mayorFrecuenciaDoc(arbol->izq, idDoc, frecuencia, mayorFrec);
        mayorFrecuenciaDoc(arbol->der, idDoc, frecuencia, mayorFrec);

        mayor = cuentaFrecuenciaOcurrencias(arbol->ocurrencias, idDoc);
        if(mayor > *frecuencia){
            *frecuencia = mayor;
            mayorFrec = arbol;
        }
    }

    //return nodoFrecuente;
}

nodoA* mayorFrecuenciaPalabra(nodoA* arbol, int idDoc){
    nodoA* nodoFrecuente;

    int frecuencia;
    if(arbol){
        nodoFrecuente = arbol;
        frecuencia = cuentaFrecuenciaOcurrencias(arbol->ocurrencias, idDoc);

        mayorFrecuenciaDoc(arbol->izq, idDoc, &frecuencia, nodoFrecuente);
        mayorFrecuenciaDoc(arbol->der, idDoc, &frecuencia, nodoFrecuente);
        //printf("%s", nodoFrecuente->palabra);
    }else{
        nodoFrecuente = NULL;
    }

    return nodoFrecuente;
}

//int cuentaFrecuenciaOcurrencias (nodoT* ocurrencias, int idDoc)
//{
//    int contador = 0;
//    while (ocurrencias && ocurrencias->idDOC < idDoc)
//    {
//        ocurrencias = ocurrencias->sig;
//    }
//
//    while (ocurrencias && ocurrencias->idDOC == idDoc)
//    {
//        contador ++;
//        ocurrencias = ocurrencias->sig;
//    }
//    ocurrencias = ocurrencias->sig;
//    return contador;
//}


int cuentaFrecuenciaOcurrencias (nodoT* ocurrencias, int idDoc)
{
    int contador = 0;

    while (ocurrencias){
        if(ocurrencias->idDOC == idDoc)
        {
            contador ++;
        }
        ocurrencias = ocurrencias->sig;
    }
    return contador;
}

///Inciso 6: Utilizar la distancia de levenshtein en el ingreso de una palabra y sugerir similares a partir de una distancia <= 3.
int Minimo (int a, int b, int c)
{
    if(a <= b && a <= c)
    {
        return a;
    }
    else if(b <= a && b <= c)
    {
        return b;
    }
    else if(c <= a && c <= b)
    {
        return c;
    }
}
int Levenshtein(char *s1,char *s2)
{
    int t1,t2,i,j,*m,costo,res,ancho;

// Calcula tamanios strings
    t1=strlen(s1);
    t2=strlen(s2);

// Verifica que exista algo que comparar
    if (t1==0)
        return(t2);
    if (t2==0)
        return(t1);
    ancho=t1+1;

// Reserva matriz con malloc                     m[i,j] = m[j*ancho+i] !!
    m=(int*)malloc(sizeof(int)*(t1+1)*(t2+1));
    if (m==NULL)
        return(-1); // ERROR!!

// Rellena primera fila y primera columna
    for (i=0; i<=t1; i++)
        m[i]=i;
    for (j=0; j<=t2; j++)
        m[j*ancho]=j;

// Recorremos resto de la matriz llenando pesos
    for (i=1; i<=t1; i++)
        for (j=1; j<=t2; j++)
        {
            if (s1[i-1]==s2[j-1])
                costo=0;
            else
                costo=1;
            m[j*ancho+i]=Minimo(m[j*ancho+i-1]+1, m[(j-1)*ancho+i]+1, m[(j-1)*ancho+i-1]+costo);
        }      // Sustitucion

// Devolvemos esquina final de la matriz
    res=m[t2*ancho+t1];
    free(m);
    return(res);
}

void sugierePalabrasSimilares (nodoA* arbol, char* palabra)
{
    if (arbol)
    {
        sugierePalabrasSimilares(arbol->izq, palabra);
        if (Levenshtein(arbol->palabra, palabra)<=3)
        {
            printf("%s-", arbol->palabra);
        }
        sugierePalabrasSimilares(arbol->der, palabra);
    }
}
