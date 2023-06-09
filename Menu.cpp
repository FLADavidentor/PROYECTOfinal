#include <iostream>
#include <fstream>
#include <vector>
#include "Definiciones.cpp"
using namespace std;
void menu(){

vector<Producto> inventario = leerArchivo();
    vector<Usuario> Credenciales = leerUsuario();
    string usuarionum;
    string contrasenianum;
    int opcion;
    cout << "Nombre de Usuario: ";
    cin >> usuarionum;
    cout << "Contrasenia: ";
    cin >> contrasenianum;
    bool encontradousuario = false;
    for (auto const &u : Credenciales) /*auto const es una forma de declarar una variable de forma que su tipo sea deducido automáticamente por el compilador, y además se indique que dicha variable es constante.*/
    {
        if (u.usuario == usuarionum && u.contrasenia == contrasenianum)
        {
            do
            {

                cout << "Menu:\n";
                cout << "1. Agregar producto\n";
                cout << "2. Modificar producto\n";
                cout << "3. Eliminar producto\n";
                cout << "4. Imprimir inventario\n";
                cout << "5. Salir\n";
                cout << "Opcion: ";
                cin >> opcion;

                switch (opcion)
                {
                case 1:
                    agregarProducto(inventario);
                    guardarArchivo(inventario);
                    break;
                case 2:

                    modificarProducto(inventario);
                    guardarArchivo(inventario);
                    break;
                case 3:
                    eliminarProducto(inventario);
                    guardarArchivo(inventario);
                    break;
                case 4:
                    imprimirProductos(inventario);
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida\n";
                }
            } while (opcion != 5);
            encontradousuario = true;
        }
    }
    if (!encontradousuario)
    {
        cout << "Contrasenia o usuario incorrectos" << endl;
    }
    guardarUsuario(Credenciales);







}