#include <iostream>      // Directiva que proporciona funcionalidades para la entrada y salida en consola 
#include <iomanip>       // Directiva que permite manipular la entrada y salida de datos
#include <sstream>       // Directiva que facilita trabajar con cadenas de flujo 
#include <chrono>        // Directiva que permite trabajar con funciones y estructuras relacionadas con el tiempo 
#include <ctime>         // Directiva que permite trabajar con funciones y estructuras relacionadas con el tiempo 
#include <algorithm>     // Directiva que proporciona algoritmos estándar 
#include <stdexcept>     // Directiva que incluye clases para el manejo de excepciones estándar 

#include "Cuenta.hpp"           // Incluye un archivo

// Constructor por defecto
Cuenta::Cuenta() {

    idCliente = 0; 
    idCuenta = 0;
    moneda = "";
    saldo = 0.00;
    fechaApertura = "";
    
}

// Constructor para inicializar una cuenta
Cuenta::Cuenta(int idCliente, int idCuenta, const std::string& moneda, double saldo, const std::string& fechaApertura)
    : idCliente(idCliente), idCuenta(idCuenta), moneda(moneda), saldo(saldo), fechaApertura(fechaApertura) {

}

// Método para obtener la información de la cuenta bancaria
void Cuenta::obtenerInformacion(DBManager& dbManager) {


    // Obtener ID del cliente
    while (true) {
        try {
            std::cout << "Ingrese el ID del cliente (máximo 9 dígitos): ";
            std::string input;
            std::getline(std::cin, input);

            // Verificar longitud de la entrada
            if (input.empty() || input.size() > 9) {
                throw std::out_of_range("La longitud del ID del cliente excede el máximo permitido (9 dígitos).");
            }

            // Convertir la entrada a int
            std::stringstream ss(input);
            if (!(ss >> idCliente) || !ss.eof()) {
                throw std::invalid_argument("Debe ingresar un número entero válido.");
            }

            // Si todo está bien, salir del bucle
            break;

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            std::cout << "Ingrese la moneda de la cuenta que se desea crear (CRC O USD): ";
            std::getline(std::cin, moneda);

            // Verificar tipo de dato
            for (char c : moneda) {
                if (!isalpha(c) && !isspace(c)) {
                    throw std::invalid_argument("La moneda debe ser una cadena de texto.");
                }
            }

            // Verificar tamaño de dato
            if (moneda.length() > 3) {
                throw std::out_of_range("No se especifica la moneda correctamente o se excede de la longitud máxima permitida.");
            }

            break; // Si todo está bien, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Consulta para verificar la existencia del cliente
    std::string consultaCliente = "SELECT id_client FROM Client WHERE id_client = '" + std::to_string(idCliente) + "'";
    std::string resultadoCliente = dbManager.ejecutarConsulta(consultaCliente);

    if (resultadoCliente.empty()) {
        
        std::cerr << "El cliente con ID " << idCliente << " no está registrado en la base de datos. No se puede actualizar." << std::endl;
        return; // Salir del método si el cliente no está registrado
    }

    // Consultar la cantidad de cuentas del cliente
    std::string consultaCantidad = "SELECT COUNT(*) AS id_account FROM BankAccount WHERE id_client = '" + std::to_string(idCliente) + "'";
    std::string resultadoCantidad = dbManager.ejecutarConsulta(consultaCantidad);
    int cantidadCuentas = std::stoi(resultadoCantidad); // Convertir resultado a entero

    // Consultar el tipo de cuentas del cliente (colones o dólares)
    std::string consultaTipo = "SELECT currency FROM BankAccount WHERE id_client = '" + std::to_string(idCliente) + "'";
    std::string resultadoTipo = dbManager.ejecutarConsulta(consultaTipo);

    // Lógica para determinar si se puede crear la cuenta
    if (cantidadCuentas >= 2) {
        std::cout << "El cliente ya tiene dos cuentas asociadas. No se puede crear más cuentas." << std::endl;
    } else if (resultadoTipo.find("CRC") != std::string::npos && moneda == "CRC") {
        std::cout << "El cliente ya tiene una cuenta en colones. No se puede crear otra cuenta en colones." << std::endl;
    } else if (resultadoTipo.find("USD") != std::string::npos && moneda == "USD") {
        std::cout << "El cliente ya tiene una cuenta en dólares. No se puede crear otra cuenta en dólares." << std::endl;
    } else {

        while (true) {
            try {
            std::cout << "Ingrese el ID de la cuenta a crear (máximo 10 dígitos): ";
            std::string input;
            std::getline(std::cin, input);

            // Verificar tipo de dato (debe ser un entero)
            std::stringstream ss(input);
            int temp;
            if (!(ss >> temp) || !ss.eof()) {
                throw std::invalid_argument("El ID de la cuenta debe ser un dato número entero.");
            }

            // Verificar tamaño de dato
            if (input.length() > 10) {
                throw std::out_of_range("El ID de la cuenta excede la longitud máxima permitida.");
            }

            idCuenta = temp; // Asignar el valor convertido a int a idCliente

            break; // Si todo está bien, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Función que obtiene la fecha actual
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_tm = std::localtime(&now_time);
    std::stringstream ss;
    ss << std::put_time(local_tm, "%Y-%m-%d");
    fechaApertura = ss.str();

    // Construir la consulta SQL
    std::string query = "INSERT INTO BankAccount (id_account, id_client, currency, opening_date) VALUES (";
    query += std::to_string(idCuenta) + ", ";
    query += std::to_string(idCliente) + ", ";
    query += "'" + moneda + "', ";
    query += "'" + fechaApertura + "')";

    // Ejecutar la consulta SQL
    dbManager.ejecutarSQL(query);

    // Actualizar id_colones_account o id_dólares_account en la tabla Client en función de la moneda ingresada 
    std::string consultaActualizar = "UPDATE Client SET ";

    if (moneda == "CRC") {
        consultaActualizar += "id_colones_account = (SELECT id_account FROM BankAccount WHERE id_client = '" + std::to_string(idCliente) + "' AND currency = 'CRC')";
    } else if (moneda == "USD") {
        consultaActualizar += "id_dólares_account = (SELECT id_account FROM BankAccount WHERE id_client = '" + std::to_string(idCliente) + "' AND currency = 'USD')";
    }

    consultaActualizar += " WHERE id_client = '" + std::to_string(idCliente) + "'";

    // Ejecutar la consulta SQL para actualizar las cuentas
    dbManager.ejecutarSQL(consultaActualizar);

    std::cout << "Cuenta agregada correctamente." << std::endl;
    }

}


// Metodo para eliminar cuenta
void Cuenta::eliminarCuenta(DBManager& dbManager) {

    // Pedir y validar el ID del cliente a eliminar
    // Obtener ID del cliente
    while (true) {
        try {
            std::cout << "Ingrese el ID del cliente que desea eliminar una cuenta (máximo 9 dígitos): ";
            std::string input;
            std::getline(std::cin, input);

            // Verificar longitud de la entrada
            if (input.empty() || input.size() > 9) {
                throw std::out_of_range("La longitud del ID del cliente excede el máximo permitido (9 dígitos).");
            }

            // Convertir la entrada a int
            std::stringstream ss(input);
            if (!(ss >> idCliente) || !ss.eof()) {
                throw std::invalid_argument("Debe ingresar un número entero válido.");
            }

            // Si todo está bien, salir del bucle
            break;

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Consulta para verificar la existencia del cliente
    std::string consultaClient = "SELECT client_name, client_lastname FROM Client WHERE id_client = '" + std::to_string(idCliente) + "'";
    std::string columnaClient = "client_name";
    std::string resultadoClient = dbManager.ejecutarConsulta(consultaClient);

    if (resultadoClient.empty()) {
        std::cerr << "El cliente con ID " << idCliente << " no esta registrado en la base de datos." << std::endl;
        return;
    }

    // Verifica si posee cuentas
    std::cout << std::endl << "Cliente registrado" << std::endl;;
    std::string consultaAccount = "SELECT id_account FROM BankAccount WHERE id_client = " + std::to_string(idCliente);
    std::string columnaAccount = "id_account"; // La columna que quieres obtener
    std::string resultadoAccount = dbManager.ejecutarConsulta(consultaAccount);


    if (resultadoAccount.empty()) {
        std::cerr << "El cliente no tiene cuentas asociadas." << std::endl;
        return;
    }

    while (true) {

        try {
            std::cout << "Ingrese el ID de la cuenta a eliminar (máximo 10 digitos): ";
            std::string input;
            std::getline(std::cin, input);

            // Verificar tipo de dato (debe ser un entero)
            std::stringstream ss(input);
            int temp;
            if (!(ss >> temp) || !ss.eof()) {
                throw std::invalid_argument("El ID de la cuenta debe ser número entero.");
            }

            // Verificar tamaño de dato
            if (input.length() > 10) {
                throw std::out_of_range("El ID de la cuenta excede la longitud máxima permitida.");
            }

            idCuenta = temp; // Asignar el valor convertido a int a idCliente

            break; // Si todo está bien, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }


    // Verificar si la cuenta que se desea eliminar existe
    std::string consultaC = "SELECT id_account FROM BankAccount WHERE id_client = " + std::to_string(idCliente) + " AND id_account = " + std::to_string(idCuenta);
    std::string resultadoC = dbManager.ejecutarConsulta(consultaC);

    // Obtener la moneda de la cuenta
    std::string consultaCurrency = "SELECT currency FROM BankAccount WHERE id_client = " + std::to_string(idCliente) + " AND id_account = " + std::to_string(idCuenta);
    std::string columnaCurrency = "currency";
    std::string resultadoCurrency = dbManager.ejecutarConsulta(consultaCurrency);

    if (resultadoC.empty()) {
        std::cerr << "La cuenta con ID " << idCuenta << " no existe para el cliente con ID " << idCliente << "." << std::endl;
        return;
    }

    // Eliminar la cuenta seleccionada
    std::string comandoSQL = "DELETE FROM BankAccount WHERE id_client = " + std::to_string(idCliente) + " AND id_account = " + std::to_string(idCuenta);
    dbManager.ejecutarSQL(comandoSQL);
    std::cout << "Se ha eliminado correctamente la cuenta con ID " << idCuenta << " del cliente con ID " << idCliente << "." << std::endl;

    std::string campoActualizar = "";
    if (resultadoCurrency == "CRC") {
        campoActualizar = "id_colones_account = NULL";
    } else if (resultadoCurrency == "USD") {
        campoActualizar = "id_dólares_account = NULL";
    }

    std::string actualizarCliente = "UPDATE Client SET " + campoActualizar + " WHERE id_client = " + std::to_string(idCliente);
    dbManager.ejecutarSQL(actualizarCliente);
    std::cout << "Se ha eliminado correctamente la cuenta con ID " << idCuenta << " del cliente con ID " << idCliente << "." << std::endl;

}

