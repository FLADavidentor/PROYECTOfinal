#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Producto
{
    string nombre;
    float precio;
    string descripcion;

    /*Usamos una funcion operator para que cuando tratemos de imprimir el objeto "Producto" imprima de cierta forma especifica.
     *El friend es para dar permisos de que cada vez que se llame el vector Producto en el codigo para imprimirse, se imprima de la manera que dice el operator
     *El return os; es para poder encadenar varias impresiones, y al ser un vector de varias lineas es necesario ponerlo
     *ostream se utiliza para enviar datos desde un programa a una salida, como por ejemplo la consola o un archivo de texto.*/
    friend ostream &operator<<(ostream &os, const Producto &p)
    {
        os << p.nombre << " - $" << p.precio << " \n- " << p.descripcion << endl;
        return os;
    }
};

/** Guarda los productos en el archivo "inventario.txt". */
void guardarArchivo(const vector<Producto> &inventario)
{
    ofstream archivo("inventario.txt");
    if (archivo.is_open())
    {
        for (auto const &p : inventario)/*auto const es una forma de declarar una variable de forma que su tipo sea deducido automáticamente por el compilador, y además se indique que dicha variable es constante.*/
        {
            archivo << p.nombre << " " << p.precio << " " << p.descripcion << endl;
        }
        archivo.close();
    }
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
        /** Lee los datos del archivo y crea un objeto Producto para cada línea leída.
         * El while que rodea esta línea de código se utiliza para leer todas las líneas del archivo inventario.txt hasta el final, mientras se almacenan los valores de las variables nombre, precio y descripcion en un objeto de tipo Producto que se agrega al vector inventario.*/
        while (archivo >> nombre >> precio >> ws && getline(archivo, descripcion))/*ws es para ignorar cualquier espacio en blanco como lo son espacios, saltos de linea, etc*/
        {
            inventario.push_back(Producto{nombre, precio, descripcion});
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
    cout << "Nombre: ";
    cin >> nombre;
    cout << "Precio: ";
    cin >> precio;
    cin.ignore(); // Ignorar el salto de línea dejado por cin
    cout << "Descripcion: ";
    getline(cin, descripcion);
    inventario.push_back(Producto{nombre, precio, descripcion});/*los "{}" son esteticos, se pudieron haber usado "()"*/
    cout << "Producto agregado" << endl;
}

/** Imprime todos los productos en el vector de productos. */
void mostrarInventario(const vector<Producto> &inventario)
{
    if (inventario.empty())
    {
        cout << "No hay productos en el inventario" << endl;
    }
    else
    {
        for (auto const &p : inventario)
        {
            cout << p << endl;
        }
    }
}

/** Busca un producto por su nombre en el vector de productos y lo imprime en la salida estándar. */
void buscarProducto(const vector<Producto> &inventario)
{
    if (inventario.empty())
    {
        cout << "No hay productos en el inventario" << endl;
    }
    else
    {
        string nombre;
        cout << "Nombre del producto: ";
        cin >> nombre;
        bool encontrado = false;
        for (auto const &p : inventario)/*auto const es una forma de declarar una variable de forma que su tipo sea deducido automáticamente por el compilador, y además se indique que dicha variable es constante.*/
        {
            if (p.nombre == nombre)
            {
                cout << p << endl;
                encontrado = true;
                break;
            }
        }
        if (!encontrado)
        {
            cout << "Producto no encontrado" << endl;
        }
    }
}

/** Elimina un producto por su nombre del vector de productos. */
void borrarProducto(vector<Producto> &inventario)
{
    if (inventario.empty())
    {
        cout << "No hay productos en el inventario" << endl;
    }
    else
    {
        string nombre;
        cout << "Nombre del producto a eliminar: ";
        cin >> nombre;
        bool encontrado = false;
        /** Itera sobre el vector de productos y elimina el producto si su nombre coincide con el nombre proporcionado.
         * Iterar es la funcion de recorrer los elementos de en este caso el vector inventario uno por uno, es decir, el for lo que hace es recorrer una sola vez de forma completa todo el vector inventario y si encuentra una coincidencia con el nombre proporcionado entonces borra la linea completa del vector.*/
        for (auto it = inventario.begin(); it != inventario.end(); ++it)
        {
            if (it->nombre == nombre)
            {
                inventario.erase(it);
                encontrado = true;
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

int main()
{
    vector<Producto> inventario = leerArchivo();
    int opc;
    do
    {
        cout << "\n1. Agregar producto" << endl;
        cout << "2. Mostrar inventario" << endl;
        cout << "3. Buscar producto" << endl;
        cout << "4. Borrar producto" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opc;
        system("cls");
        switch (opc)
        {
            /** Agrega un nuevo producto al vector de inventario. */
            case 1:
                agregarProducto(inventario);
                break;
            /** Imprime todos los productos en el vector de inventario. */
            case 2:
                mostrarInventario(inventario);
                break;
            /** Busca un producto por su nombre en el vector de productos y lo imprime en la salida estándar. */
            case 3:
                buscarProducto(inventario);
                break;
            /** Elimina un producto por su nombre del vector de inventario. */
            case 4:
                borrarProducto(inventario);
                break;
            case 0:
                break;
            default:
                cout << "Opcion no valida" << endl;
        }
    } while (opc != 0);
    guardarArchivo(inventario);
    return 0;
}