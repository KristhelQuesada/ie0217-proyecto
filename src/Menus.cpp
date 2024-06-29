#include "Funciones.hpp"
#include "Transaccion.hpp"
#include "AbonoPrestamo.hpp"
#include "Prestamo.hpp"
#include "Menus.hpp"

#include "Deposito.hpp"
#include "Retiro.hpp"
#include "Transferencia.hpp"

/*
----------------------------------------
           IMPLEMENTACION
----------------------------------------
*/

// Funcion de atencion al cliente
void menuCS(DBManager& db) {
    // Variables
    string input;
    bool detener = false;
    int operacion, cliente;

    cout << "-----------------------------------------------------" << endl;
    cout << "|          INTERFAZ DE ATENCION AL CLIENTE          |" << endl;
    cout << "-----------------------------------------------------" << endl;

    // Inicializacion del id_cliente
    cout << "Ingrese el ID del cliente: ";
    cin >> cliente;
    

    // Inicio del menu principal
    while (detener == false) {
        // Menu para el ususario
        cout << "---------------------------------------------------------------------" << endl;
        cout << "|                      OPERACIONES DISPONIBLES                      |" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "|  1. Plataforma  |  2. Transaccion  |  3. Solicitud de Documentos  |" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "\n Indique el modo de operacion: ";
        cin >> input;
        operacion = verifyMenuOption(input, CS_MAX); // Maneja errores
        cin.ignore();


        // Determinacion de funcion a ejecutar
        switch (operacion) {
            case PLATAFORMA: {
                menuPlatform(cliente, db);
                break;
            }
            case DOC_REQUEST: {
                menuDocuments(cliente, db);
                break;
            }
            case TRANSACCION: {
                menuTransactions(cliente, db);
                break;
            }
            case FINALIZAR_CS: {
                cout << "Atencion a cliente finalizada." << endl;
                detener = true;
                break;
            }
            default: {
                cout << "La operacion ingresada no es valida." << endl;
                break;
            }
        }
    }
}

// Menus del menu de atencion al cliente
void menuPlatform(int id_client, DBManager& db) {
    // Variables
    string input;
    bool detener = false;
    int modo;

    // Instancias predefinidas
    //Cliente* cliente = Cliente();
    Prestamo* prestamo = new Prestamo(id_client, db);

    // Inicio del menu principal
    while (detener == false) {
        // Menu para el ususario
        cout << "------------------------------------" << endl;
        cout << "|            PLATAFORMA            |" << endl;
        cout << "------------------------------------" << endl;
        cout << "|  1. Cliente                      |" << endl;
        cout << "|  2. Prestamos                    |" << endl;
        cout << "|  3. Certificados de Deposito     |" << endl;
        cout << "|  4. Retornar a CS                |" << endl;
        cout << "------------------------------------" << endl;
        cout << "\n Indique el modo de operacion: ";
        cin >> input;
        modo = verifyMenuOption(input, OPT_PLAT_MAX); // Maneja errores
        cin.ignore();


        // Determinacion de funcion a ejecutar
        switch (modo) {
            case CLIENTE: {
                cout << "cliente" << endl;
                break;
            }
            case LOAN: {
                // Crear un prestamo
                prestamo->createLoan();

                // Ver todos los prestamos
                prestamo->viewAll();

                // Buscar un prestamo
                prestamo->searchLoans();
                break;
            }    
            case CDP: {
                cout << "cdp" << endl;
                break;
            }
            case RETURN_CS: {
                cout << "Consulta en plataforma finalizada." << endl;
                detener = true;
                break;
            }
            default: {
                cout << "La operacion ingresada no es valida." << endl;
                break;
            }
        }

    }

    // Liberamos memoria
    delete prestamo;
}


void menuDocuments(int id_client, DBManager& db) {
    int option;
    string input;
    Transaccion* transaccion = nullptr;

    cout << "-------------------------------------" << endl;
    cout << "|            TRANSACCION            |" << endl;
    cout << "-------------------------------------" << endl;
    cout << "|  1. Deposito                      |" << endl;
    cout << "|  2. Retiro                        |" << endl;
    cout << "|  3. Transferencia                 |" << endl;
    cout << "|  3. Abono a prestamos             |" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Ingrese la transaccion: " << endl;


    cin >> input;
    option = verifyMenuOption(input, DOCS_MAX); // Maneja errores
    cin.ignore();

    switch (option) {
        case RDP:
            cout << "Reporte de prestamos" << endl;
            break;
        case RDT:
            cout << "Registro de transacciones" << endl;
            break;
        default:
            cout << "La transaccion seleccionada fue invalida." << endl;
            break;
    }
}


void menuTransactions(int id_client, DBManager& db) {
    int option;
    string input;
    Transaccion* transaccion = nullptr;

    cout << "-------------------------------------" << endl;
    cout << "|            TRANSACCION            |" << endl;
    cout << "-------------------------------------" << endl;
    cout << "|  1. Deposito                      |" << endl;
    cout << "|  2. Retiro                        |" << endl;
    cout << "|  3. Transferencia                 |" << endl;
    cout << "|  3. Abono a prestamos             |" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Ingrese la transaccion: " << endl;


    cin >> input;
    option = verifyMenuOption(input, TRAN_MAX); // Maneja errores
    cin.ignore();

    switch (option) {
        case DEPOSIT:
            cout << "Opcion 1" << endl;
            transaccion = new Deposito(id_client, db);
            break;
        case WITHDRAWAL:
            cout << "Opcion 2" << endl;
            transaccion = new Retiro(id_client, db);
            break;
        case TRANSFER:
            cout << "Opcion 3" << endl;
            // transaccion = new Transferencia(id_client, db);
            break;
        case LOAN_PAYMENT:
            transaccion = new AbonoPrestamo(id_client, db);
            break;
        default:
            cout << "La transaccion seleccionada fue invalida." << endl;
            break;
    }

    if (transaccion) {
        transaccion->ejecutar();
        delete transaccion;
    }
}