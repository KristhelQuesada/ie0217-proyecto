// ----------------------------------------------------------
// Inclusion de header files y bibliotecas necesarias
#include <iostream>
#include "Funciones.hpp"
//#include "Prestamo.hpp"
using namespace std;

// Inclusion de Enums
enum initialMenu {
    ATENCION_CLIENTE = 1,
    INFO_PRESTAMOS,
    SALIR,
    OPCIONES_MAX
};
// ----------------------------------------------------------



// ----------------------------------------------------------
//                          MAIN CODE
// ----------------------------------------------------------
int main() {
    // Variables
    string input;
    bool detener = false;
    int operacion;
    cout << "INICIO DEL PROGRAMA" << endl;

    // Inicializacion de la base de datos
    DBManager db("Hola");
    

    // Inicio del menu principal
    while (detener == false) {
        // Menu para el ususario
        cout << "\n---------------------------------\n";
        cout << "         MODO DE OPERACION";
        cout << "\n---------------------------------\n";
        cout << "1. Atencion al cliente\n";
        cout << "2. Informacion de Prestamos\n";
        cout << "5. Salir del programa";
        cout << "\n---------------------------------";
        cout << "\nIndique el modo de operacion: ";
        cin >> input;
        operacion = verifyMenuOption(input, OPCIONES_MAX); // Maneja errores
        cin.ignore();


        // Determinacion de funcion a ejecutar
        switch (operacion) {
            case ATENCION_CLIENTE: {
                cout << "hola" << endl;
                menuCS(db);
                break;
            }
            case INFO_PRESTAMOS: {
                map<string, string> loan_data = calculateLoan();

                // Esto se borra =======================================
                cout << "\nLos datos son los siguientes: " << endl;
                for (const auto& pair : loan_data) {
                    cout << pair.first << ": " << pair.second << endl;
                }
                // =====================================================
                break;
            }
            case SALIR: {
                cout << "Saliendo del sistema..." << endl;
                detener = true;
                break;
            }
            default: {
                cout << "Opcion ingresada no valida." << endl;
                break;
            }

        } // fin del switch
    } // fin del while

    return 0;
} // fin del main