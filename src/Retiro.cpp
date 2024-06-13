#include "Retiro.hpp"
#include <iostream>

Retiro::Retiro(int id, double monto, const std::string& moneda, const std::string& detalle,
               int cuentaOrigen, double balanceAnterior, double balancePosterior)
    : Transaccion(id, monto, moneda, detalle), cuentaOrigen(cuentaOrigen),
      balanceAnterior(balanceAnterior), balancePosterior(balancePosterior) {}

void Retiro::ejecutar() {
    std::cout << "Realizando retiro de " << monto << " " << moneda
              << " de la cuenta " << cuentaOrigen << ". Balance anterior: " << balanceAnterior
              << ", Balance posterior: " << balancePosterior << std::endl;
    // Aquí iría la lógica para actualizar la base de datos
}
