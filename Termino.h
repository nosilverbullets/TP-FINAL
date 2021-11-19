#ifndef TERMINO_H_INCLUDED
#define TERMINO_H_INCLUDED

typedef struct {
  char palabra[20];
  int idDOC;
  int pos; //incrementa palabra por palabra, y no letra por letra
}Termino;

int dimensionArchivo (char archivoTexto[]);
// Abre el archivo bin de texto por parametro y lo retorna formando un string del tamaño total del texto.

char *generarStringTxt(char archivoTexto[], int tamanio);

// Compara los caracteres devolviendo 1 si es una letra valida, o 0 si es un caracter especial, espacio, etc...

int validaChar(char letra);

// Genera el contador de palabras recorriendo el string de todo el texto, generado previamente
// y descarta los espacios y caracteres especiales

int contarCantidadPalabras(char texto[], int validos);

/**
 Separa las palabras del string de todo el texto, formando un arreglo del tipo "Termino" con cada palabra
 Recorro el arreglo de caracteres de todo el texto formando palabras mientras que los caracteres sean invalidos,
 cuando encuentro un caracter valido, empiezo a copiar todo lo que sigue hasta encontrar un nuevo caracter invalido
 dentro del arreglo "palabra" que tiene como propiedad la estructura "Termino" de cada posicion del arreglo.
**/
void textoToArregloTermino(char texto[], int validosT, Termino textoT[], int validos, int idDoc);
void mostrarTermino(Termino palabra);
void mostrarArregloTermino(Termino arreglo[], int validos);
void mostrarLetraAsciiString(char texto[], int validos);
void guardarTextoEnArchivoDic(char archivo[], Termino palabras[], int validos);

#endif // TERMINO_H_INCLUDED
