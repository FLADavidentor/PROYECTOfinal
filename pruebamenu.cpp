#include <iostream>
#include <iomanip>
using namespace std;

void imprimirMensaje() {
    cout << "\033[1;33m"
         << "Bienvenido a Cyberstock"
         << "\033[0m" << endl;
}

int main() {
    imprimirMensaje();
    return 0;
}