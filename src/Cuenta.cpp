#include "Cuenta.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

template<typename T>
Cuenta<T>::Cuenta(int idCuenta, const std::string& tipoCuenta, const std::string& moneda, double saldo, 
               const std::string& estado, const std::tm& fechaApertura) {
    detallesCuenta["ID Cuenta"] = idCuenta;
    detallesCuenta["Tipo de Cuenta"] = tipoCuenta;
    detallesCuenta["Moneda"] = moneda;
    detallesCuenta["Saldo"] = saldo;
    detallesCuenta["Estado"] = estado;

    std::ostringstream oss;
    oss << std::put_time(&fechaApertura, "%d/%m/%Y");
    detallesCuenta["Fecha de Apertura"] = oss.str();
}

template<typename T>
void Cuenta<T>::obtenerInformacion() {
    int idCuenta;
    double saldo;
    std::string tipoCuenta, moneda, estado;
    int dia, mes, anio;

    std::cout << "Ingrese el ID de la cuenta: ";
    std::cin >> idCuenta;
    std::cout << "Ingrese el tipo de cuenta: ";
    std::cin >> tipoCuenta;
    std::cout << "Ingrese la moneda: ";
    std::cin >> moneda;
    std::cout << "Ingrese el saldo: ";
    std::cin >> saldo;
    std::cout << "Ingrese el estado de la cuenta: ";
    std::cin >> estado;

    std::cout << "Ingrese la fecha de apertura (dia mes anio): ";
    std::cin >> dia >> mes >> anio;

    // Ajustar el mes para que enero sea 1 y diciembre sea 12
    if (mes < 1 || mes > 12) {
        std::cerr << "El mes ingresado es inválido." << std::endl;
        return;
    }

    std::tm fechaApertura = {};
    fechaApertura.tm_mday = dia;
    fechaApertura.tm_mon = mes - 1; // Ajuste para que enero sea 1
    fechaApertura.tm_year = anio - 1900;

    // Actualizar los detalles de la cuenta con los valores proporcionados
    detallesCuenta["ID Cuenta"] = idCuenta;
    detallesCuenta["Tipo de Cuenta"] = tipoCuenta;
    detallesCuenta["Moneda"] = moneda;
    detallesCuenta["Saldo"] = saldo;
    detallesCuenta["Estado"] = estado;

    std::ostringstream oss;
    oss << std::put_time(&fechaApertura, "%d/%m/%Y");
    detallesCuenta["Fecha de Apertura"] = oss.str();
}

template<typename T>
void Cuenta<T>::actualizarDatos() {
    std::unordered_map<std::string, T> nuevosDatos;

    T nuevoIdCuenta, nuevoSaldo;
    std::string nuevoTipoCuenta, nuevaMoneda, nuevoEstado;
    int nuevoDia, nuevoMes, nuevoAnio;

    std::cout << "Ingrese el nuevo ID de la cuenta: ";
    std::cin >> nuevoIdCuenta;
    std::cout << "Ingrese el nuevo tipo de cuenta: ";
    std::cin >> nuevoTipoCuenta;
    std::cout << "Ingrese la nueva moneda: ";
    std::cin >> nuevaMoneda;
    std::cout << "Ingrese el nuevo saldo: ";
    std::cin >> nuevoSaldo;
    std::cout << "Ingrese el nuevo estado de la cuenta: ";
    std::cin >> nuevoEstado;
    std::cout << "Ingrese la nueva fecha de apertura (dia mes anio): ";
    std::cin >> nuevoDia >> nuevoMes >> nuevoAnio;

    // Actualizar el diccionario con los nuevos datos
    nuevosDatos["ID Cuenta"] = nuevoIdCuenta;
    nuevosDatos["Tipo de Cuenta"] = nuevoTipoCuenta;
    nuevosDatos["Moneda"] = nuevaMoneda;
    nuevosDatos["Saldo"] = nuevoSaldo;
    nuevosDatos["Estado"] = nuevoEstado;

    for (const auto& par : nuevosDatos) {
        detallesCuenta[par.first] = par.second;
    }
}

