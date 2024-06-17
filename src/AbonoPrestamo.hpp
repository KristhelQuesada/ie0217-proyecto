#ifndef ABONO_PRESTAMO_HPP
#define ABONO_PRESTAMO_HPP

#include "Transaccion.hpp"

class AbonoPrestamo : public Transaccion {
public:
    AbonoPrestamo(int id_client, DBManager& db);
    void ejecutar() override; // Implementa el método de depósito
};

#endif // ABONO_PRESTAMO_HPP
