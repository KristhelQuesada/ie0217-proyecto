#include "Deposito.hpp"
#include "DBManager.hpp"
#include <iostream>
#include <string>

Deposito::Deposito(int id_client, DBManager& db) : Transaccion(id_client, db) {}

void Deposito::ejecutar() {
    double monto;
    std::string moneda;
    int cuentaDestino;
    std::cout << "Ingrese el monto a depositar: ";
    std::cin >> monto;
    std::cin.ignore();  // Limpiar el buffer
    std::cout << "Ingrese la moneda: ";
    std::getline(std::cin, moneda);
    std::cout << "Ingrese el número de cuenta destino: ";
    std::cin >> cuentaDestino;

    DBManager dbManager("tu_cadena_de_conexion");
    std::string consulta = "SELECT balance, tipoCuenta FROM Cuentas WHERE numero_de_cuenta = " + std::to_string(cuentaDestino);
    auto datos = dbManager.ejecutarConsultaRetiroDeposito(consulta);

    if (datos.empty()) {
        std::cout << "Cuenta no encontrada.\n";
        return;
    }

    double balanceAnterior = std::stod(datos["balance"]);
    std::string tipoCuenta = datos["tipoCuenta"];

    // Convertir el monto si las monedas son diferentes
    if (moneda != tipoCuenta) {
        double tipoDeCambio = dbManager.obtenerTipoDeCambio(moneda, tipoCuenta);
        monto = monto * tipoDeCambio;
        std::cout << "Monto convertido a " << tipoCuenta << ": " << monto << std::endl;
    }

    double balancePosterior = balanceAnterior + monto;

    std::cout << "Realizando depósito de " << monto << " " << tipoCuenta
              << " en la cuenta " << cuentaDestino << ". Balance anterior: " << balanceAnterior
              << ", Balance posterior: " << balancePosterior << std::endl;

    // Actualizar el balance en la base de datos
    std::string comandoSQL = "UPDATE Cuentas SET balance = " + std::to_string(balancePosterior) +
                             " WHERE numero_de_cuenta = " + std::to_string(cuentaDestino);
    dbManager.ejecutarSQL(comandoSQL);

    // Registrar la transacción
    std::string registrarTransaccion = "INSERT INTO Transacciones (tipo, cuenta, monto, fecha) VALUES ('deposito', '" +
                                       std::to_string(cuentaDestino) + "', " + std::to_string(monto) + ", NOW())";
    dbManager.ejecutarSQL(registrarTransaccion);

    std::cout << "Depósito realizado y base de datos actualizada correctamente." << std::endl;
}