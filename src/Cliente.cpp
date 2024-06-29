#include <iostream>     // Directiva que proporciona funcionalidades para la entrada y salida estándar en consola 
#include <stdexcept>    // Directiva que incluye clases para el manejo de excepciones estándar 
#include <chrono>       // Directiva que permite trabajar con funciones y estructuras relacionadas con el tiempo 
#include <ctime>        // Directiva que permite trabajar con funciones y estructuras relacionadas con el tiempo 
#include <sstream>      // Directiva que facilita trabajar con cadenas de flujo 


#include "Cliente.hpp"  // Incluir el archivo de encabezado de la clase Cliente


// Constructor por defecto
Cliente::Cliente() {

    nombre = "";
    apellido = "";
    idCliente = 0;
    idCuentaColones = 0;
    idCuentaDolares = 0;
    

}



// Inicialización del constructor de la clase cliente
Cliente::Cliente(int idCliente, const std::string& nombre, const std::string& apellido, int idCuentaColones, int idCuentaDolares)
    : idCliente(idCliente), nombre(nombre), apellido(apellido), idCuentaColones(idCuentaColones), idCuentaDolares(idCuentaDolares) {}



// Método que solicita los datos del cliente y los almacena en la base de datos
void Cliente::obtenerInformacion(DBManager dbManager) {

    // Limpiar el buffer de entrada antes de pedir datos
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Obtener ID del cliente
    while (true) {
        try {
            std::cout << "Ingrese el ID del cliente (maximo 9 digitos): ";
            std::string input;
            std::getline(std::cin, input);
        
            // Verificar tipo de dato (debe ser un entero)
            std::stringstream ss(input);
            int temp;
            if (!(ss >> temp) || !ss.eof()) {
                throw std::invalid_argument("El ID del cliente debe ser un dato tipo numero entero.");
            }

            // Verificar tamaño de dato
            if (idCliente < 0 || idCliente > 999999999) {
                throw std::out_of_range("El ID del cliente excede la longitud maxima permitida.");
            }

            idCliente = temp; // Asignar el valor convertido a int a idCliente

            break; // Si todo está bien, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Obtener nombre
    while (true) {
        try {
            std::cout << "Ingrese el nombre del cliente (maximo 50 caracteres): ";
            std::getline(std::cin, nombre);

            // Verificar tipo de dato (debe contener solo letras y espacios)
            for (char c : nombre) {
                if (!isalpha(c) && !isspace(c)) {
                    throw std::invalid_argument("El nombre debe ser un dato tipo texto.");
                }
            }

            // Verificar tamaño de dato
            if (nombre.length() > 50) {
                throw std::out_of_range("El nombre excede la longitud maxima permitida.");
            }

            break; // Si todo está bien, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Obtener apellido
    while (true) {
        try {
            std::cout << "Ingrese el apellido del cliente (maximo 50 caracteres): ";
            std::getline(std::cin, apellido);

            // Verificar tipo de dato (debe contener solo letras y espacios)
            for (char c : apellido) {
                if (!isalpha(c) && !isspace(c)) {
                    throw std::invalid_argument("El apellido debe ser un dato tipo texto.");
                }
            }

            // Verificar tamaño de dato
            if (apellido.length() > 50) {
                throw std::out_of_range("El apellido excede la longitud maxima permitida.");
            }

            break; // Si todo está bien, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Insertar los datos en la base de datos
    std::string comandoSQL = "INSERT INTO Client (id_client, client_name, client_lastname) VALUES (" +
                             std::to_string(idCliente) + ", '" +
                             nombre + "', '" +
                             apellido + "')";

    dbManager.ejecutarSQL(comandoSQL);

    std::cout << std::endl;
    std::cout << "Datos del Cliente:" << std::endl;
    std::cout << "ID cliente: " << idCliente << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Apellido: " << apellido << std::endl;
    std::cout << std::endl;


}




// Funcion que imprime datos de un cliente
void Cliente::imprimirDatos(DBManager dbManager){

    // Limpiar el buffer de entrada antes de pedir datos
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Obtener ID del cliente
    while (true) {
        try {
            std::cout << "Ingrese el ID del cliente (maximo 9 digitos): ";
            std::string input;
            std::getline(std::cin, input);

            // Verificar tipo de dato (debe ser un entero)
            std::stringstream ss(input);
            int temp;
            if (!(ss >> temp) || !ss.eof()) {
                throw std::invalid_argument("El ID del cliente debe ser un dato tipo numero entero.");
            }

            // Verificar tamaño de dato
            if (idCliente < 0 || idCliente > 999999999) {
                throw std::out_of_range("El ID del cliente excede la longitud maxima permitida.");
            }

            idCliente = temp; // Asignar el valor convertido a int a idCliente

            break; // Si todo está bien, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Construir la consulta SQL para obtener cada dato del cliente
    std::string idClientQuery = "SELECT id_client FROM Client WHERE id_client = " + std::to_string(idCliente);
    std::string nameQuery = "SELECT client_name FROM Client WHERE id_client = " + std::to_string(idCliente);
    std::string lastnameQuery = "SELECT client_lastname FROM Client WHERE id_client = " + std::to_string(idCliente);
    std::string colonesQuery = "SELECT id_colones_account FROM Client WHERE id_client = " + std::to_string(idCliente);
    std::string dolaresQuery = "SELECT id_dolares_account FROM Client WHERE id_client = " + std::to_string(idCliente);
    

    // Obtener cada dato del cliente usando el método ejecutarSQL del DBManager

    try {

        idCliente = std::stoi(dbManager.ejecutarConsulta(idClientQuery));
        nombre = dbManager.ejecutarConsulta(nameQuery);
        apellido = dbManager.ejecutarConsulta(lastnameQuery);

        // Manejo de valores NULL para idCuentaColones y idCuentaDolares
        std::string colonesStr = dbManager.ejecutarConsulta(colonesQuery);
        if (!colonesStr.empty()) {
            idCuentaColones = std::stoi(colonesStr);
        } else {
            idCuentaColones = 0;  // Asignar valor por defecto o manejar de otra manera según tu lógica de negocio
        }

        std::string dolaresStr = dbManager.ejecutarConsulta(dolaresQuery);
        if (!dolaresStr.empty()) {
            idCuentaDolares = std::stoi(dolaresStr);
        } else {
            idCuentaDolares = 0;  // Asignar valor por defecto o manejar de otra manera según tu lógica de negocio
        }

    } catch (const std::exception& e) {
        std::cerr << "Error al obtener datos del cliente: " << e.what() << std::endl;
        return;
    }

    std::cout << "Datos del Cliente:" << std::endl;
    std::cout << "ID cliente: " << idCliente << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Apellido: " << apellido << std::endl;
    std::cout << "ID cuenta en colones: " << idCuentaColones << std::endl;
    std::cout << "ID cuenta en dólares: " << idCuentaDolares << std::endl;
    std::cout << std::endl;  // Línea en blanco al final


}



// Función que actualiza datos del cliente
void Cliente::actualizarDatos(DBManager& dbManager) {

    // Limpiar el buffer de entrada antes de pedir datos
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int nuevoIdCliente = 0;  
    std::string nuevoNombre;     
    std::string nuevoApellido;

    

    // Obtener ID del cliente
    while (true) {
        try {
            std::cout << "Ingrese el ID del cliente del que desea actualizar (maximo 9 digitos): ";
            std::string input;
            std::getline(std::cin, input);

            // Verificar tipo de dato (debe ser un entero)
            std::stringstream ss(input);
            int temp;
            if (!(ss >> temp) || !ss.eof()) {
                throw std::invalid_argument("El ID del cliente debe ser un dato tipo numero entero.");
            }

            // Verificar tamaño de dato
            if (idCliente < 0 || idCliente > 999999999) {
                throw std::out_of_range("El ID del cliente excede la longitud maxima permitida.");
            }

            idCliente = temp; // Asignar el valor convertido a int a idCliente

            break; // Si todo está bien, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Verificar si el cliente existe en la base de datos antes de actualizar
    std::string consulta = "SELECT id_client FROM Client WHERE id_client = " + std::to_string(idCliente);
    std::string resultado = dbManager.ejecutarConsulta(consulta);


    if (resultado.empty()) {
        std::cerr << "El cliente con ID " << idCliente << " no esta registrado en la base de datos. No se puede actualizar." << std::endl;
        return; // Salir del método si el cliente no está registrado
    } else {

        // Si está registrado
        std::cerr << std::endl << "Cliente registrado." << std::endl;
        while (true) {
        try {
            std::cout << "Ingrese el nuevo ID del cliente (máximo 9 dígitos): ";
            std::string input;
            std::getline(std::cin, input);

            // Verificar si es un número entero
            std::stringstream ss(input);
            int temp;
            if (!(ss >> temp) || !ss.eof()) {
                throw std::invalid_argument("El ID del cliente debe ser un número entero.");
            }

            // Verificar la longitud del número
            if (nuevoIdCliente < 0 || nuevoIdCliente > 999999999) {
                throw std::out_of_range("El ID del cliente excede la longitud máxima permitida.");
            }

            nuevoIdCliente = temp; // Asignar el valor convertido a int a idCliente

            // Verificar si el clientenuevo ID cliente existe en la base de datos antes de actualizar
            std::string consultaCl = "SELECT id_client FROM Client WHERE id_client = " + std::to_string(nuevoIdCliente);
            std::string resultado = dbManager.ejecutarConsulta(consultaCl);

            if (!resultado.empty()) {
                // Convertir std::string a int y luego comparar
                int id = std::stoi(resultado);

                if (nuevoIdCliente == id) {
                    std::cerr << "El ID del cliente ya está registrado. Por favor, ingrese otro." << std::endl;
                    continue; // Volver a pedir el ID del cliente
                }
            }

            break; // Si todo está bien y el idCliente no está en uso, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

        // Solicitud del nuevo nombre
        while (true) {
        try {
            std::cout << "Ingrese el nuevo nombre del cliente (maximo 50 caracteres): ";
            std::getline(std::cin, nuevoNombre);

            // Verificar tipo de dato (debe contener solo letras y espacios)
            for (char c : nuevoNombre) {
                if (!isalpha(c) && !isspace(c)) {
                    throw std::invalid_argument("El nuevo nombre debe ser un dato tipo texto.");
                }
            }

            // Verificar tamaño de dato
            if (nuevoNombre.length() > 50) {
                throw std::out_of_range("El nuevo nombre excede la longitud maxima permitida.");
            }

            break; // Si todo está bien, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Solicitud del nuevo apellido
    while (true) {
        try {
            std::cout << "Ingrese el nuevo apellido del cliente (maximo 50 caracteres): ";
            std::getline(std::cin, nuevoApellido);

            // Verificar tipo de dato (debe contener solo letras y espacios)
            for (char c : nuevoApellido) {
                if (!isalpha(c) && !isspace(c)) {
                    throw std::invalid_argument("El nuevo apellido debe ser un dato tipo texto.");
                }
            }

            // Verificar tamaño de dato
            if (nuevoApellido.length() > 50) {
                throw std::out_of_range("El nuevo apellido excede la longitud maxima permitida.");
            }

            break; // Si todo está bien, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
        // Actualizar los datos en la base de datos
        std::string comandoSQL = "UPDATE Client SET id_client = '" + std::to_string(nuevoIdCliente) + "', client_name = '" + nuevoNombre + "', client_lastname = '" + nuevoApellido + "' WHERE id_client = " + std::to_string(idCliente);
        dbManager.ejecutarSQL(comandoSQL);
        // Actualizar en cascada en otras tablas relacionadas
        std::string actualizarCascadaSQL = "UPDATE BankAccount SET id_client = '" + std::to_string(nuevoIdCliente) + "' WHERE id_client = " + std::to_string(idCliente);
        dbManager.ejecutarSQL(actualizarCascadaSQL);

        std::cout << "Datos del cliente actualizados correctamente en la base de datos." << std::endl;

        std::cout << std::endl;
        std::cout << "Datos actualizados del Cliente:" << std::endl;
        std::cout << "ID cliente: " << nuevoIdCliente << std::endl;
        std::cout << "Nombre: " << nuevoNombre << std::endl;
        std::cout << "Apellido: " << nuevoApellido << std::endl;
        std::cout << std::endl;
    }


}


// Método para eliminar un cliente por completo en la base de datos
void Cliente::eliminarCliente(DBManager& dbManager) {

    // Limpiar el buffer de entrada antes de pedir datos
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Bucle para obtener ID del cliente
    while (true) {
        try {
            std::cout << "Ingrese el ID del cliente que desea eliminar (máximo 9 digitos): ";
            std::string input;
            std::getline(std::cin, input);

            // Verificar tipo de dato (debe ser un entero)
            std::stringstream ss(input);
            int temp;
            if (!(ss >> temp) || !ss.eof()) {
                throw std::invalid_argument("El ID del cliente debe ser un numero entero.");
            }

            // Verificar tamaño de dato
            if (idCliente < 0 || idCliente > 999999999) {
                throw std::out_of_range("El ID del cliente excede la longitud maxima permitida (9 digitos).");
            }

            idCliente = temp; // Asignar el valor convertido a int a idCliente

            break; // Si todo está bien, salir del bucle

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Consultar si el cliente existe en la base de datos
    std::string consulta = "SELECT id_client FROM Client WHERE id_client = " + std::to_string(idCliente);
    std::string resultado = dbManager.ejecutarConsulta(consulta);

    // Verificar si el resultado está vacío (no existe el cliente)
    if (resultado.empty()) {
        std::cerr << std::endl << "El cliente con ID " << idCliente << " no esta registrado en la base de datos. No se puede eliminar." << std::endl;
        return; // Salir del método si el cliente no está registrado
    }

    // Eliminar al cliente de la base de datos
    std::string comandoSQL = "DELETE FROM Client WHERE id_client = " + std::to_string(idCliente);
    // Eliminación en cascada en otras tablas relacionadas
    std::string eliminarCascadaSQL = "DELETE FROM BankAccount WHERE id_client = " + std::to_string(idCliente);
            
    try {
        dbManager.ejecutarSQL(comandoSQL);
        dbManager.ejecutarSQL(eliminarCascadaSQL);
        std::cout << "Cliente con ID " << idCliente << " eliminado correctamente." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error al intentar eliminar el cliente: " << e.what() << std::endl;
    }

    

}