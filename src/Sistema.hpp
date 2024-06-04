#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
//#include "Cliente.hpp"
//#include "Cuenta.hpp"
//#include "Prestamo.hpp"
#include "Transaccion.hpp"
#include "DBManager.hpp"

class Sistema {
private:
    std::string database;
    DBManager dbManager;

public:
    Sistema(const std::string& dbPath);

    // Métodos centrados en las operaciones principales del sistema
    void atencionCliente();
    std::string solicitarInfo(const std::string& tipoInfo);
    void crear(ObjectType type, const std::string& data);
    void obtenerRe();
    std::string obtenerRegTrans(int idCliente);
    std::string obtenerRepPrest(int idPrestamo);
};

#endif // SISTEMA_HPP
