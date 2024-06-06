#include "Transferencia.hpp"
#include <iostream>

Transferencia::Transferencia(int id, double monto, const std::string& moneda, const std::string& detalle,
               int cuentaOrigen, int cuentaDestino, double balanceAnterior, double balancePosterior)
    : Transaccion(id, monto, moneda, detalle), cuentaOrigen(cuentaOrigen), cuentaDestino(cuentaDestino),
      balanceAnterior(balanceAnterior), balancePosterior(balancePosterior) {}

void Transferencia::ejecutar() {
    std::cout << "Realizando transferencia de " << monto << " " << moneda
              << " desde la cuenta " << cuentaOrigen << " a la cuenta " << cuentaDestino
              << ". Balance anterior: " << balanceAnterior
              << ", Balance posterior: " << balancePosterior << std::endl;
    
}