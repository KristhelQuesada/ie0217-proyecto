#include "DBManager.hpp"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
using namespace std;
using namespace sql;

DBManager::DBManager(const std::string& connStr) : connectionString(connStr) {
    DBManager.conectar();
}

void DBManager::conectar() {
    // Aquí va el código para establecer una conexión con la base de datos
    std::cout << "Conectando a la base de datos con la cadena: " << connectionString << std::endl;
  
    // Si se usa MySQL, se inicia la conexión aquí
    try {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        // Conexion con la base de datos
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("localhost:3306", "kris", "electricA2409"); // local
        //con = driver->connect("database-ie0217.c1y4e4ecsmip.us-east-2.rds.amazonaws.com:3306", "admin", "electricA2409"); // Amazon RDS

        // Seleccionar la base de datos
        con->setSchema("Local_Bank_Test");


        // Query de Prueba para ir validando conexion. Solo despliega todos los datos de la Tabla Cliente
        stmt = con->createStatement();
        
        res = stmt->executeQuery("SELECT * FROM Cliente");
        while (res->next()) {
            cout << "id = " << res->getInt("id_client");
            cout << ", client_name = " << res->getString("client_name");
            cout << ", client_lastname = " << res->getString("client_lastname");
            cout << ", colones_account = " << res->getInt("colones_account");
            cout << ", dolares_account = " << res->getInt("dolares_account") << endl;
        }   


        delete res;
        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {
        cout << "ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }  

}

std::string DBManager::ejecutarConsulta(const std::string& consulta) {
    // Este método ejecuta una consulta SQL y devuelve el resultado
    std::cout << "Ejecutando consulta: " << consulta << std::endl;
    // Se supone que devuelve un resultado de ejemplo
    return "Resultado de la consulta";
}

void DBManager::ejecutarSQL(const std::string& comandoSQL) {
    // Este método ejecuta un comando SQL que no devuelve un conjunto de resultados
    std::cout << "Ejecutando SQL: " << comandoSQL << std::endl;
    // Ejecuta el comando utilizando la librería de conexión a la base de datos
}

void DBManager::manejarErrores(const std::exception& e) {
    // Este método maneja errores de la base de datos
    std::cerr << "Error en la base de datos: " << e.what() << std::endl;
}

