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
    // Funciones para la conexion
    DBManager(const std::string& connStr); // Permite la conexion con el servidor al instanciase
    ~DBManager();                          // Cierra la conexion con el servidor
    void conectar();

    // Funciones para visualizacion sin retorno de datos
    void desplegarConsulta(const std::string& consulta, std::map<std::string, std::string> tableInfo);
    void desplegarPrestamos(const std::string& consulta);
    void desplegarCDP(const std::string& consulta);
    
    // Funciones que permiten retornar datos (unico o completo)
    std::string ejecutarConsulta(const std::string& consulta, std::string& columna);
    std::map<std::string, std::string> ejecutarConsultaRetiroDeposito(const std::string& consulta);
    std::map<std::string, std::string> cargarDatos(const std::string& consulta, std::map<std::string, std::string> tableInfo);

    // Funcion que permite ejecucion de queries CIUD sin retorno
    void ejecutarSQL(const std::string& comandoSQL);

    // Funcion para el manejo de errores
    void manejarErrores(const sql::SQLException &e);

    // Funcion para exportar datos asociados a prestamos
    void exportLoanReport();

    // Funcion de pruebas de vinculacion
    void testingVinculo();
};

#endif // DBMANAGER_HPP