#include "Deposito.hpp"
#include "DBManager.hpp"
#include <iostream>
#include <string>
#include <limits>

Deposito::Deposito(int id_client, DBManager& db) : Transaccion(id_client, db) {}

void Deposito::ejecutar() {
    double monto;
    std::string moneda;
    int cuentaDestino;
    std::string beginTransactionSQL = "START TRANSACTION; ";
    std::string endTransactionSQL   = "COMMIT; ";


    // Solicitar y validar el monto
    while (true) {
        std::cout << "Ingrese el monto a depositar: ";
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

    // Solicitar y validar el número de cuenta destino
    while (true) {
        std::cout << "Ingrese el número de cuenta destino: ";
        std::cin >> cuentaDestino;
        if (std::cin.fail() || cuentaDestino <= 0) {
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer
            std::cout << "Número de cuenta inválido. Inténtelo de nuevo.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer
            break;
        }
    }

    std::string consulta = "SELECT balance, tipoCuenta FROM Cuentas WHERE origin_account = " + std::to_string(cuentaDestino);
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

    // Convertir el monto si las monedas son diferentes
    if (moneda != tipoCuenta) {
        double tipoDeCambio = db.obtenerTipoDeCambio(moneda, tipoCuenta);
        monto = monto * tipoDeCambio;
        std::cout << "Monto convertido a " << tipoCuenta << ": " << monto << std::endl;
    }

    double balancePosterior = balanceAnterior + monto;

    std::cout << "Realizando depósito de " << monto << " " << tipoCuenta
              << " en la cuenta " << cuentaDestino << ". Balance anterior: " << balanceAnterior
              << ", Balance posterior: " << balancePosterior << std::endl;

    db.ejecutarSQL(beginTransactionSQL);
    //db.ejecutarSQL(endTransactionSQL);
 
    // Actualizar el balance en la base de datos
    std::string comandoSQL = "UPDATE Cuentas SET balance = " + std::to_string(balancePosterior) +
                             " WHERE target_account = " + std::to_string(cuentaDestino);
    db.ejecutarSQL(comandoSQL);

    // Registrar la transacción
    std::string registrarTransaccion = "INSERT INTO Transacciones (tipo, cuenta, monto, fecha) VALUES ('deposito', '" +
                                       std::to_string(cuentaDestino) + "', " + std::to_string(monto) + ", NOW())";
    db.ejecutarSQL(registrarTransaccion);

    db.ejecutarSQL(endTransactionSQL);

    std::cout << "Depósito realizado y base de datos actualizada correctamente." << std::endl;
}