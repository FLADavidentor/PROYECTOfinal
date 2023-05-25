#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <ctime>
#include <sstream>
#include "auxiliar.h"
#define MAX 150
#define MAX_ENTSAL 500 

using namespace std;

/*BOOLS*/

bool valordisplay = false;

/*Arreglos y variables principales*/
string FechaActual() 
{
    time_t t = time(nullptr);
    struct tm* tmpo = localtime(&t);
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
    string descripcion[MAX];
};
Inventario Items[MAX];
int TamInv = 0;

struct ManejoEntsal
{
    char codprodentsal [3];
    int entrada;
    int salida;
    int identiEntsal;//puede ser 1 o 2 (1=entrada, 2=salida)
    char fechaentsal[9]; //Fecha de movimientos de existencias
};
ManejoEntsal  Entsal[MAX_ENTSAL];
int TamEntsal = 0;


/*
Create
Read
Update
Delete
*/

/*Create*/
void agregarProducto(Inventario Inv);
/*Read*/
void mostrarProducto(int pos, int valid);
void mostrarProductos(int pos, int valid);//para mostrar todos los productos hacer un if con un bucle dentro y en el otro if solo imprimir una vez (el bool)
int buscarEntsal(char codproducto[], char fecha[]);//Producto o fecha
int buscarProducto(char codproducto[]);
void iniciarProducto(int pos);
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



void agregarProducto(Inventario Inv)
{
    Items[TamInv] = Inv;
    TamInv++;
}


void mostrarProducto(int pos, int valid)
{
    if (valid==1)
    {
        int ex=4;
         do
         {
        

        gotoxy(30,ex);
        cout << "Codigo de producto: " << Items[pos].codproductoinv << endl;
        ex++;
        gotoxy(30,ex);
        cout << "Producto: " << Items[pos].producto << endl;
        ex++;
        gotoxy(30,ex);
        cout << "Precio: $" << Items[pos].precio << endl;
        ex++;
        gotoxy(30,ex);
        cout << "Existencias: " << Items[pos].existencias << endl;
        ex++;
        gotoxy(10,ex);
        cout << "Descripcion: \n" << Items[pos].descripcion << "\n====================================================="<<endl;
        ex+5;
         } while (pos<TamInv);
        
            
    }
        

    else
    {
    gotoxy(30,4);
    cout << "Codigo de producto: " << Items[pos].codproductoinv << endl;
    gotoxy(30,5);
    cout << "Producto: " << Items[pos].producto << endl;
    gotoxy(30,6);
    cout << "Precio: $" << Items[pos].precio << endl;
    gotoxy(30,7);
    cout << "Existencias: " << Items[pos].existencias << endl;
    gotoxy(10,8);
    cout << "Descripcion: \n" << Items[pos].descripcion << endl;
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

void mostrarProductos(int pos, int valid=0)
{
    system("cls");
    if (TamInv==0)
    {
        cout << "No hay productos\n";
        return;
    }
    for (int i = 0; i < TamInv; i++)
    {
        valid=1;
        mostrarProducto(i, valid);
    }
    
    
}

void editarProducto(Inventario Inv, int pos)
{
    Items[pos] = Inv;
}

