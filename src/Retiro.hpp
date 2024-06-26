#ifndef RETIRO_HPP
#define RETIRO_HPP

#include "Transaccion.hpp"

class Retiro : public Transaccion {
private:
    int cuentaOrigen;
    double balanceAnterior;
    double balancePosterior;

public:
    Retiro(int id_client, DBManager& db);
    // Se implementa el método de retiro
    void ejecutar() override; 
};

#endif // RETIRO_HPP


