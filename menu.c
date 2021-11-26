#include "menu.h"

/**Esta funcion pide por consola el nombre del texto para así guardarse en el archivo de nombres de textos (Que contiene los nombres junto con sus idDoc)
*  Luego de cargar ese archivo, concatena un .bin a ese nombre así pasa a ser un archivo (Ya puesto en la carpeta del proyecto)
*  Con este archivo se genera un string de todo el texto, para luego cargarlo en el arreglo Termino, y así cargarlo en el diccionario.
*/
void cargaTextoDiccionario ()
{
    char nomTexto [100];
    pedirNomTexto(nomTexto);
    guardarNomTextArchivo(nomTexto, NOMBRESTEXTOS);
    strcat(nomTexto, ".bin");
    int vali=dimensionArchivo(nomTexto);
    char *texto = (char*)malloc(sizeof(char)*vali);
    strcpy(texto, generarStringTxt(nomTexto, vali));
    printf("Contenido de el texto: \n");
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

///Llama a la funcion de carga de los diferentes textos y su correspondiente carga en el diccionario hasta que por consola se diga que no.
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

///Menu de funcionalidad del programa completo, llama a todas las funciones de usuario (Más 3 funciones de desarrollador)
void menuUsuario ()
{
    nodoA* arbol = NULL;
    nodoA* mayorFREC = NULL;
    nodoFrase* lista = NULL;
    crearArbolDiccionario(&arbol,DICCIONARIO);
    char palabra [20];
    int control = '0';
    int flag = 0;
    int idBusqueda1 = 0;
    int idBusqueda2 = 0;
    int fraseEncontrada = 0;
    do
    {
        printf("\n*** Bienvenido al motor de busqueda de LAB 2 ***\n");
        printf("\nIngrese el numero de la funcion que quiera utilizar.\n");
        printf("1.Buscar todas las apariciones de un termino en algun documento\n");
        printf("2.Buscar todas las apariciones de un termino en un documento y otro\n");
        printf("3.Buscar la aparicion de mas de un termino en el mismo documento.\n");
        printf("4.Buscar una frase completa\n");
        printf("5.Buscar la palabra de mas frecuencia que aparece en alguno de los docs.\n");
        printf("6.Ingresar una palabra y buscar similares.\n");
        printf("\n10.Cargar textos al sistema. (DESARROLLADOR)\n");
        printf("11.Mostrar diccionario. (DESARROLLADOR)\n");
        printf("12.Mostrar arbol en PREORDER. (DESARROLLADOR)\n");
        printf("\n0.Salir del programa.\n");
        printf("\n************************************************\n");
        printf("Ingrese su opcion:\n");
        fflush(stdin);
        scanf("%d", &control);
        system("cls");
        switch (control)
        {
        case 1:
            printf("\nIngrese la palabra: ");
            fflush(stdin);
            gets(palabra);
            buscarPalabra(arbol, palabra);
            break;
        case 2:
            do
            {
                flag = 0;
                printf("\nIngrese la palabra: ");
                fflush(stdin);
                gets(palabra);
                flag = verificarPalabra(arbol, palabra);
            }while (flag!=0);
            printf("\nTextos disponibles: \n");
            recorrerArch(NOMBRESTEXTOS);
            printf("\nVamos a comparar entre dos id's\n");
            printf("\nIngrese los id del los documentos que quiera buscar su palabra:\n");
            do
            {
                flag = 0;
                printf("\nPrimer idDoc\n");
                scanf("%d", &idBusqueda1);
                flag = verificarIdIngresado(idBusqueda1);
            }
            while (flag != 0);
            do
            {
                flag = 0;
                printf("\nSegundo idDoc\n");
                scanf("%d", &idBusqueda2);
                flag = verificarIdIngresado(idBusqueda2);
            }
            while (flag != 0);
            buscarPalabraPorAnd(arbol, palabra, idBusqueda1, idBusqueda2);
            break;
        case 3:
            printf("Ingrese las palabras a buscar:\n");
            ingresarFrase(&lista);
            fraseEncontrada = buscaPalabrasMismoDoc(arbol, lista);
            if (fraseEncontrada)
            {
                mostrarFraseEncontrada(lista);
            }
            else
            {
                printf("Palabras no encontradas o mal escritas\n");
            }
            liberarFrase(&lista);
            break;
        case 4:
            printf("Ingrese la frase a buscar:\n");
            ingresarFrase(&lista);
            fraseEncontrada = buscarFrase(arbol, lista);
            if (fraseEncontrada)
            {
                mostrarFraseEncontrada(lista);
            }
            else
            {
                printf("Frase no encontrada o mal escrita\n");
            }
            liberarFrase(&lista);
            break;
        case 5:
            do
            {
                flag = 0;
                printf("Ingrese el idDoc donde quiera buscar la palabra con mayor frecuencia.\n");
                scanf("%d", &idBusqueda1);
                flag = verificarIdIngresado(idBusqueda1);
            }
            while (flag != 0);
            mayorFREC = mayorFrecuenciaDoc(arbol, idBusqueda1);
            mostrarNodoAFREC(mayorFREC, idBusqueda1);
            break;
        case 6:
            printf("\nIngrese la palabra: ");
            fflush(stdin);
            gets(palabra);
            printf("Palabras sugeridas a la palabra %s : \n", palabra);
            sugierePalabrasSimilares(arbol, palabra);
            break;
        case 10:
            menuTextoDiccionario();
            printf("\n");
            break;
        case 11:
            mostrarDiccionario(DICCIONARIO);
            break;
        case 12:
            mostrarArbolPreOrder(arbol);
            break;
        case 0:
            printf("\n--------------------------------\n");
            printf("\n**** GRACIAS VUELVA PRONTOS ****\n");
            printf("\n************ <3 <3 *************\n");
            printf("\n--------------------------------\n");
            exit(0);
        default:
            printf("\n***OPCION INCORRECTA***\n");
            printf("\n");
            break;
        }
        printf("\n");
        system("pause");
        system("cls");
    }
    while (control != 0);

}
