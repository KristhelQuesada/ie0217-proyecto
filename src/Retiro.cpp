#include "Retiro.hpp"
#include "DBManager.hpp"
#include <iostream>
#include <string>
#include <limits>

Retiro::Retiro(int id_client, DBManager& db) : Transaccion(id_client, db) {}

void Retiro::ejecutar() {
    double monto;
    std::string moneda;
    int cuentaOrigen;
    std::string detalles;
    std::string beginTransactionSQL = "START TRANSACTION; ";
    std::string endTransactionSQL   = "COMMIT; ";

    // Solicitar y validar el número de cuenta de origen
    while (true) {
        std::cout << "Ingrese el número de cuenta del cliente: ";
        std::cin >> cuentaOrigen;
        if (std::cin.fail() || cuentaOrigen <= 0) {
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(); // Limpiar el buffer
            std::cout << "Número de cuenta inválido. Inténtelo de nuevo.\n";
        } else {
            std::cin.ignore(); // Limpiar el buffer
            break;
        }
    }

    // Solicitar y validar la moneda
    while (true) {
        std::cout << "Ingrese la moneda (CRC o USD): ";
        std::getline(std::cin, moneda);
        if (moneda != "CRC" && moneda != "USD") {
            std::cout << "Moneda inválida. Inténtelo de nuevo.\n";
        } else {
            break;
        }
    }

    // Solicitar y validar el monto
    while (true) {
        std::cout << "Ingrese el monto a retirar: ";
        std::cin >> monto;
        if (std::cin.fail() || monto <= 0) {
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(); // Limpiar el buffer
            std::cout << "Monto inválido. Inténtelo de nuevo.\n";
        } else {
            std::cin.ignore(); // Limpiar el buffer
            break;
        }
    }

    // Solicitar detalles de la transacción
    std::cout << "Ingrese detalles de la transacción (opcional): ";
    std::getline(std::cin, detalles);
    std::string consulta = "SELECT balance, currency FROM BankAccount WHERE id_account = " + std::to_string(cuentaOrigen);
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
    std::string tipoCuenta = datos["currency"];

    // Conversión de moneda si es necesario
    if (moneda != tipoCuenta) {
        double tipoDeCambio = db.obtenerTipoDeCambio(moneda, tipoCuenta);
        monto *= tipoDeCambio;
        std::cout << "Monto convertido a " << tipoCuenta << ": " << monto << std::endl;
    } else {
        std::cout << "Monto en " << tipoCuenta << ": " << monto << std::endl;
    }

    // Verificar que el monto a retirar no exceda el balance de la cuenta
    if (monto > balanceAnterior) {
        std::cout << "No se puede retirar más de lo que hay en la cuenta.\n";
        return;
    }

    double balancePosterior = balanceAnterior - monto;
    std::cout << "Realizando retiro de " << monto << " " << tipoCuenta
              << " de la cuenta " << cuentaOrigen << ". Balance anterior: " << balanceAnterior
              << ", Balance posterior: " << balancePosterior << std::endl;

    db.ejecutarSQL(beginTransactionSQL);

    // Actualizar el balance en la base de datos
    std::string comandoSQL = "UPDATE BankAccount SET balance = " + std::to_string(balancePosterior) +
                             " WHERE id_account = " + std::to_string(cuentaOrigen) + ";";
    db.ejecutarSQL(comandoSQL);

    // Registrar la transacción
    std::string registrarTransaccion = "INSERT INTO Transaction (transaction_type, currency, "
                                       "transaction_amount, origin_account, target_account, detail, "
                                       "previous_qty, present_qty) VALUES ('RT', '" + tipoCuenta + "', "
                                       + std::to_string(monto) + ", " + std::to_string(cuentaOrigen) + ", " 
                                       + std::to_string(cuentaOrigen) + ", '" + detalles + "', " 
                                       + std::to_string(balanceAnterior) + ", "
                                       + std::to_string(balancePosterior) + ")";
    db.ejecutarSQL(registrarTransaccion);

    db.ejecutarSQL(endTransactionSQL);

    std::cout << "Retiro realizado y base de datos actualizada correctamente." << std::endl;
}
