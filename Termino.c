#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "Termino.h"

/// Funcion que pide el nombre del texto por consola.
void pedirNomTexto (char nomTexto[])
{
    printf("\tIngrese el nombre del texto\n");
    fflush(stdin);
    gets(nomTexto);
}

/// Funcion que abre el archivo de nombresTextos para su lectura, y as� determinar la cantidad de idDocs cargados.
int contarCantIdDoc (char archivo[])
{
    int idDoc = 0;
    infoTexto a;
    FILE* arch;
    arch = fopen(archivo, "rb");
    if (arch)
    {
        if (fread(&a, sizeof(infoTexto), 1, arch)>0)
        {
            fseek(arch, sizeof(infoTexto)*(-1), SEEK_END);
            fread(&a, sizeof(infoTexto), 1, arch);
            idDoc = a.idDOC;
        }
        if(fclose(arch) != 0)
            printf("\nError al cerrar el archivo!...\n");
    }
    else
        printf("\nError al abrir el archivo!...\n");
    return idDoc;
}

/// El nombre ingresado por consola se guarda junto con su idDoc en el archivo de nombresTextos.
void guardarNomTextArchivo (char nomTexto [], char archivo[])
{
    infoTexto a;
    FILE* arch = fopen(archivo, "ab");
    if (arch)
    {
        strcpy(a.nomTexto, nomTexto);
        a.idDOC = contarCantIdDoc(archivo); // Ac� se llama a esta funci�n para determinar cuantos idDoc hay en el archivo.
        a.idDOC +=1; // Y ac� se incrementa en +=1 el valor retornado por la funci�n anterior y as� cargarlo en el archivo.
        fwrite(&a, sizeof(infoTexto), 1, arch);
        if(fclose(arch) != 0)
            printf("\nError al cerrar el archivo!...\n");
    }
    else
        printf("\nError al abrir el archivo!...\n");
}

/// Funci�n que recorre el archivo de nombresTextos y as� mostrarlo por pantalla.
void recorrerArch (char archivo[])
{
    int flag = 0;
    infoTexto a;
    FILE* arch = fopen(archivo, "rb");
    if (arch)
    {
        while (fread(&a, sizeof(infoTexto), 1, arch)>0)
        {
            flag = 1;
            printf("\n-Nombre del texto: %s\n", a.nomTexto);
            printf("\n--- Id doc: %d\n", a.idDOC);
        }
        if(fclose(arch) != 0)
            printf("\nError al cerrar el archivo!...\n");
    }
    else
        printf("\nError al abrir el archivo!...\n");
    if (flag == 0)
    {
        printf("El archivo no tiene textos cargados! \n");
    }
}

///Retorna la dimensi�n del archivo de texto cargado para ser utilizada como v�lidos.
int dimensionArchivo (char archivoTexto[])
{
    FILE* arch = fopen(archivoTexto, "rb");
    int tamanio = 0;
    if (arch)
    {
        fseek(arch, 0, SEEK_END);
        tamanio = (ftell(arch)/(sizeof(char)));
        if(fclose(arch) != 0)
            printf("\nError al cerrar el archivo!...\n");
    }
    else
        printf("\nError al abrir el archivo!...\n");
    return tamanio;
}

/// Abre el archivo bin de texto por parametro y retorna un string del tama�o total del texto.
char *generarStringTxt(char archivoTexto[], int tamanio){
    FILE *arch = fopen(archivoTexto, "rb");
    char *texto;
    if(arch){
        texto = (char*)malloc(sizeof(char)*tamanio);
        fseek(arch, 0, SEEK_SET);
        fread(texto, tamanio*sizeof(char), 1, arch);
        if(fclose(arch) != 0)
            printf("\nError al cerrar el archivo!...\n");
    }
    else
        printf("\nError al abrir el archivo!...\n");
    return texto;
}

/** Compara los caracteres devolviendo 1 si es una letra valida, o 0 si es un caracter especial, espacio, etc...
* Solo valido para ASCII en codificacion ANSI
*/
int validaChar(char letra){
    int rta = 0;

    /*if((letra>64 && letra<91) ||
       (letra>96 && letra<123) ||
       letra == -31 ||
       letra == -23 ||
       letra == -19 ||
       letra == -13 ||
       letra == -6  ||
       letra == -64 ||
       letra == -56 ||
       letra == -52 ||
       letra == -46 ||
       letra == -39)
        rta=1;*/
    if (isalpha(letra))
    {
     rta=1;
    }
    return rta;
}

/** Genera el contador de palabras recorriendo el string de todo el texto, generado previamente
* y descarta los espacios y caracteres especiales
*/
int contarCantidadPalabras(char texto[], int validos){ ///validos = validos del texto
    int cant = 0;
    int i = 0;
    while(i<validos){
        while(validaChar(texto[i])==0 && i<validos)
        {
            i++;
        }
        if (i<validos)
        {
            cant++;
            while(validaChar(texto[i])==1 && i<validos)
            {
                i++;
            }
        }

    }
    return cant;
}

/**
 Separa las palabras del string de todo el texto, cargando un arreglo del tipo "Termino" con cada palabra
 Recorro el arreglo de caracteres de todo el texto mientras que los caracteres sean invalidos,
 cuando encuentro un caracter valido, empiezo a copiar todo lo que sigue hasta encontrar un nuevo caracter invalido
 dentro del arreglo "palabra" que tiene como propiedad la estructura "Termino" de cada posicion del arreglo.
**/
void textoToArregloTermino(char texto[], int validos, Termino textoT[], int cantPalabras, int idDoc){
    int pos;
    int i = 0;

    for(pos = 0; pos < cantPalabras; pos++){

        while(validaChar(texto[i])== 0 && i<validos)
        {
            i++;
        }

        if(i < validos)
        {
            int j = 0;
            textoT[pos].idDOC = idDoc;
            textoT[pos].pos = pos+1;
            while(validaChar(texto[i])==1 && i<validos)
            {
                textoT[pos].palabra[j] = texto[i];
                textoT[pos].palabra[j] = tolower(textoT[pos].palabra[j]);
                i++;
                j++;
            }
            textoT[pos].palabra[j] = '\0';
        }
    }
}

void mostrarTermino(Termino palabra){
    printf("\n\tID Documento: %i", palabra.idDOC);
    printf("\n\tPalabra: %s", palabra.palabra);
    printf("\n\tPosicion: %i\n", palabra.pos);
}
/// Funci�n auxiliar solo utilizada para ver como se estaban cargando los t�rminos.
void mostrarArregloTermino(Termino arreglo[], int validos){
    for(int i=0; i<validos; i++)
        mostrarTermino(arreglo[i]);
}

/// Funci�n auxiliar solo utilizada para saber el codigo Ascii de los car�cteres especiales le�dos por el sistema.
void mostrarLetraAsciiString(char texto[], int validos){
    int i=0;
    while(i<validos){
        printf("\n Letra [%i]: %c, Ascii: %i", i, texto[i], texto[i]);
        i++;
    }
}
/// Guarda el arreglo de terminos en el archivo dicccionario.
void guardarTextoEnArchivoDic(char archivo[], Termino palabras[], int validos){
    FILE *arch = fopen(archivo, "ab");

    if(arch){
        int i=0;

        while(i<validos){
            fwrite(&palabras[i], sizeof(Termino), 1, arch);
            i++;
        }

        if(fclose(arch) != 0)
            printf("\nError al cerrar el archivo!...\n");
    }
    else
        printf("\nError al abrir el archivo!...\n");
}

/// Funcion auxiliar utilizada para ver como se iba cargando el diccionario (Utilizada tambien en el 11 como solo DESARROLLADOR).
void mostrarDiccionario (char archivo[])
{
    Termino a;
    FILE* arch = fopen(archivo, "rb");
    if (arch)
    {
        while (fread(&a, sizeof(Termino),1, arch)>0)
        {
            mostrarTermino(a);
        }

        if(fclose(arch) != 0)
            printf("\nError al cerrar el archivo!...\n");
    }
    else
        printf("\nError al abrir el archivo!...\n");
}
