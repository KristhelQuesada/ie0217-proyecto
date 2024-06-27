#ifndef ABONO_PRESTAMO_HPP
#define ABONO_PRESTAMO_HPP

#include "Transaccion.hpp"

class AbonoPrestamo : public Transaccion {
public:
    AbonoPrestamo(int id_client, DBManager& db);
    void ejecutar() override; // Implementa el método de depósito
    double interesAmortizacion(std::string loanID, DBManager& db);
    std::string calculateDueDate(std::string loanID, DBManager& db);
};

#endif // ABONO_PRESTAMO_HPP
