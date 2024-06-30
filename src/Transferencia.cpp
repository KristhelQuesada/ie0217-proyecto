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
    while (true) {
        try {
            std::cout << "Ingrese el número de cuenta de origen: ";
            std::getline(std::cin, cuentaOrigen);

            // Verificar longitud de la entrada
            if (cuentaOrigen.empty() || cuentaOrigen.size() > 10) {
                throw std::out_of_range("La longitud del número de cuenta excede el máximo permitido (10 carácteres).");
            }

            // Verificar si es un número entero
            std::stringstream ss(cuentaOrigen);
            int temp;
            if (!(ss >> temp) || !ss.eof()) {
                throw std::invalid_argument("El número de cuenta debe ser un número entero válido.");
            }

            // Si todo está bien, salir del bucle
            break;

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            std::cout << "Ingrese el número de cuenta de destino: ";
            std::getline(std::cin, cuentaOrigen);

            // Verificar longitud de la entrada
            if (cuentaOrigen.empty() || cuentaOrigen.size() > 10) {
                throw std::out_of_range("La longitud del número de cuenta excede el máximo permitido (10 carácteres).");
            }

            // Verificar si es un número entero
            std::stringstream ss(cuentaDestino);
            int temp;
            if (!(ss >> temp) || !ss.eof()) {
                throw std::invalid_argument("El número de cuenta debe ser un número entero válido.");
            }

            // Si todo está bien, salir del bucle
            break;

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Solicitar y validar el monto
    while (true) {

        std::string input;

        try {
            std::cout << "Ingrese el monto a transferir: ";
            std::getline(std::cin, input);

            // Intentar convertir la entrada a double
            std::size_t pos; // Variable para detectar carácteres no convertidos
            monto = std::stod(input, &pos);

            // Verificar si el monto es mayor que cero
            if (monto <= 0) {
                throw std::invalid_argument("El monto debe ser mayor que cero.");
            }

            // Si se llega aquí, la conversión fue exitosa y el monto es válido
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Error inesperado. Inténtelo de nuevo.\n";
        }

        return;
    }


    std::string detalle;
    bool detalleValido = false;

    while (!detalleValido) {
        std::cout << "Ingrese el detalle de la transacción (máximo 255 carácteres): ";
        std::getline(std::cin, detalle);

        try {
            if (detalle.length() > 255) {
                throw std::length_error("El detalle de la transacción no puede exceder los 255 carácteres.");
            }
            detalleValido = true; // Si no hay excepción, el detalle es válido y se sale del ciclo
        } catch (const std::length_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            // detalleValido se mantiene como false para repetir el ciclo
        }
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

    
    double tipoDeCambio = db.obtenerTipoDeCambio(monedaOrigen, monedaDestino);
    double montoCambio = monto * tipoDeCambio;
    
    

        // Actualizar balances
    double nuevoSaldoOrigen = balanceAnteriorCO - monto;
    double nuevoSaldoDestino = balanceAnteriorCD + montoCambio;

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
    std::string registrarTransaccionOrigen = "INSERT INTO Transaction (date_and_time, transaction_type, currency, transaction_amount, origin_account, detail, previous_qty, present_qty) VALUES (NOW(), 'TS', '" +
                                                monedaOrigen + "', " + std::to_string(monto) + ", '" + cuentaOrigen + "', '" + detalle + "', " +
                                                std::to_string(balanceAnteriorCO) + ", " + std::to_string(nuevoSaldoOrigen) + ")";

    // Insertar transacción de entrada
    std::string registrarTransaccionDestino = "INSERT INTO Transaction (date_and_time, transaction_type, currency, transaction_amount, target_account, detail, previous_qty, present_qty) VALUES (NOW(), 'TE', '" +
                                                monedaDestino + "', " + std::to_string(montoCambio) + ", '" + cuentaDestino + "', '" + detalle + "', " +
                                                std::to_string(balanceAnteriorCO) + ", " + std::to_string(nuevoSaldoDestino) + ")";


    db.ejecutarSQL(registrarTransaccionOrigen);
    db.ejecutarSQL(registrarTransaccionDestino);

    // Finalizar transacción
    db.ejecutarSQL(endTransactionSQL);


}

