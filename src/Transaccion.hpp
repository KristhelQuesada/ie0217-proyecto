#ifndef TRANSACCION_HPP
#define TRANSACCION_HPP

#include <string>

class Transaccion {
protected:
    int idTransaccion;
    double monto;
    std::string moneda;
    std::string detalle;

public:
    Transaccion(int id, double monto, const std::string& moneda, const std::string& detalle="");
    virtual void ejecutar() = 0; // Método virtual puro para ser implementado por clases derivadas
};

#endif // TRANSACCION_HPP
