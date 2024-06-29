#ifndef CUENTA_HPP       // Evalúa si la variable está definida
#define CUENTA_HPP       // Define una variable si no la hay

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
    std::string fechaApertura;
   

public:

    // Constructor por defecto
    Cuenta();

    // Constructor para inicializar una cuenta
    Cuenta(int idCliente, int idCuenta, const std::string& moneda, double saldo, const std::string& fechaApertura);

    // Método para obtener información detallada de la cuenta
    void obtenerInformacion(DBManager& dbManager);

    // Método para eliminar cuenta
    void eliminarCuenta(DBManager& dbManager);
};

#endif // CUENTA_HPP