#include <iostream>      // Directiva que proporciona funcionalidades para la entrada y salida en consola 
#include <iomanip>       // Directiva que permite manipular la entrada y salida de datos
#include <sstream>       // Directiva que facilita trabajar con cadenas de flujo 
#include <ctime>         // Directiva que permite trabajar con funciones y estructuras relacionadas con el tiempo 
#include <algorithm>     // Directiva que proporciona algoritmos estándar 
#include <stdexcept>     // Directiva que incluye clases para el manejo de excepciones estándar 
#include <unordered_map> // Directiva que ofrece el contenedor hash map
#include <stdexcept>     // Directiva para manejar excepciones estándar

#include "Cuenta.hpp"           // Incluye un archivo

// Constructor de la clase cuenta que incializa sus atributo
Cuenta::Cuenta(int idCliente, int idCuenta, const std::string& moneda, double saldo, const std::tm& fechaApertura) {
    this->idCliente = idCliente;
    this->idCuenta = idCuenta;
    this->moneda = moneda;
    this->saldo = saldo;
    this->fechaApertura = fechaApertura;
}

// Métodos para obtener y establecer el ID del cliente
int Cuenta::getIdCliente() const {
    return idCliente;
}

void Cuenta::setIdCliente(int idCliente) {
    this->idCliente = idCliente;
}

// Métodos para obtener y establecer el ID de la cuenta
int Cuenta::getIdCuenta() const {
    return idCuenta;
}

void Cuenta::setIdCuenta(int idCuenta) {
    this->idCuenta = idCuenta;
}

// Métodos para obtener y establecer la moneda de la cuenta bancaria
const std::string& Cuenta::getMoneda() const {
    return moneda;
}

void Cuenta::setMoneda(const std::string& moneda) {
    this->moneda = moneda;
}

// Métodos para obtener y establecer el saldo de la cuenta bancaria
double Cuenta::getSaldo() const {
    return saldo;
}

void Cuenta::setSaldo(double saldo) {
    this->saldo = saldo;
}

// Métodos para obtener y establecer la fecha de apertura de la cuenta bancaria
const std::tm& Cuenta::getFechaApertura() const {
    return fechaApertura;
}

void Cuenta::setFechaApertura(const std::tm& fechaApertura) {
    this->fechaApertura = fechaApertura;
}

// Método para obtener la información de la cuenta bancaria
void Cuenta::obtenerInformacion() {
    std::cout << "Ingrese el ID del cliente: ";
    std::cin >> idCliente;
    setIdCliente(idCliente);

    std::cout << "Ingrese el ID de la cuenta: ";
    std::cin >> idCuenta;
    setIdCuenta(idCuenta);

    std::cout << "Ingrese la moneda de la cuenta: ";
    std::cin >> moneda;
    setMoneda(moneda);

    std::cout << "Ingrese el saldo de la cuenta: ";
    std::cin >> saldo;
    setSaldo(saldo);

    obtenerFechaApertura(); // Llama a la función para obtener la fecha de apertura
    
}

// Método para obtener la fecha de apertura de la cuenta bancaria
void Cuenta::obtenerFechaApertura() {
    std::string fechaStr;
    std::cout << "Ingrese la fecha de apertura (formato día/mes/año, por ejemplo 12/06/2024): ";
    std::cin >> fechaStr;

    // Parsear la fechaStr para obtener día, mes y año
    int day, month, year;
    char delimiter;
    std::istringstream iss(fechaStr);
    iss >> day >> delimiter >> month >> delimiter >> year;

    // Validar que el mes esté en el rango correcto (1-12)
    if (month < 1 || month > 12) {
        std::cerr << "Error: Mes fuera de rango válido (1-12)." << std::endl;
        // Manejar el error según tu aplicación
        // Aquí puedes lanzar una excepción, devolver un valor especial o realizar alguna otra acción
        return;
    }

    // Configurar la fecha de apertura en std::tm
    fechaApertura.tm_mday = day;
    fechaApertura.tm_mon = month - 1; // Ajuste necesario para std::tm
    fechaApertura.tm_year = year - 1900; // std::tm cuenta los años desde 1900
    fechaApertura.tm_hour = 0; // Establecer horas, minutos y segundos a 0 si no se necesitan
    fechaApertura.tm_min = 0;
    fechaApertura.tm_sec = 0;

    // Opcional: Validar la entrada de fecha y manejar errores
}

// Método para insertar los datos d ela cuenta bancaria a la base de datos
bool Cuenta::insertarDetallesCuentaBaseDatos(DBManager& dbManager) {
    // Construir la fecha en formato YYYY-MM-DD para la consulta SQL
    std::ostringstream oss;
    oss << std::put_time(&fechaApertura, "%Y-%m-%d");
    std::string fechaAperturaStr = oss.str();

    // Construir la consulta SQL
    std::string query = "INSERT INTO Cuenta (id_account, id_client, currency, balance, opening_date) VALUES (";
    query += std::to_string(idCuenta) + ", ";
    query += std::to_string(idCliente) + ", ";
    query += "'" + moneda + "', ";
    query += std::to_string(saldo) + ", ";
    query += "'" + fechaAperturaStr + "')";

    // Ejecutar la consulta SQL
    dbManager.ejecutarSQL(query);

    return true;
}

// Método para actualizar los datos de una cuenta bancaria
void Cuenta::actualizarDatos(DBManager& dbManager) {
    int idCliente;
    std::string moneda;
    int nuevoIdCuenta;
    double nuevoSaldo;
    std::string nuevaMoneda;
    std::tm nuevaFechaApertura;

    // Solicitar al usuario que ingrese el ID del cliente a actualizar
    std::cout << "Ingrese el ID del cliente a actualizar: ";
    std::cin >> idCliente;

    // Solicitar al usuario que ingrese la moneda en la que se encuentra la cuenta bancaria registrada
    std::cout << "Ingrese la moneda en la que se encuentra la cuenta bancaria registrada: ";
    std::cin >> moneda;

    // Consultar y mostrar los datos actuales del cliente asociado al ID antes de la actualización
    std::cout << "Datos actuales del cliente con ID " << idCliente << " y moneda " << moneda << " antes de la actualización:" << std::endl;
    std::string consultaAntes = "SELECT id_account, id_client, currency, balance, opening_date FROM BankAccount WHERE id_client = " + std::to_string(idCliente) + " AND currency = '" + moneda + "'";
    std::string resultadoConsultaAntes = dbManager.ejecutarConsulta(consultaAntes);
    std::cout << resultadoConsultaAntes << std::endl;  // Imprimir el resultado de la consulta antes de la actualización

    // Solicitar al usuario que ingrese los nuevos datos para la cuenta
    std::cout << "Ingrese el nuevo ID de cuenta: ";
    std::cin >> nuevoIdCuenta;
    setIdCuenta(nuevoIdCuenta); // Utilizar el método set para establecer el nuevo ID de cuenta

    std::cout << "Ingrese el nuevo saldo: ";
    std::cin >> nuevoSaldo;
    setSaldo(nuevoSaldo); // Utilizar el método set para establecer el nuevo saldo

    std::cout << "Ingrese la nueva moneda: ";
    std::cin >> nuevaMoneda;
    setMoneda(nuevaMoneda); // Utilizar el método set para establecer la nueva moneda

    obtenerFechaApertura(); // Solicitar al usuario la nueva fecha de apertura

    // Construir la fecha en formato YYYY-MM-DD para la consulta SQL
    std::ostringstream oss;
    oss << std::put_time(&fechaApertura, "%Y-%m-%d");
    std::string fechaAperturaStr = oss.str();

    // Construir la consulta SQL para actualizar los datos en la base de datos
    std::string query = "UPDATE BankAccount SET ";
    query += "id_account = " + std::to_string(getIdCuenta()) + ", ";
    query += "currency = '" + getMoneda() + "', ";
    query += "balance = " + std::to_string(getSaldo()) + ", ";
    query += "opening_date = '" + fechaAperturaStr + "' ";
    query += "WHERE id_client = " + std::to_string(idCliente) + " AND currency = '" + moneda + "'";

    // Ejecutar la consulta SQL para actualizar los datos
    dbManager.ejecutarSQL(query);

    std::cout << "Los datos de la cuenta para el cliente con ID " << idCliente << " y moneda " << moneda << " han sido actualizados." << std::endl;
}
