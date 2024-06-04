#include "Deposito.hpp"
#include <iostream>

Deposito::Deposito(int id, double monto, const std::string& moneda, const std::string& detalle,
                   int cuentaDestino, double balanceAnterior, double balancePosterior)
    : Transaccion(id, monto, moneda, detalle), cuentaDestino(cuentaDestino),
      balanceAnterior(balanceAnterior), balancePosterior(balancePosterior) {}

void Deposito::ejecutar() {
    std::cout << "Realizando depósito de " << monto << " " << moneda
              << " en la cuenta " << cuentaDestino << ". Balance anterior: " << balanceAnterior
              << ", Balance posterior: " << balancePosterior << std::endl;
    // Aquí va la lógica para actualizar la base de datos
}
