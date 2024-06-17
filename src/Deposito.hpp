#ifndef DEPOSITO_HPP
#define DEPOSITO_HPP

#include "Transaccion.hpp"

class Deposito : public Transaccion {
private:
    int cuentaDestino;
    double balanceAnterior;
    double balancePosterior;

public:
    Deposito(int id_client, DBManager& db);

    void ejecutar() override; // Implementa el método de depósito
};

#endif // DEPOSITO_HPP
