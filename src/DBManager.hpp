

#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

// Librerias convecinales de C++
#include <string>
#include <stdexcept>

// Librerías necesarias para la conexión con la base de datos como <mysql/mysql.h> para MySQL
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <map>

class DBManager {
private:
    // Atributos previo
    std::string connectionString;
    // Aributos para mantener la sesion activa
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

public:
    // Constructor y Destructor
    DBManager(const std::string& connStr); // Permite la conexion con el servidor al instanciase
    ~DBManager();                          // Cierra la conexion con el servidor

    // Funciones personalizadas
    void conectar();
    std::string ejecutarConsulta(const std::string& consulta, std::map<std::string, std::string> tableInfo);
    std::map<std::string, std::string> DBManager::ejecutarConsultaRetiroDeposito(const std::string& consulta)
    void ejecutarSQL(const std::string& comandoSQL);
    void manejarErrores(const sql::SQLException &e);

    // Funcion adicional al funcionamiento basico
    void exportLoanReport();

    // Funcion de pruebas de vinculacion
    void testingVinculo();
};

#endif // DBMANAGER_HPP