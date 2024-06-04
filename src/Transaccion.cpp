#include "Transaccion.hpp"

Transaccion::Transaccion(int id, double monto, const std::string& moneda, const std::string& detalle)
    : idTransaccion(id), monto(monto), moneda(moneda), detalle(detalle) {}
