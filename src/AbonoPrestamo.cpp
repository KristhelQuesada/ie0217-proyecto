#include "AbonoPrestamo.hpp"
#include <iostream>

AbonoPrestamo::AbonoPrestamo(int id, double monto, const std::string& moneda, int idPrestamo,
                             double balanceAnterior, double balancePosterior)
    : Transaccion(id, monto, moneda), idPrestamo(idPrestamo),
      balanceAnterior(balanceAnterior), balancePosterior(balancePosterior) {}

void AbonoPrestamo::ejecutar() {
    std::cout << "Realizando pago de cuota (abono) de " << monto << " " << moneda
              << " para el prestamo " << idPrestamo << ". Balance anterior: " << balanceAnterior
              << ", Balance posterior: " << balancePosterior << std::endl;
    // Aquí va la lógica para actualizar la base de datos
}