

#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include <string>
#include <iostream>
#include <stdexcept>
// Incluir aquí las librerías necesarias para la conexión con la base de datos como <mysql/mysql.h> para MySQL

class DBManager {
private:
    std::string connectionString;
    // Se supone que se va a usar una librería de conexión a DB como MySQL, pensar en mas atributos

public:
    DBManager(const std::string& connStr);
    void conectar();
    std::string ejecutarConsulta(const std::string& consulta);
    void ejecutarSQL(const std::string& comandoSQL);
    void manejarErrores(const std::exception& e);
};

#endif // DBMANAGER_HPP