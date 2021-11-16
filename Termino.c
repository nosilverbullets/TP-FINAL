#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "Termino.h"

void errorCerrar(){printf("\n Error al cerrar el archivo!...\n");}
void errorAbrir(){printf("\n Error al abrir el archivo!...\n");}

// Abre el archivo bin de texto por parametro y lo retorna formando un string del tamaño total del texto.

char *generarStringTxt(char archivoTexto[]){
    FILE *arch = fopen(archivoTexto, "rb");
    char *texto;
    if(arch){
        fseek(arch, 0, SEEK_END);
        int tamanio = (ftell(arch))/(sizeof(char));
         printf("\n Tamanio %i\n", tamanio);
        texto = (char*)malloc(sizeof(char)*tamanio);
        fseek(arch, 0, SEEK_SET);

        fread(texto, tamanio*sizeof(char), 1, arch);

        if(fclose(arch) != 0)
            errorCerrar();
    }
    else
        errorAbrir();
    return texto;
}
// Compara los caracteres devolviendo 1 si es una letra valida, o 0 si es un caracter especial, espacio, etc...
// Solo valido para ASCII en codificacion ANSI

int validaChar(char letra){
    int rta = 0;

    if(
       (letra>64 && letra<91) ||
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
       letra == -39
    )
        rta=1;//if (isalpha(letra))          -> Reemplaza lo anterior
    return rta;
}

// Genera el contador de palabras recorriendo el string de todo el texto, generado previamente
// y descarta los espacios y caracteres especiales

int contarCantidadPalabras(char texto[], int validos){
    int cant = 0;
    int i = 0;
    // printf("\nContarPalabras Validos: %i", validos);
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
 Separa las palabras del string de todo el texto, formando un arreglo del tipo "Termino" con cada palabra
 Recorro el arreglo de caracteres de todo el texto formando palabras mientras que los caracteres sean invalidos,
 cuando encuentro un caracter valido, empiezo a copiar todo lo que sigue hasta encontrar un nuevo caracter invalido
 dentro del arreglo "palabra" que tiene como propiedad la estructura "Termino" de cada posicion del arreglo.
**/
void textoToArregloTermino(char texto[], int validosT, Termino textoT[], int validos, int idDoc){
    int pos=0;

    // printf("\n ValidosT: %i", validosT);
    // printf("\n Validos: %i", validos);

    for(int i=0; i<validosT; i++){
        if(pos<validos){ // validosT? Para que tome el salto de linea
            while(validaChar(texto[i])==0 && i<validosT)
                i++;

            int j=0;
            textoT[pos].idDOC = idDoc;
            textoT[pos].pos = pos+1;
            textoT[pos].palabra[j] = texto[i];
            i++;
            j++;
            while(validaChar(texto[i])==1 && i<validosT){
                textoT[pos].palabra[j] = texto[i];
                i++;
                j++;
            }
            textoT[pos].palabra[j] = '\0';
            pos++;
        }
    }
}

void mostrarTermino(Termino palabra){
    printf("\n ID Documento: %i", palabra.idDOC);
    printf("\n Palabra: %s", palabra.palabra);
    printf("\n Posicion: %i\n", palabra.pos);
}

void mostrarArregloTermino(Termino arreglo[], int validos){
    for(int i=0; i<validos; i++)
        mostrarTermino(arreglo[i]);
}

void mostrarLetraAsciiString(char texto[], int validos){
    int i=0;
    while(i<validos){
        printf("\n Letra [%i]: %c, Ascii: %i", i, texto[i], texto[i]);
        i++;
    }
}

void guardarTextoEnArchivoDic(char archivo[], Termino palabras[], int validos){
    FILE *arch = fopen(archivo, "ab");

    if(arch){
        int i=0;

        while(i<validos){
            fwrite(&palabras[i], sizeof(Termino), 1, arch);
            i++;
        }

        if(fclose(arch) != 0)
            errorCerrar();
    }
    else
        errorAbrir();
}
