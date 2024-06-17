#ifndef TRANSFERENCIA_HPP
#define TRANSFERENCIA_HPP

#include <cmath>
#include "Transaccion.hpp"

class Transferencia : public Transaccion {
private:
    int cuentaOrigen;
    int cuentaDestino;
    double balanceAnterior;
    double balancePosterior;

public:
    // Constructor
    Transferencia(int id, double monto, const std::string& moneda, const std::string& detalle,
           int cuentaOrigen, int cuentaDestino, double balanceAnterior, double balancePosterior);

    // Implementa el método de transferencia
    void ejecutar() override;

    // Método que solicita información
    void solicitudInformacion ();

    // Método para convertir moneda
    double convertirMoneda(double monto, const std::string& monedaOrigen, 
                        const std::string& monedaDestino);

    // Métodos para transferir entre cuentas de la misma moneda y diferente moneda
    void transferirMismaMoneda(double monto, const std::string& moneda, 
                             int numeroCuentaOrigen, int numeroCuentaDestino);
    void transferirDiferenteMoneda(double monto, const std::string& monedaDestino, 
                                 int numeroCuentaOrigen, int numeroCuentaDestino);

    // Métodos para consultar y actualizar saldos
    double consultarSaldo(int numeroCuenta);
    void actualizarSaldos(int numeroCuenta, double nuevoSaldo);

    // Método para registrar la transacción
    void registrarTransaccion(int idCliente, const std::string& nombreCliente, int numeroCuentaOrigen, 
                            int numeroCuentaDestino, double monto, const std::string& moneda, 
                            const std::string& detalle);
};

#endif // TRANSFERENCIA_HPP 