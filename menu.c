#include "menu.h"

void cargaTextoDiccionario ()
{
    char nomTexto [100];
    pedirNomTexto(nomTexto);
    guardarNomTextArchivo(nomTexto, NOMBRESTEXTOS);
    strcat(nomTexto, ".bin");
    int vali=dimensionArchivo(nomTexto);
    char *texto = (char*)malloc(sizeof(char)*vali);
    strcpy(texto, generarStringTxt(nomTexto, vali));
    printf("%s", texto);
    printf("\n");
    system("pause");
    system("cls");
    int cant = contarCantidadPalabras(texto, vali);
    Termino* palabrasTexto1 = (Termino*)malloc(sizeof(Termino)*cant);
    int idDoc = contarCantIdDoc(NOMBRESTEXTOS);
    textoToArregloTermino(texto, vali, palabrasTexto1, cant, idDoc);
    guardarTextoEnArchivoDic(DICCIONARIO, palabrasTexto1, cant);
}
void menuTextoDiccionario ()
{
    char control = 's';
    recorrerArch(NOMBRESTEXTOS);
    printf("Quiere cargar textos? (s-n)\n");
    fflush(stdin);
    scanf("%c", &control);
    while (control == 's')
    {
        cargaTextoDiccionario();
        system("cls");
        printf("Quiere cargar otro texto? \n");
        fflush(stdin);
        scanf("%c", &control);
    }
    system("cls");
    printf("Lista de textos cargados: \n");
    recorrerArch(NOMBRESTEXTOS);
}
void menuUsuario ()
{
    nodoA* arbol= NULL;
    nodoFrase* lista = NULL;
    crearArbolDiccionario(&arbol,DICCIONARIO);
    char palabra [20];
    int control = '0';
    int idBusqueda1 = 0;
    int idBusqueda2 = 0;
    int fraseEncontrada = 0;


    do
    {
        printf("\n*** Bienvenido al motor de busqueda de LAB 2 ***\n");
        printf("Ingrese el numero de la funcion que quiera utilizar.\n");
        printf("1.Buscar todas las apariciones de un termino en algun documento\n");
        printf("2.Buscar todas las apariciones de un termino en un documento y otro\n");
        printf("3.Buscar la aparicion de mas de un termino en el mismo documento.\n");
        printf("4.Buscar una frase completa\n");
        printf("5.Buscar la palabra de mas frecuencia que aparece en alguno de los docs.\n");
        printf("6.Ingresar una palabra y buscar similares.\n");
        printf("10.Cargar textos al sistema. (DESARROLLADOR)\n");
        printf("0.Salir del programa.\n");
        printf("\n************************************************\n");
        printf("Ingrese su opcion:\n");
        scanf("%d", &control);
        system("cls");
        switch (control)
        {
        case 1:
            printf("\n Ingrese la palabra: ");
            fflush(stdin);
            gets(palabra);
            buscarPalabra(arbol, palabra);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 2:
            printf("\n Ingrese la palabra: ");
            fflush(stdin);
            gets(palabra);
            printf("Textos disponibles: \n");
            recorrerArch(NOMBRESTEXTOS);
            printf("Vamos a comparar entre dos id's\n");
            printf("\nIngrese los id del los documentos que quiera buscar su palabra:\n");
            verificarIdIngresado(&idBusqueda1, &idBusqueda2);
            buscarPalabraPorAnd(arbol, palabra, idBusqueda1, idBusqueda2);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 3:
            printf("Ingrese las palabras a buscar:\n");
            ingresarFrase(&lista);
            fraseEncontrada = buscaPalabrasMismoDoc(arbol, lista);
            if (fraseEncontrada)
            {
                mostrarFraseEncontrada(lista);
            }
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 4:
            printf("Ingrese la frase a buscar:\n");
            ingresarFrase(&lista);
            fraseEncontrada = buscarFrase(arbol, lista);
            if (fraseEncontrada)
            {
                mostrarFraseEncontrada(lista);
            }
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 5:
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 6:
            printf("\n Ingrese la palabra: ");
            fflush(stdin);
            gets(palabra);
            printf("Palabras sugeridas a la palabra %s : \n", palabra);
            sugierePalabrasSimilares(arbol, palabra);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 10:
            menuTextoDiccionario();
            printf("\n");
            system("pause");
            system("cls");
            break;
        default:
            printf("\n***OPCION INCORRECTA***\n");
            printf("\n");
            system("pause");
            system("cls");
            break;
        }
    }
    while (control != 0);

}
