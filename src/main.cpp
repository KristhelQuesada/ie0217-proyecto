#include <iostream>
#include "DBManager.hpp"
using namespace std;

int main() {
    // Aca se instanciaran las clases prueba necesarias para corroborar el comportamiento
    cout << "PRUEBAS" << endl;

    // Instancia de DBManager
    DBManager mydb("Hola");
    mydb.ejecutarConsulta("SELECT * FROM Client");
    
    return 0;
}