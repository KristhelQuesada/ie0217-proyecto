#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <map>

#include "Cliente.hpp"


template<typename T>
Cliente<T>::Cliente(int idCliente, const std::string& nombre, const std::string& apellido, int idCuentaColones, int idCuentaDolares) {
    informacion["idCliente"] = idCliente;
    informacion["nombreCliente"] = nombre;
    informacion["apellidoCliente"] = apellido;
    informacion["idCuentaColonesCliente"] = idCuentaColones;
    informacion["idCuentaDolaresCliente"] = idCuentaColones;
}

// Métodos para obtener y establecer el ID del cliente
template<typename T>
T Cliente<T>::getIdCliente() const {
    return informacion.at("idCliente");
}

template<typename T>
void Cliente<T>::setIdCliente(T idCliente) {
    // Validar tipo de dato
    if (typeid(idCliente) != typeid(T)) {
        throw std::invalid_argument("El ID de cliente debe ser un dato tipo entero");
    }

    // Validar rango (ejemplo de rango)
    if (idCliente < 0 || idCliente > 999999999) {
        throw std::out_of_range("ID de cliente fuera del rango permitido (0, 999999999)");
    }

    informacion["idCliente"] = idCliente;
}

// Métodos para obtener y establecer el nombre del cliente
template<typename T>
const std::string& Cliente<T>::getNombreCliente() const {
    return informacion.at("nombreCliente");
}

template<typename T>
void Cliente<T>::setNombreCliente(const std::string& nombre) {
    // Validar longitud (ejemplo de longitud)
    if (nombre.length() > 50) {
        throw std::length_error("El nombre digitado excede la longitud maxima permitida (50 carcateres)");
    }

    // Validar tipo de dato (asegurarse que T sea compatible con std::string)
    if (typeid(T) != typeid(std::string)) {
        throw std::invalid_argument("El nombre del cliente debe ser una cadena de texto)");
    }

    informacion["nombreCliente"] = nombre;
}

// Métodos para obtener y establecer el apellido del cliente
template<typename T>
const std::string& Cliente<T>::getApellidoCliente() const {
    return informacion.at("apellidoCliente");
}

template<typename T>
void Cliente<T>::setApellidoCliente(const std::string& apellido) {
    // Validar tipo de dato (asegurarse que T sea compatible con std::string)
    if (typeid(T) != typeid(std::string)) {
        throw std::invalid_argument("El apellido del cliente debe ser una cadena de texto)");
    }

    // Validar longitud (ejemplo de longitud)
    if (apellido.length() > 50) {
        throw std::length_error("El apellido digitado excede la longitud maxima permitida (50 caracteres)");
    }

    informacion["apellidoCliente"] = apellido;
}

// Métodos para obtener y establecer el ID de la cuenta bancaria en colones
template<typename T>
T Cliente<T>::getIdCuentaColones() const {
    return informacion.at("idCuentaColonesCliente");
}

template<typename T>
void Cliente<T>::setIdCuentaColones(T idCuentaColones) {
    // Validar tipo de dato
    if (typeid(idCuentaColones) != typeid(T)) {
        throw std::invalid_argument("El ID de la cuenta en colones debe ser un dato tipo entero");
    }

    // Validar rango (ejemplo de rango)
    if (idCuentaColones < 0 || idCuentaColones > 9999999999) {
        throw std::out_of_range("ID de cuenta de colones fuera del rango permitido (0, 9999999999)");
    }

    informacion["idCuentaColonesCliente"] = idCuentaColones;
}

// Método para obtener y establecer el ID de la cuenta bancaria en dólares
template<typename T>
T Cliente<T>::getIdCuentaDolares() const {
    return informacion.at("idCuentaDolaresCliente");
}

template<typename T>
void Cliente<T>::setIdCuentaDolares(T idCuentaDolares) {
    // Validar tipo de dato
    if (typeid(idCuentaDolares) != typeid(T)) {
        throw std::invalid_argument("El ID de cuenta de dolares debe ser un dato tipo entero");
    }

    // Validar rango (ejemplo de rango)
    if (idCuentaDolares < 0 || idCuentaDolares > 9999999999) {
        throw std::out_of_range("ID de cuenta de dólares fuera del rango permitido");
    }

    informacion["idCuentaDolaresCliente"] = idCuentaDolares;
}

template<typename T>
std::map<std::string, T> Cliente<T>::getInformacion() const {
  return informacion;
}

template<typename T>
void Cliente<T>::obtenerInformacion() {
    T idCliente;
    std::string nombre, apellido;
    bool success = false;

    // Bucle para obtener ID del cliente
    while (!success) {
        try {
            std::cout << "Ingrese el ID del cliente: ";
            std::cin >> idCliente;
            if (std::cin.fail()) {
                throw std::invalid_argument("El ID del cliente debe ser un número.");
            }
            setIdCliente(idCliente); // Usar el método set para establecer el valor
            success = true;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cin.clear(); // Limpiar el estado de error del cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar el resto de la entrada
        }
    }

    success = false;

    // Bucle para obtener el nombre del cliente
    while (!success) {
        try {
            std::cout << "Ingrese el nombre del cliente: ";
            std::cin >> nombre;
            setNombreCliente(nombre); // Usar el método set para establecer el valor
            success = true;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    success = false;

    // Bucle para obtener el apellido del cliente
    while (!success) {
        try {
            std::cout << "Ingrese el apellido del cliente: ";
            std::cin >> apellido;
            setApellidoCliente(apellido); // Usar el método set para establecer el valor
            success = true;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

template<typename T>
bool Cliente<T>::insertarInformacionBaseDeDatos(DBManager& dbManager) {
    // Asumiendo que los datos ya están en el formato correcto y no necesitan ser escapados ni convertidos
    int idCliente = informacion["idCliente"];
    std::string nombreCliente = informacion["nombreCliente"];
    std::string apellidoCliente = informacion["apellidoCliente"];
    int idCuentaColonesCliente = informacion["idCuentaColonesCliente"];
    int idCuentaDolaresCliente = informacion["idCuentaDolaresCliente"];

    // Construimos la consulta SQL con los nuevos nombres de las columnas
    std::string query = "INSERT INTO Clientes (id_client, client_name, client_lastname, id_colones_account, id_dolares_account) VALUES (";
    query += std::to_string(idCliente) + ", ";
    query += "'" + nombreCliente + "', ";
    query += "'" + apellidoCliente + "', ";
    query += std::to_string(idCuentaColonesCliente) + ", ";
    query += std::to_string(idCuentaDolaresCliente) + ");";

    // Ejecutamos la consulta SQL
    dbManager.ejecutarSQL(query);

    return true;

}


template<typename T>
void Cliente<T>::actualizarDatos(DBManager& dbManager) {
    int idCliente;
    std::string nuevoNombre, nuevoApellido;

    // Solicitar al usuario que ingrese el ID del cliente a actualizar en un bucle para manejar excepciones
    while (true) {
        try {
            std::cout << "Ingrese el ID del cliente a actualizar: ";
            std::cin >> idCliente;
            setIdCliente(idCliente);  // Validar y establecer el ID del cliente

            // Si no se lanzó ninguna excepción, salir del bucle
            break;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\nPor favor, intente de nuevo." << std::endl;
        }
    }

    // Consultar y mostrar los datos actuales del cliente asociado al ID antes de la actualización
    std::cout << "Datos actuales del cliente con ID " << idCliente << " antes de la actualización:" << std::endl;
    std::string consultaAntes = "SELECT id_client, client_name, client_lastname, id_colones_account, id_dolares_account FROM Client WHERE id_client = " + std::to_string(idCliente);
    std::string resultadoConsultaAntes = dbManager.ejecutarConsulta(consultaAntes);
    std::cout << resultadoConsultaAntes << std::endl;  // Imprimir el resultado de la consulta antes de la actualización

    // Solicitar al usuario que ingrese el nuevo nombre y apellido en un bucle para manejar excepciones
    while (true) {
        try {
            std::cout << "Ingrese el nuevo nombre del cliente: ";
            std::cin.ignore();  // Ignorar el salto de línea anterior
            std::getline(std::cin, nuevoNombre);
            setNombreCliente(nuevoNombre);  // Validar y establecer el nuevo nombre

            std::cout << "Ingrese el nuevo apellido del cliente: ";
            std::getline(std::cin, nuevoApellido);
            setApellidoCliente(nuevoApellido);  // Validar y establecer el nuevo apellido

            // Si no se lanzó ninguna excepción, salir del bucle
            break;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\nPor favor, intente de nuevo." << std::endl;
        }
    }


    // Construir la consulta SQL para actualizar nombre y apellido
    std::string actualizarQuery = "UPDATE Clientes SET client_name = '" + nuevoNombre + "', client_lastname = '" + nuevoApellido + "' WHERE id_client = " + std::to_string(idCliente);

    // Ejecutar la consulta para actualizar en la base de datos
    dbManager.ejecutarSQL(actualizarQuery);

    // Mostrar mensaje de éxito
    std::cout << "Nombre y apellido del cliente actualizados correctamente." << std::endl;

    // Consultar y mostrar los datos actualizados del cliente asociado al ID después de la actualización
    std::cout << "Datos actualizados del cliente con ID " << idCliente << ":" << std::endl;
    std::string consultaDespues = "SELECT id_client, client_name, client_lastname, id_colones_account, id_dolares_account FROM Client WHERE id_client = " + std::to_string(idCliente);
    std::string resultadoConsultaDespues = dbManager.ejecutarConsulta(consultaDespues);
    std::cout << resultadoConsultaDespues << std::endl;  // Imprimir el resultado de la consulta después de la actualización
}
