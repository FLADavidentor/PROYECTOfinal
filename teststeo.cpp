#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*DECLARACION D LA ESTRUCTURA DE DATOS*/
struct Producto
{
    string nombre;
    float precio;

public:
    Producto(string nombre, float precio)
    {
        this->nombre = nombre;
        this->precio = precio;
    }

    string getNombre() const
    {
        return nombre;
    }

    float getPrecio() const
    {
        return precio;
    }

    friend ostream &operator<<(ostream &os, const Producto &p)
    {
        os << p.nombre << " - $" << p.precio << endl;
        return os;
    }
};

/*SI EL PROGRAMA TIENE UN VALOR NUEVO DENTRO DL VECTOR ENTONCES SE GUARDA AL "INVENTARIO.TXT"*/
void guardarArchivo(const vector<Producto> &productos)
{
    ofstream archivo;
    archivo.open("inventario.txt");
    if (archivo.is_open())
    {
        for (const Producto &p : productos)
        {
            archivo << p.getNombre() << " " << p.getPrecio() << endl;
        }
        archivo.close();
    }
}

/*ASIGNACION DEL VECTOR A PARTIR DEL ARCHIVO "INVENTARIO.TXT"*/
vector<Producto> leerArchivo()
{
    vector<Producto> productos;
    ifstream archivo("inventario.txt");
    if (archivo.is_open())
    {
        string nombre;
        float precio;
        while (archivo >> nombre >> precio)
        {
            productos.push_back(Producto(nombre, precio));
        }
        archivo.close();
    }
    return productos;
}

/*MAIN*/
int main()
{
    vector<Producto> productos = leerArchivo();
    int opc;
    /*FUNCION SWITCH*/
    do
    {
        cout << "\n1. Agregar producto" << endl;
        cout << "2. Mostrar inventario" << endl;
        cout << "3. Buscar producto" << endl;
        cout << "4. Borrar producto" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opc;
        if (opc == 1)
        {
            string nombre;
            float precio;
            system("cls");
            cout << "Nombre: ";
            cin >> nombre;
            cout << "Precio: ";
            cin >> precio;
            productos.push_back(Producto(nombre, precio));
            cout << "Producto agregado" << endl;
        }
        else if (opc == 2)
        {
            if (productos.empty())
            {
                system("cls");
                cout << "\nNo hay productos en el inventario" << endl;
            }
            else
            {
                system("cls");
                for (const Producto &p : productos)
                {
                    cout <<"\n"<< p;
                }
            }
        }
        else if (opc == 3)
        {
            if (productos.empty())
            {
                cout << "\nNo hay productos en el inventario" << endl;
            }
            else
            {
                string nombre;
                system("cls");
                cout << "\nNombre del producto: ";
                cin >> nombre;
                bool encontrado = false;
                for (const Producto &p : productos)
                {
                    if (p.getNombre() == nombre)
                    {
                        cout << p;
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado)
                {
                    cout << "\nProducto no encontrado" << endl;
                }
            }
        }
        else if (opc == 4)
        {
            if (productos.empty())
            {
                system("cls");
                cout << "\nNo hay productos en el inventario" << endl;
            }
            else
            {
                string nombre;
                cout << "\nNombre del producto a eliminar: ";
                cin >> nombre;
                bool encontrado = false;
                for (vector<Producto>::iterator it = productos.begin(); it != productos.end(); ++it)
                {
                    if (it->getNombre() == nombre)
                    {
                        system("cls");
                        productos.erase(it);
                        encontrado = true;
                        system("cls");
                        cout << "Producto eliminado" << endl;
                        break;
                    }
                }
                if (!encontrado)
                {
                    cout << "Producto no encontrado" << endl;
                }
            }
        }
        else if (opc != 0)
        {
            cout << "Opcion no valida" << endl;
        }
    } while (opc != 0);
    guardarArchivo(productos);
    return 0;
}