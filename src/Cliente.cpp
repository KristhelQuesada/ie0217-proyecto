#include "Cliente.hpp"

template<typename T>
Cliente<T>::Cliente(int idCliente, const std::string& nombre, const std::string& apellido) {
    informacion["idCliente"] = idCliente;
    informacion["nombreCliente"] = nombre;
    informacion["apellidoCliente"] = apellido;
}

template<typename T>
void Cliente<T>::obtenerInformacion() {
    T idCliente;
    std::string nombre, apellido;

    std::cout << "Ingrese el ID del cliente: ";
    std::cin >> idCliente;
    std::cout << "Ingrese el nombre del cliente: ";
    std::cin >> nombre;
    std::cout << "Ingrese el apellido del cliente: ";
    std::cin >> apellido;

    // Inicializar los atributos del cliente con los valores proporcionados
    informacion["idCliente"] = idCliente;
    informacion["nombreCliente"] = nombre;
    informacion["apellidoCliente"] = apellido;
}

template<typename T>
void Cliente<T>::actualizarDatos() {
    std::unordered_map<std::string, T> nuevosDatos;

    T nuevoIdCliente;
    std::string nuevoNombre, nuevoApellido;

    std::cout << "Ingrese el nuevo ID del cliente: ";
    std::cin >> nuevoIdCliente;
    std::cout << "Ingrese el nuevo nombre del cliente: ";
    std::cin >> nuevoNombre;
    std::cout << "Ingrese el nuevo apellido del cliente: ";
    std::cin >> nuevoApellido;

    // Actualizar el diccionario con los nuevos datos
    informacion["idCliente"] = nuevoIdCliente;
    informacion["nombreCliente"] = nuevoNombre;
    informacion["apellidoCliente"] = nuevoApellido;
}

// Instanciaciones de las plantillas utilizadas
template class Cliente<int>;
