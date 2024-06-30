#include "Funciones.hpp"
#include "Transaccion.hpp"
#include "AbonoPrestamo.hpp"
#include "CDP.hpp"

#include "Menus.hpp"
#include "Prestamo.hpp"
#include "Deposito.hpp"
#include "Retiro.hpp"
#include "Transferencia.hpp"

#include "Cliente.hpp"
#include <cctype> // Para toupper
/*
----------------------------------------
           IMPLEMENTACION
----------------------------------------
*/

// Funcion de atencion al cliente
void menuCS(DBManager& db) {
    // Variables
    std::string input;
    bool detener = false;
    int operacion, cliente = 0; // Inicializamos cliente a 0
    char registrado;

    // Encabezado bonito
    std::cout << "=====================================================" << std::endl;
    std::cout << "||          INTERFAZ DE ATENCION AL CLIENTE        ||" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "    Bienvenido al sistema de atencion al cliente.    " << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "                                                     " << std::endl;


    // Preguntar si el cliente está registrado en el banco
    while (true) {
        std::cout << "¿El cliente está registrado en el banco? (S/N): ";
        std::cin >> registrado;
        registrado = toupper(registrado); // Convertir a mayúsculas para evitar problemas de comparación

        if (registrado == 'S' || registrado == 'N') {
            break;
        } else {
            std::cout << "Opción inválida. Inténtelo de nuevo.\n";
        }
    }

    // Inicializacion del id_cliente
    if (registrado == 'S') {
        std::cout << "Ingrese el ID del cliente: ";
        std::cin >> cliente;
    } else {
        std::cout << "El cliente no está registrado en el banco. ID de cliente asignado: 0\n";
    }
    
    std::cout << "                                                     " << std::endl;
    std::cout << "                                                     " << std::endl;
    std::cout << "                                                     " << std::endl;

    // Inicio del menu principal
    while (detener == false) {
        // Menu para el ususario
        cout << "---------------------------------------------------------------------" << endl;
        cout << "|                      OPERACIONES DISPONIBLES                      |" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "|  1. Plataforma  |  2. Transaccion  |  3. Solicitud de Documentos  |" << endl;
        cout << "|  4. Finalizar   |                  |                              |" << endl;
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
    Cliente* cliente = new Cliente();
    Prestamo* prestamo = new Prestamo(id_client, db);
    CDP* certificado = new CDP(id_client, db);

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
                bool detenerCliente = false;
                while (!detenerCliente) {
                    cout << "Cliente - Opciones:\n1. Crear Cliente\n2. Ver Clientes\n3. Actualizar Cliente\n4. Eliminar Cliente\n5. Retornar" << endl;
                    cout << "Indique el modo de operacion: ";
                    cin >> input;
                    int subModo = verifyMenuOption(input, 5); // Maneja errores
                    cin.ignore();

                    switch (subModo) {
                        case 1:
                            cliente->obtenerInformacion(db);
                            break;
                        case 2:
                            cliente->imprimirDatos(db);
                            break;
                        case 3:
                            cliente->actualizarDatos(db);
                            break;
                        case 4:
                            cliente->eliminarCliente(db);
                            break;
                        case 5:
                            detenerCliente = true;
                            break;
                        default:
                            cout << "La operacion ingresada no es valida." << endl;
                            break;
                    }
                }
                break;
            }
            case LOAN: {
                bool detenerPrestamo = false;
                while (!detenerPrestamo) {
                    cout << "Prestamos - Opciones:\n1. Crear Prestamo\n2. Ver Prestamos\n3. Buscar Prestamo\n4. Retornar" << endl;
                    cout << "Indique el modo de operacion: ";
                    cin >> input;
                    int subModo = verifyMenuOption(input, 4); // Maneja errores
                    cin.ignore();

                    switch (subModo) {
                        case 1:
                            prestamo->createLoan();
                            break;
                        case 2:
                            prestamo->viewAll();
                            break;
                        case 3:
                            prestamo->searchLoans();
                            break;
                        case 4:
                            detenerPrestamo = true;
                            break;
                        default:
                            cout << "La operacion ingresada no es valida." << endl;
                            break;
                    }
                }
                break;
            }    
            case CerDP: {
                bool detenerCDP = false;
                while (!detenerCDP) {
                    cout << "Certificados de Deposito - Opciones:\n1. Crear CDP\n2. Ver CDP\n3. Buscar CDP\n4. Retornar" << endl;
                    cout << "Indique el modo de operacion: ";
                    cin >> input;
                    int subModo = verifyMenuOption(input, 4); // Maneja errores
                    cin.ignore();

                    switch (subModo) {
                        case 1:
                            certificado->createCDP();
                            break;
                        case 2:
                            certificado->viewAll();
                            break;
                        case 3:
                            certificado->searchCDP();
                            break;
                        case 4:
                            detenerCDP = true;
                            break;
                        default:
                            cout << "La operacion ingresada no es valida." << endl;
                            break;
                    }
                }
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
    delete certificado;
    delete cliente;
}


void menuDocuments(int id_client, DBManager& db) {
    int option;
    string input;
    Transaccion* transaccion = nullptr;

    cout << "-------------------------------------" << endl;
    cout << "|      SOLICITUD DE DOCUMENTOS      |" << endl;
    cout << "-------------------------------------" << endl;
    cout << "|  1. Reporte de Prestamos          |" << endl;
    cout << "|  2. Registro de Transacciones     |" << endl;
    cout << "|  3. Retornar a CS                 |" << endl;
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