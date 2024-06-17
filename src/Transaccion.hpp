#ifndef TRANSACCION_HPP
#define TRANSACCION_HPP

#include "DBManager.hpp"

class Transaccion {
protected:
    int id_client;
    DBManager& db;

public:
    Transaccion(int id_client, DBManager& db);
    virtual void ejecutar() = 0; // Método virtual puro para ser implementado por clases derivadas
};

#endif // TRANSACCION_HPP