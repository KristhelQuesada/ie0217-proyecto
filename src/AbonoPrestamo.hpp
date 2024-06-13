#ifndef ABONO_PRESTAMO_HPP
#define ABONO_PRESTAMO_HPP

#include "Transaccion.hpp"

class AbonoPrestamo : public Transaccion {
private:
    int idPrestamo;
    double balanceAnterior;
    double balancePosterior;

public:
    AbonoPrestamo(int id, double monto, const std::string& moneda, int idPrestamo,
             double balanceAnterior, double balancePosterior);

    void ejecutar() override; // Implementa el método de depósito
};

#endif // ABONO_PRESTAMO_HPP
