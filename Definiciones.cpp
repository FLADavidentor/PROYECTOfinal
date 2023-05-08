#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Usuario
{
    string usuario;
    string contrasenia;
};

struct Producto
{
    string nombre;
    int existencias = 0;
    float precio;
    string descripcion;

    /*Usamos una funcion operator para que cuando tratemos de imprimir el objeto "Producto" imprima de cierta forma especifica.
     *El friend es para dar permisos de que cada vez que se llame el vector Producto en el codigo para imprimirse, se imprima de la manera que dice el operator
     *El return os; es para poder encadenar varias impresiones, y al ser un vector de varias lineas es necesario ponerlo
     *ostream se utiliza para enviar datos desde un programa a una salida, como por ejemplo la consola o un archivo de texto.*/
    friend ostream &operator<<(ostream &os, const Producto &p)
    {
        os << p.nombre << " - $" << p.precio << "\nexistencias: " << p.existencias << " \n- " << p.descripcion << endl;
        return os;
    }
};

/** Guarda los productos en el archivo "inventario.txt". */
void guardarArchivo(const vector<Producto> &inventario)
{
    ofstream archivo("inventario.txt");
    if (archivo.is_open())
    {
        for (auto const &p : inventario)
        {
            archivo << p.nombre << " " << p.existencias << " " << p.precio << " " << p.descripcion << endl;
        }
        archivo.close();
    }
}

/** Guarda los usuarios en el archivo "Credenciales.txt". */
void guardarUsuario(const vector<Usuario> &Credenciales)
{
    ofstream archivo("Credenciales.txt");
    if (archivo.is_open())
    {
        for (auto const &u : Credenciales)
        {
            archivo << u.contrasenia << " " << u.usuario << endl;
        }
        archivo.close();
    }
}

/** Lee los credenciales del archivo "Credenciales.txt" y los retorna en un vector. */
vector<Usuario> leerUsuario()
{
    vector<Usuario> Credenciales;
    ifstream archivo("Credenciales.txt");
    if (archivo.is_open())
    {
        string usuario;
        string contrasenia;
        /** Lee los datos del archivo y crea un objeto Usuario para cada línea leída.
         * El while que rodea esta línea de código se utiliza para leer todas las líneas del archivo Credenciales.txt hasta el final, mientras se almacenan los valores de las variables nombre, precio y descripcion en un objeto de tipo Producto que se agrega al vector inventario.*/
        while (archivo >> contrasenia >> ws && getline(archivo, usuario))
        {
            Credenciales.push_back(Usuario{usuario, contrasenia});
        }
        archivo.close();
    }
    return Credenciales;
}

/** Lee los productos del archivo "inventario.txt" y los retorna en un vector. */
vector<Producto> leerArchivo()
{
    vector<Producto> inventario;
    ifstream archivo("inventario.txt");
    if (archivo.is_open())
    {
        string nombre, descripcion;
        float precio;
        int existencias = 0;
        /** Lee los datos del archivo y crea un objeto Producto para cada línea leída.
         * El while que rodea esta línea de código se utiliza para leer todas las líneas del archivo inventario.txt hasta el final, mientras se almacenan los valores de las variables nombre, precio y descripcion en un objeto de tipo Producto que se agrega al vector inventario.*/
        while (archivo >> nombre >> existencias >> precio >> ws && getline(archivo, descripcion))
        {
            inventario.push_back(Producto{nombre, existencias, precio, descripcion});
        }
        archivo.close();
    }
    return inventario;
}

/** Agrega un nuevo producto al vector de productos. */
void agregarProducto(vector<Producto> &inventario)
{
    string nombre, descripcion;
    float precio;
    int existencias = 0;
    cout << "Nombre: ";
    cin >> nombre;
    cout << "Existencias: ";
    cin >> existencias;
    cout << "Precio: ";
    cin >> precio;
    cout << "Descripcion: ";
    cin.ignore();
    getline(cin, descripcion);
    inventario.push_back(Producto{nombre, existencias, precio, descripcion});
}

/** Modifica un producto del vector de productos. */
void modificarProducto(vector<Producto> &inventario)
{
    int opcion;
    cout << "¿Que producto deseas modificar?\n";
    for (int i = 0; i < inventario.size(); i++)
    {
        cout << i + 1 << ". " << inventario[i].nombre << endl;
    }
    cin >> opcion;
    opcion--;
    cout << "Nombre: ";
    cin >> inventario[opcion].nombre;
    cout << "Existencias: ";
    cin >> inventario[opcion].existencias;
    cout << "Precio: ";
    cin >> inventario[opcion].precio;
    cout << "Descripcion: ";
    cin.ignore();
    getline(cin, inventario[opcion].descripcion);
}

/** Elimina un producto del vector de productos. */
void eliminarProducto(vector<Producto> &inventario)
{
    int opcion;
    cout << "¿Que producto deseas eliminar?\n";
    for (int i = 0; i < inventario.size(); i++)
    {
        cout << i + 1 << ". " << inventario[i].nombre << endl;
    }
    cin >> opcion;
    opcion--;
    inventario.erase(inventario.begin() + opcion);
}

/** Imprime todos los productos del vector de productos. */
void imprimirProductos(const vector<Producto> &inventario)
{
    for (auto const &p : inventario)
    {
        cout << p << endl;
    }
}