#ifndef TRANSFERENCIA_HPP
#define TRANSFERENCIA_HPP

#include "Transaccion.hpp"
#include "DBManager.hpp"

class Transferencia : public Transaccion {
private:
    
    double monto;
    int cuentaOrigen, cuentaDestino;
    std::string monedaOrigen, monedaDestino;
    double balanceAnterior, balancePosterior;

public:
    // Constructor
    Transferencia(int id_client, DBManager& db);

    // Implementa el método de transferencia
    void ejecutar() override;

};

#endif // TRANSFERENCIA_HPP