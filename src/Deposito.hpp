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
    // Se implementa el método de depósito
    void ejecutar() override; 
};

#endif // DEPOSITO_HPP


