#ifndef TRANSFERENCIA_HPP
#define TRANSFERENCIA_HPP

#include "Transaccion.hpp"

class Transferencia : public Transaccion {
private:
    int cuentaOrigen;
    int cuentaDestino;
    double balanceAnterior;
    double balancePosterior;

public:
    Transferencia(int id, double monto, const std::string& moneda, const std::string& detalle,
           int cuentaOrigen, int cuentaDestino, double balanceAnterior, double balancePosterior);

    void ejecutar() override; // Implementa el método de transferencia
};

#endif // TRANSFERENCIA_HPP