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
        cout << "-------------------------------------" << endl;
        cout << "|            PLATAFORMA             |" << endl;
        cout << "-------------------------------------" << endl;
        cout << "| 1. Cliente                        |" << endl;
        cout << "| 2. Prestamos                      |" << endl;
        cout << "| 3. Certificados de Deposito       |" << endl;
        cout << "| 4. Retornar a atencion al cliente |" << endl;
        cout << "-------------------------------------" << endl;
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
    std::string input;
    bool detener = false;

    while (!detener) {
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "|      SOLICITUD DE DOCUMENTOS      |" << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "| 1. Reporte de Prestamos           |" << std::endl;
        std::cout << "| 2. Registro de Transacciones      |" << std::endl;
             cout << "| 3. Retornar a atencion al cliente |" << endl;
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "Ingrese la operacion a realizar: ";

        std::cin >> input;
        option = verifyMenuOption(input, DOCS_MAX); // Maneja errores
        std::cin.ignore();

        switch (option) {
            case RDP: {
                std::cout << "Reporte de prestamos" << std::endl;

                if (id_client == 0) {
                    std::cout << "No se puede hacer reporte de prestamos porque el cliente no está registrado en el sistema." << std::endl;
                } else {
                    try {
                        std::string client_id_str = std::to_string(id_client);
                        db.exportLoanReport(client_id_str);
                    } catch (const std::invalid_argument& e) {
                        std::cout << "Número de cuenta inválido. Inténtelo de nuevo." << std::endl;
                    } catch (const std::out_of_range& e) {
                        std::cout << "Número de cuenta fuera de rango. Inténtelo de nuevo." << std::endl;
                    }
                }
                break;
            }
            case RDT: {
                std::cout << "Reporte de transacciones" << std::endl;
                std::string accountID;
                std::cout << "Ingrese el número de cuenta: ";
                std::cin >> accountID;

                bool ownsAccount = db.verificarPertenencia("BankAccount", "id_account", accountID);

                if (ownsAccount) {
                    try {
                        db.desplegarRegistroTransacciones(accountID);
                    } catch (const std::invalid_argument& e) {
                        std::cout << "Número de cuenta inválido. Inténtelo de nuevo." << std::endl;
                    } catch (const std::out_of_range& e) {
                        std::cout << "Número de cuenta fuera de rango. Inténtelo de nuevo." << std::endl;
                    }                    
                } else {
                    cout << "La cuenta  bancaria ingresada no es de su pertenencia" << endl;
                }
                    

                break;
            }
            case RETURN_CS3: {
                std::cout << "Retornando a atencion al cliente..." << std::endl;
                detener = true;
                break;
            }
            default:
                std::cout << "La transaccion seleccionada fue invalida." << std::endl;
                break;
        }
    }
}


void menuTransactions(int id_client, DBManager& db) {
    int option;
    std::string input;
    Transaccion* transaccion = nullptr;
    bool detener = false;

    while (!detener) {
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "|            TRANSACCION            |" << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "| 1. Deposito                       |" << std::endl;
        std::cout << "| 2. Retiro                         |" << std::endl;
        std::cout << "| 3. Transferencia                  |" << std::endl;
        std::cout << "| 4. Abono a prestamos              |" << std::endl;
             cout << "| 5. Retornar a atencion al cliente |" << endl;
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "Ingrese la transaccion: ";
        
        std::cin >> input;
        option = verifyMenuOption(input, TRAN_MAX); // Maneja errores
        std::cin.ignore();

        switch (option) {
            case DEPOSIT:
                std::cout << "Opcion Deposito" << std::endl;
                transaccion = new Deposito(id_client, db);
                break;
            case WITHDRAWAL:
                std::cout << "Opcion Retiro" << std::endl;
                transaccion = new Retiro(id_client, db);
                break;
            case TRANSFER:
                std::cout << "Opcion Transferencia" << std::endl;
                transaccion = new Transferencia(id_client, db);
                break;
            case LOAN_PAYMENT:
                std::cout << "Opcion Abono a prestamos" << std::endl;
                transaccion = new AbonoPrestamo(id_client, db);
                break;
            case RETURN_CS2: // Opción para retornar al menú principal
                std::cout << "Retornando a atencion al cliente..." << std::endl;
                detener = true;
                break;
            default:
                std::cout << "La transaccion seleccionada fue invalida." << std::endl;
                break;
        }

        if (transaccion) {
            transaccion->ejecutar();
            delete transaccion;
            transaccion = nullptr;
        }
    }
}