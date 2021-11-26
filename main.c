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
#include "nodoFrase.h"
#include "funcionesUsuario.h"
#include "menu.h"
#define DICCIONARIO "diccionario.bin"
#define NOMBRESTEXTOS "infoTexto.bin"

int main()
{
    setlocale(LC_ALL, "spanish"); // Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); // Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252); // Cambiar STDOUT - Para máquinas Windows

    menuUsuario();

    return 0;
}

