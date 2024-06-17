#ifndef CUENTA_HPP       // Evalúa si la variable está definida
#define CUENTA_HPP       // Define una variable si no la hay

#include <unordered_map> // Contenedor para almacenar pares clave-valor
#include <vector>        // Contenedor dinámico para almacenar una colección de elementos
#include <string>        // Manejo de cadenas de caracteres
#include <ctime>         // Funciones relacionadas con el tiempo
#include <iostream>      // Mostrar información en consola

#include "DBManager.hpp" // Manejo de la conexión a la base de datos

// Clase que crea un objeto cuenta
class Cuenta {
private:

    // Atributos
    int idCliente;
    int idCuenta;
    double saldo;
    std::string moneda;
    std::tm fechaApertura;

public:
    // Constructor para inicializar una cuenta
    Cuenta(int idCliente, int idCuenta, const std::string& moneda, double saldo, const std::tm& fechaApertura;);

    // Métodos para obtener y establecer el ID del cliente
    int Cuenta::getIdCliente() const;
    void Cuenta::setIdCliente(int idCliente);

    // Métodos para obtener y establecer el ID de la cuenta
    int Cuenta::getIdCuenta() const;
    void Cuenta::setIdCuenta(int idCuenta);

    // Métodos para obtener y establecer la moneda de la cuenta
    const std::string& Cuenta::getMoneda() const;
    void Cuenta::setMoneda(const std::string& moneda);

    // Métodos para obtener y establecer el saldo de la cuenta
    double Cuenta::getSaldo() const;
    void Cuenta::setSaldo(double saldo);

    // Métodos para obtener y establecer la fecha de apertura de la cuenta
    const std::tm& Cuenta::getFechaApertura();
    void Cuenta::setFechaApertura(const std::tm& fechaApertura);

    // Función para insertar datos en la base de datos
    bool Cuenta::insertarDetallesCuentaBaseDatos(DBManager& dbManager);

    // Método para obtener información detallada de la cuenta
    void Cuenta::obtenerInformacion();

    // Método para obtener información detallada de la fecha de apertura
    void Cuenta::obtenerFechaApertura();

    // Método para actualizar datos de la cuenta en la base de datos
    void Cuenta::actualizarDatos(DBManager& dbManager);

    // Método para eliminar datos del cliente
    bool elminarInformacionBaseDeDatos(DBManager& dbManager);
};
