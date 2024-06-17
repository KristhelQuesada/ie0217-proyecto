#include "Retiro.hpp"
#include "DBManager.hpp"
#include <iostream>
#include <string>

Retiro::Retiro(int id_client, DBManager& db) : Transaccion(id_client, db) {}


void Retiro::ejecutar() {
    double monto;
    std::string moneda;
    std::string cuentaOrigen;
    std::cout << "Ingrese el monto a retirar: ";
    std::cin >> monto;
    std::cin.ignore();
    std::cout << "Ingrese la moneda: ";
    std::getline(std::cin, moneda);
    std::cout << "Ingrese el número de cuenta de origen: ";
    std::getline(std::cin, cuentaOrigen);

    DBManager dbManager("tu_cadena_de_conexion");
    std::string consulta = "SELECT balance, tipoCuenta FROM Cuentas WHERE numero_de_cuenta = '" + cuentaOrigen + "'";
    auto datos = dbManager.ejecutarConsultaRetiroDeposito(consulta);

    if (datos.empty()) {
        std::cout << "Cuenta no encontrada.\n";
        return;
    }

    double balanceAnterior = std::stod(datos["balance"]);
    std::string tipoCuenta = datos["tipoCuenta"];

    std::cout << "Realizando retiro de " << monto << " " << moneda
              << " de la cuenta " << cuentaOrigen << ". Balance anterior: " << balanceAnterior
              << ".\n";

    // Conversión de moneda si es necesario
    if (moneda != tipoCuenta) {
        double tipoDeCambio = dbManager.obtenerTipoDeCambio(moneda, tipoCuenta);
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
                             " WHERE numero_de_cuenta = '" + cuentaOrigen + "'";
    dbManager.ejecutarSQL(comandoSQL);

    // Registrar la transacción
    std::string registrarTransaccion = "INSERT INTO Transacciones (tipo, cuenta, monto, fecha) VALUES ('retiro', '" +
                                       cuentaOrigen + "', " + std::to_string(monto) + ", NOW())";
    dbManager.ejecutarSQL(registrarTransaccion);

    std::cout << "Retiro realizado y base de datos actualizada correctamente." << std::endl;
}
