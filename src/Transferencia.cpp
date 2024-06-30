#include "Transferencia.hpp"

#include <iostream>
#include <sstream>      // Directiva que facilita trabajar con cadenas de flujo


Transferencia::Transferencia(int id_client, DBManager& db) : Transaccion(id_client, db) {}

void Transferencia::ejecutar() {

    double monto;
    std::string moneda;
    std::string cuentaOrigen;
    std::string cuentaDestino;
    std::string beginTransactionSQL = "START TRANSACTION; ";
    std::string endTransactionSQL   = "COMMIT; ";


    // Solicitar y validar el número de cuenta de origen
    std::cout << "Ingrese el numero de cuenta de origen: ";
    std::getline(std::cin, cuentaOrigen);
    if (cuentaOrigen.empty()) {
        std::cout << "Numero de cuenta invalido. Intentelo de nuevo.\n";
        return;
    }

    // Solicitar y validar el número de cuenta de destino
    std::cout << "Ingrese el numero de cuenta de destino: ";
    std::getline(std::cin, cuentaDestino);
    if (cuentaDestino.empty()) {
        std::cout << "Numero de cuenta destino invalido. Intentelo de nuevo.\n";
        return;
    }

    // Solicitar y validar el monto
    while (true) {
        std::cout << "Ingrese el monto a transferir: ";
        std::cin >> monto;
        if (std::cin.fail() || monto <= 0) {
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer
            std::cout << "Monto invalido. Intentelo de nuevo.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer
            break;
        }
    }

    // Solicitar y validar la moneda
    std::cout << "Ingrese la moneda: ";
    std::getline(std::cin, moneda);
    if (moneda.empty()) {
        std::cout << "Moneda invalida. Intentelo de nuevo.\n";
        return;
    }


    // Consultar el balance y la moneda de la cuenta de origen
    std::string consultaBalanceCO = "SELECT balance, currency FROM BankAccount WHERE id_account = '" + cuentaOrigen + "'";
    auto datosCO = db.ejecutarConsultaTransferencia(consultaBalanceCO);

    if (datosCO.empty()) {
        std::cout << "Cuenta de origen no encontrada.\n";
        return;
    }

    double balanceAnteriorCO;
    std::string monedaOrigen;
    try {
        balanceAnteriorCO = std::stod(datosCO["balance"]);
        monedaOrigen = datosCO["currency"];
    } catch (const std::invalid_argument& e) {
        std::cout << "Error al convertir el balance de la cuenta de origen.\n";
        return;
    } catch (const std::out_of_range& e) {
        std::cout << "Balance de la cuenta de origen fuera de rango.\n";
        return;
    }


    // Consultar el balance y la moneda de la cuenta de destino
    std::string consultaBalanceCD = "SELECT balance, currency FROM BankAccount WHERE id_account = '" + cuentaDestino + "'";
    auto datosCD = db.ejecutarConsultaTransferencia(consultaBalanceCD);

    if (datosCD.empty()) {
        std::cout << "Cuenta de destino no encontrada.\n";
        return;
    }

    double balanceAnteriorCD;
    std::string monedaDestino;
    try {
        balanceAnteriorCD = std::stod(datosCD["balance"]);
        monedaDestino = datosCD["currency"];
    } catch (const std::invalid_argument& e) {
        std::cout << "Error al convertir el balance de la cuenta de destino.\n";
        return;
    } catch (const std::out_of_range& e) {
        std::cout << "Balance de la cuenta de destino fuera de rango.\n";
        return;
    }

    // Conversión de moneda si es necesario
    if (moneda != monedaOrigen) {
        double tipoDeCambio = db.obtenerTipoDeCambio(moneda, monedaOrigen);
        monto *= tipoDeCambio;
        std::cout << "Monto convertido a " << monedaOrigen << ": " << monto << std::endl;
    }

        // Actualizar balances
    double nuevoSaldoOrigen = balanceAnteriorCO - monto;
    double nuevoSaldoDestino = balanceAnteriorCD + monto;

    // Iniciar transacción
    db.ejecutarSQL(beginTransactionSQL);

    // Actualizar el balance en la base de datos
    std::string actualizarBalanceOrigen = "UPDATE BankAccount SET balance = " + std::to_string(nuevoSaldoOrigen) +
                                          " WHERE id_account = '" + cuentaOrigen + "'";
    std::string actualizarBalanceDestino = "UPDATE BankAccount SET balance = " + std::to_string(nuevoSaldoDestino) +
                                           " WHERE id_account = '" + cuentaDestino + "'";

    db.ejecutarSQL(actualizarBalanceOrigen);
    db.ejecutarSQL(actualizarBalanceDestino);

    // Registrar la transacción
    std::string registrarTransaccionOrigen = "INSERT INTO Transaction (date_and_time, transaction_type, currency, transaction_amount, origin_account, detail, previous_qty, present_qty) VALUES (NOW(), 'transferencia_salida', '" +
                                         monedaOrigen + "', " + std::to_string(monto) + ", '" + cuentaOrigen + "', 'Detalle de la transacción', " + std::to_string(balanceAnteriorCO) + ", " + std::to_string(nuevoSaldoOrigen) + ")";

    std::string registrarTransaccionDestino = "INSERT INTO Transaction (date_and_time, transaction_type, currency, transaction_amount, target_account, detail, previous_qty, present_qty) VALUES (NOW(), 'transferencia_entrada', '" +
                                          monedaDestino + "', " + std::to_string(monto) + ", '" + cuentaDestino + "', 'Detalle de la transacción', " + std::to_string(balanceAnteriorCD) + ", " + std::to_string(nuevoSaldoDestino) + ")";

    db.ejecutarSQL(registrarTransaccionOrigen);
    db.ejecutarSQL(registrarTransaccionDestino);

    // Finalizar transacción
    db.ejecutarSQL(endTransactionSQL);


}

