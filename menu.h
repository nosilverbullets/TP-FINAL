#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "Termino.h"
#include "nodoT.h"
#include "nodoA.h"
#include "windows.h"
#include <conio.h>
#define LONG_WORD 20        //Longitud máxima de palabra
#include "nodoFrase.h"
#include "funcionesUsuario.h"
#define DICCIONARIO "diccionario.bin"
#define NOMBRESTEXTOS "infoTexto.bin"

void cargaTextoDiccionario ();
void menuTextoDiccionario ();
void menuUsuario ();
#endif // MENU_H_INCLUDED