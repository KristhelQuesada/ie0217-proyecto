#include "DBManager.hpp"
#include <iostream>
using namespace std;
using namespace sql;

DBManager::DBManager(const std::string& connStr) : connectionString(connStr) {
    cout << connStr << endl;
    this->conectar();
}

DBManager::~DBManager() {
    // Elimina la conexion
    cout << "Base de datos desconectada." << endl;
    delete con;
}

void DBManager::conectar() {
    // Aquí va el código para establecer una conexión con la base de datos
    std::cout << "Conectando a la base de datos con la cadena: " << connectionString << std::endl;
  
    // Si se usa MySQL, se inicia la conexión aquí
    try {
        // Conexion con la base de datos
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("project-ie0217-db.c1y4e4ecsmip.us-east-2.rds.amazonaws.com:3306", "admin", "electricA2409");

        // Seleccionar la base de datos
        con->setSchema("project-ie0217-db");

        // Mensaje de Exito
        cout << "Conexión establecida exitosamente." << endl;

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

    // Se prueba con el ejemplo inicial de la tabla Client
    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = res = stmt->executeQuery(consulta);


        // Query de Prueba para ir validando conexion. Solo despliega todos los datos de la Tabla Cliente
        while (res->next()) {
            cout << "id = " << res->getInt("id_client");
            cout << ", client_name = " << res->getString("client_name");
            cout << ", client_lastname = " << res->getString("client_lastname");
            cout << ", id_colones_account = " << res->getInt("id_colones_account");
            cout << ", id_dolares_account = " << res->getInt("id_dolares_account") << endl;
        }   


        delete res;
        delete stmt;
        
    } catch (sql::SQLException &e) {
        cout << "ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }  

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

