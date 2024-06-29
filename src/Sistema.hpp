#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
#include "Cliente.hpp"
#include "Cuenta.hpp"
#include "Prestamo.hpp"
#include "Transaccion.hpp"
#include "DBManager.hpp"

class Sistema {
private:
    std::string database;
    DBManager dbManager;

public:
    Sistema(const std::string& dbPath);

    int inicializarSistema();
/*

    // Métodos centrados en las operaciones principales del sistema
    void atencionCliente();
    std::string solicitarInfo(const std::string& tipoInfo);
    void crear();
    void obtenerRe();
    void handleTransactions();
    std::string obtenerRegTrans(int idCliente);
    std::string obtenerRepPrest(int idPrestamo);
    std::string calcularCuotasYPago(int idPrestamo);

*/
};

#endif // SISTEMA_HPP
