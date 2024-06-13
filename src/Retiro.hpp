#ifndef RETIRO_HPP
#define RETIRO_HPP

#include "Transaccion.hpp"

class Retiro : public Transaccion {
private:
    int cuentaOrigen;
    double balanceAnterior;
    double balancePosterior;

public:
    Retiro(int id, double monto, const std::string& moneda, const std::string& detalle,
           int cuentaOrigen, double balanceAnterior, double balancePosterior);

    void ejecutar() override; // Implementa el método de retiro
};

#endif // RETIRO_HPP
