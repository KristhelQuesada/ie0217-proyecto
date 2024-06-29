#include "Retiro.hpp"
#include "DBManager.hpp"
#include <iostream>
#include <string>
#include <limits>

Retiro::Retiro(int id_client, DBManager& db) : Transaccion(id_client, db) {}

void Retiro::ejecutar() {
    double monto;
    std::string moneda;
    std::string cuentaOrigen;

    // Solicitar y validar el monto
    while (true) {
        std::cout << "Ingrese el monto a retirar: ";
        std::cin >> monto;
        if (std::cin.fail() || monto <= 0) {
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer
            std::cout << "Monto inválido. Inténtelo de nuevo.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer
            break;
        }
    }

    // Solicitar y validar la moneda
    std::cout << "Ingrese la moneda: ";
    std::getline(std::cin, moneda);
    if (moneda.empty()) {
        std::cout << "Moneda inválida. Inténtelo de nuevo.\n";
        return;
    }

    // Solicitar y validar el número de cuenta de origen
    std::cout << "Ingrese el número de cuenta de origen: ";
    std::getline(std::cin, cuentaOrigen);
    if (cuentaOrigen.empty()) {
        std::cout << "Número de cuenta inválido. Inténtelo de nuevo.\n";
        return;
    }

    std::string consulta = "SELECT balance, tipoCuenta FROM Cuentas WHERE origin_account = '" + cuentaOrigen + "'";
    auto datos = db.ejecutarConsultaRetiroDeposito(consulta);

    if (datos.empty()) {
        std::cout << "Cuenta no encontrada.\n";
        return;
    }

    double balanceAnterior;
    try {
        balanceAnterior = std::stod(datos["balance"]);
    } catch (const std::invalid_argument& e) {
        std::cout << "Error al convertir el balance de la cuenta.\n";
        return;
    } catch (const std::out_of_range& e) {
        std::cout << "Balance de la cuenta fuera de rango.\n";
        return;
    }
    std::string tipoCuenta = datos["tipoCuenta"];

    std::cout << "Realizando retiro de " << monto << " " << moneda
              << " de la cuenta " << cuentaOrigen << ". Balance anterior: " << balanceAnterior
              << ".\n";

    // Conversión de moneda si es necesario
    if (moneda != tipoCuenta) {
        double tipoDeCambio = db.obtenerTipoDeCambio(moneda, tipoCuenta);
        monto *= tipoDeCambio;
        std::cout << "Monto convertido a " << tipoCuenta << ": " << monto << std::endl;
    }

    // Verificar que el monto a retirar no exceda el balance de la cuenta
    if (monto > balanceAnterior) {
        std::cout << "No se puede retirar más de lo que hay en la cuenta.\n";
        return;
    }

    double balancePosterior = balanceAnterior - monto;
    std::cout << "Balance posterior al retiro: " << balancePosterior << std::endl;

    // Actualizar el balance en la base de datos
    std::string comandoSQL = "UPDATE Cuentas SET balance = " + std::to_string(balancePosterior) +
                             " WHERE target_account = '" + cuentaOrigen + "'";
    db.ejecutarSQL(comandoSQL);

    // Registrar la transacción
    std::string registrarTransaccion = "INSERT INTO Transacciones (tipo, cuenta, monto, fecha) VALUES ('retiro', '" +
                                       cuentaOrigen + "', " + std::to_string(monto) + ", NOW())";
    db.ejecutarSQL(registrarTransaccion);

    std::cout << "Retiro realizado y base de datos actualizada correctamente." << std::endl;
}