#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <ctime>
#include <sstream>
#include "auxiliar.h"
#define MAX 150
#define CS 36
#define MAX_ENTSAL 500

using namespace std;

/*Arreglos y variables principales*/
string FechaActual()
{
    time_t t = time(nullptr);
    struct tm *tmpo = localtime(&t);
    stringstream gfecha;
    gfecha << put_time(tmpo, "%d/%m/%Y");
    return gfecha.str();
};

struct Inventario
{
    char codproductoinv[3];
    char producto[20];
    float precio;
    int existencias;
    char descripcion[MAX];
};
Inventario Items[MAX];
int TamInv = 0;

struct ManejoEntsal
{
    char codprodentsal[3];
    int entrada;
    int salida;
    int identiEntsal;    // puede ser 1 o 2 (1=entrada, 2=salida)
    char fechaentsal[9]; // Fecha de movimientos de existencias
};
ManejoEntsal Entsal[MAX_ENTSAL];
int TamEntsal = 0;

struct CredencialesA
{
    char nickname[CS];
    char password[CS];
};
CredencialesA Credenciales[10];
int TamCred = 0;

/*
Create
Read
Update
Delete
*/

/*Create*/
void agregarProducto(Inventario Inv);
void agregarCredenciales(CredencialesA Cred);
/*Read*/
void mostrarProducto(int pos, int valid);
void mostrarProductos(int valid);                   // para mostrar todos los productos hacer un if con un bucle dentro y en el otro if solo imprimir una vez (el bool)
int buscarEntsal(char codproducto[], char fecha[]); // Producto o fecha
int buscarProducto(char codproducto[]);
void iniciarProducto(int pos);
void mostrarCredenciales(int posC);
int buscarCredenciales();
Inventario obtenerInv(int pos);
/*Update*/
void editarProducto(Inventario Inv, int pos);
/*Delete*/
void eliminarProducto(int pos);
void eliminarHistorial(int pos, char fecha[]);

/*Menus*/
int menu();
int menuEditarProd();
void start();

/*Archivos*/
FILE *Inventariofile;
void guardarInv();
void leerInv();
int CalcTamInv(FILE *archivo);
FILE *Credencialesfile;
void guardarCred();
void leerCred();
int CalcTamCred(FILE *archivo);

void agregarProducto(Inventario Inv)
{
    Items[TamInv] = Inv;
    TamInv++;
}

void mostrarProducto(int pos, int valid)
{
    if (valid == 1)
    {
        pos = 0;
        int ex = 4;
        do
        {

            gotoxy(30, ex);
            cout << "Codigo de producto: " << Items[pos].codproductoinv << endl;
            ex++;
            gotoxy(30, ex);
            cout << "Producto: " << Items[pos].producto << endl;
            ex++;
            gotoxy(30, ex);
            cout << "Precio: $" << Items[pos].precio << endl;
            ex++;
            gotoxy(30, ex);
            cout << "Existencias: " << Items[pos].existencias << endl;
            ex++;
            gotoxy(10, ex);
            cout << "Descripcion: \n"
                 << Items[pos].descripcion << "\n=====================================================" << endl;
            ex += 5;
            pos++;
        } while (pos < TamInv);
    }

    else
    {
        gotoxy(30, 4);
        cout << "Codigo de producto: " << Items[pos].codproductoinv << endl;
        gotoxy(30, 5);
        cout << "Producto: " << Items[pos].producto << endl;
        gotoxy(30, 6);
        cout << "Precio: $" << Items[pos].precio << endl;
        gotoxy(30, 7);
        cout << "Existencias: " << Items[pos].existencias << endl;
        gotoxy(10, 8);
        cout << "Descripcion: \n"
             << Items[pos].descripcion << endl;
    }
}

Inventario obtenerInv(int pos)
{
    return Items[pos];
}

int buscarProducto(char codproducto[])
{
    int posicion = 0;
    for (int i = 0; i < TamInv; i++)
    {
        if (strcmp(codproducto, Items[i].codproductoinv) == 0)
        {
            posicion = i;
            break;
        }
    }
    return posicion;
}

void mostrarProductos(int valid = 0)
{
    system("cls");
    if (TamInv == 0)
    {
        cout << "No hay productos\n";
        return;
    }
    for (int i = 0; i < TamInv; i++)
    {
        valid = 1;
        mostrarProducto(i, valid);
    }
}

void editarProducto(Inventario Inv, int pos)
{
    Items[pos] = Inv;
}

void Logo()
{
    cout << "\033[1;33m"
         << "CyberStock"
         << "\033[0m" << endl;
}

int buscarCredenciales()
{
    leerCred();
    bool Pase = false;
    char nick[CS];
    char passw[CS];
    CredencialesA Cred;
    gotoxy(40, 4);
    Logo();
    gotoxy(40, 6);

    cout << "Ingrese sus credenciales";

    gotoxy(35, 7);

    cout << "Nombre: ";

    gotoxy(35, 8);
    cout << "Contraseña: ";

    gotoxy(44, 7);

    scanf(" %[^\n]", nick);

    gotoxy(47, 8);

    scanf(" %[^\n]", passw);

    if (strcmp(Cred.nickname, nick) == 0 && strcmp(Cred.password, passw) == 0)
    {
        Pase = true;
    }
    else
    {
        system("cls");
        gotoxy(40, 5);
        cout << "CONTRASENIA O USUARIO NO VALIDO";
    }
    return Pase;
}

//================================================MENUS============================================
int menu()
{
    int op;
    int Pase;
    Pase = buscarCredenciales();
    if (Pase == true)
    {
                gotoxy(25, 5);
            Logo();
        gotoxy(15, 6);
        cout << "Cantidad de registros: " << TamInv << endl;
        gotoxy(10, 9);
        cout << " 1. Agregar Producto \n";
        gotoxy(10, 10);
        cout << " 2. Editar Producto \n";
        gotoxy(10, 11);
        cout << " 3. Eliminar Producto \n";
        gotoxy(10, 12);
        cout << " 4. Buscar Producto \n";
        gotoxy(10, 13);
        cout << " 5. Mostrar Inventario \n";
        gotoxy(10, 14);
        cout << " 6. Mostrar Entradas y Salidas \n";
        gotoxy(10, 15);
        cout << " 7. Buscar Entradas y Salidas \n";
        gotoxy(10, 16);
        cout << " 8. Mostrar Credenciales \n";
        gotoxy(10, 17);
        cout << " 9. Agregar Credenciales \n";
        gotoxy(10, 18);
        cout << " 10. Editar Credenciales \n";
        gotoxy(10, 19);
        cout << " 11. Eliminar Credenciales \n";
        gotoxy(10, 20);
        cout << " 12. Administrar Existencias \n";
        gotoxy(10, 21);
        cout << " Digite la opcion: ";
        gotoxy(29, 21);
        cin >> op;
    }
    return op;
}

void start()
{
    int op;
    char codproduct[3];
    int pos;
    Inventario Inv;
    op=menu();
    do
    {
        switch (op)
        {
        case 1:
            gotoxy(30, 4);
            cout << "Codigo de producto: ";
            gotoxy(30, 5);
            cout << "Producto: ";
            gotoxy(30, 6);
            cout << "Precio: $";
            gotoxy(30, 7);
            cout << "Existencias: ";
            gotoxy(10, 8);
            cout << "Descripcion: ";
            gotoxy(50, 4);
            cin >> Inv.codproductoinv;
            gotoxy(40, 5);
            scanf(" %[^\n]", Inv.producto);
            gotoxy(39, 6);
            cin >> Inv.precio;
            gotoxy(43, 7);
            cin >> Inv.existencias;
            gotoxy(23, 8);
            scanf(" %[^\n]", Inv.descripcion);
            agregarProducto(Inv);
            system("pause");
            guardarInv();
            break;
        case 2:
            system("cls");
            cout << "Escribe el Codigo del producto a buscar: ";
            scanf(" %[^\n]", codproduct);
            system("cls");
            pos = buscarProducto(codproduct);
            gotoxy(6, 3);
            cout << "DATOS ACTUALES\n";
            mostrarProducto(pos, 0);
            gotoxy(50, 3);
            cout << "DATOS A EDITAR\n";
            gotoxy(40, 4);
            cout << "Codigo de producto: ";
            gotoxy(40, 5);
            cout << "Producto: ";
            gotoxy(40, 6);
            cout << "Precio: $";
            gotoxy(40, 7);
            cout << "Existencias: ";
            gotoxy(40, 8);
            cout << "Descripcion: ";
            gotoxy(60, 4);
            scanf(" %[^\n]", Inv.codproductoinv);
            gotoxy(48, 5);
            scanf(" %[^\n]", Inv.producto);
            gotoxy(50, 6);
            cin >> Inv.precio;
            gotoxy(46, 7);
            cin >> Inv.existencias;
            gotoxy(47, 8);
            scanf(" %[^\n]", Inv.descripcion);
            editarProducto(Inv, pos);
            gotoxy(40, 11);
            cout << "Registro actualizado...\n";
            system("pause");
            guardarInv();
        default:
            break;
        }
    } while (op != 13);
}

// Para calcular el numero de productos totales guardados y guardar archivo bin

void guardarInv()
{
    Inventariofile = fopen("datosInv.bin", "wb");              // Abre el archivo "datos.bin" en modo de escritura binaria
    fwrite(Items, sizeof(Inventario), TamInv, Inventariofile); // Escribe los datos del inventario en el archivo
    fclose(Inventariofile);                                    // Cierra el archivo
}

void leerInv()
{
    Inventariofile = fopen("datosInv.bin", "rb"); // Abre el archivo "datos.bin" en modo de lectura binaria
    if (Inventariofile == NULL)                   // Comprueba si el archivo no existe
    {
        return; // Si el archivo no existe, la función simplemente regresa
    }
    TamInv = CalcTamInv(Inventariofile);                   // Calcula el número de productos en el archivo y lo almacena en la variable TamInv
    fread(Items, sizeof(Inventario), MAX, Inventariofile); // Lee los datos del archivo y los guarda en la estructura de inventario Items
    fclose(Inventariofile);                                // Cierra el archivo
}

int CalcTamInv(FILE *archivo)
{
    int tam_archivo, num_productos; // Declaración de variables locales

    // Obtener el tamaño delarchivo
    fseek(archivo, 0, SEEK_END);  // Mueve el puntero del archivo al final del archivo
    tam_archivo = ftell(archivo); // Obtiene la posición actual del puntero, que corresponde al tamaño total del archivo
    rewind(archivo);              // Mueve el puntero del archivo al inicio del archivo

    // Calcular el número de productos
    num_productos = tam_archivo / sizeof(Inventario); // Divide el tamaño total del archivo por el tamaño de la estructura de inventario para obtener el número de productos almacenados en el archivo
    return num_productos;                             // Devuelve el número de productos almacenados en el archivo
}

void guardarCred()
{
    Credencialesfile = fopen("datosCred.bin", "wb");                        // Abre el archivo "datos.bin" en modo de escritura binaria
    fwrite(Credenciales, sizeof(CredencialesA), TamCred, Credencialesfile); // Escribe los datos del inventario en el archivo
    fclose(Credencialesfile);                                               // Cierra el archivo
}

void leerCred()
{
    Credencialesfile = fopen("datosCred.bin", "rb"); // Abre el archivo "datos.bin" en modo de lectura binaria
    if (Credencialesfile == NULL)                    // Comprueba si el archivo no existe
    {
        return; // Si el archivo no existe, la función simplemente regresa
    }
    TamCred = CalcTamCred(Credencialesfile);                          // Calcula el número de productos en el archivo y lo almacena en la variable TamInv
    fread(Credenciales, sizeof(CredencialesA), 10, Credencialesfile); // Lee los datos del archivo y los guarda en la estructura de inventario Items
    fclose(Credencialesfile);                                         // Cierra el archivo
}

int CalcTamCred(FILE *archivo)
{
    int tam_archivo, num_Credenciales; // Declaración de variables locales

    // Obtener el tamaño delarchivo
    fseek(archivo, 0, SEEK_END);  // Mueve el puntero del archivo al final del archivo
    tam_archivo = ftell(archivo); // Obtiene la posición actual del puntero, que corresponde al tamaño total del archivo
    rewind(archivo);              // Mueve el puntero del archivo al inicio del archivo

    // Calcular el número de productos
    num_Credenciales = tam_archivo / sizeof(CredencialesA); // Divide el tamaño total del archivo por el tamaño de la estructura de inventario para obtener el número de productos almacenados en el archivo
    return num_Credenciales;                                // Devuelve el número de productos almacenados en el archivo
}