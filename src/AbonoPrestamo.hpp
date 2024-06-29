#ifndef ABONO_PRESTAMO_HPP
#define ABONO_PRESTAMO_HPP

#include "Transaccion.hpp"
#include <string>

class AbonoPrestamo : public Transaccion {
private:
    std::map<std::string, std::string> loanData;
    std::map<std::string, std::string> lastPayment;

public:
    AbonoPrestamo(int id_client, DBManager& db);
    void ejecutar() override; // Implementa el método de depósito

    // Funciones de calculo
    std::string calcularDueDate();
    double interesAmortizacion(double capitalPagado,
                               double principal, double interes);

    // Funciones de extraccion de datos
    void extraerDatos(std::string& loanID);
    void setColumnas();

    // Funciones de verificacion
    bool verificarExistencia();
    bool verificarPuntualidad();

};

#endif // ABONO_PRESTAMO_HPP
