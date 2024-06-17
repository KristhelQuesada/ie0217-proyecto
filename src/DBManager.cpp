#include "DBManager.hpp"
#include <iostream>
#include <fstream> // Libreria para que permite el uso de outfile para generar una exportacion de datos
#include <iomanip> // Libreria que permite que sean mas legibles los datos que se exportan al archivo .txt
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
    std::cout << "Conectando a la base de datos: " << connectionString << std::endl;
  
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


std::map<std::string, std::string> DBManager::ejecutarConsultaRetiroDeposito(const std::string& consulta) {
    std::map<std::string, std::string> datosConsulta;
    cout << "Ejecutando consulta: " << consulta << endl;

    try {
        Statement *stmt = con->createStatement();
        ResultSet *res = stmt->executeQuery(consulta);

        // Asumimos que solo nos interesa la primera fila para el retiro
        if (res->next()) {
            datosConsulta["balance"] = to_string(res->getDouble("balance"));
            datosConsulta["tipoCuenta"] = res->getString("tipoCuenta");
        }

        delete res;
        delete stmt;
    } catch (SQLException &e) {
        cerr << "ERR: SQLException in " << __FILE__;
        cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cerr << "ERR: " << e.what();
        cerr << " (MySQL error code: " << e.getErrorCode();
        cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    return datosConsulta;
}

void DBManager::ejecutarSQL(const std::string& consulta) {
    // Este método ejecuta un comando SQL que no devuelve un conjunto de resultados
    std::cout << "Ejecutando SQL: " << consulta << std::endl;
    
    
    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = res = stmt->executeQuery(consulta);

        delete res;
        delete stmt;
        
    } catch (sql::SQLException &e) {
        cout << "ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    } 
}

void DBManager::manejarErrores(const std::exception& e) {
    // Este método maneja errores de la base de datos
    std::cerr << "Error en la base de datos: " << e.what() << std::endl;
}

// Funcion que permite generar el reporte de prestamos, por el momento, solo falta agregarle un where
// al query y parametrizar para que quede general y se consulte por persona.
void DBManager::exportLoanReport() {
    // Impresion inicial
    cout << "Ejecutando exportacion del Reporte de Prestamos: " << endl;

    // Query que genera la tabla temporal (aun tengo que agregarle un where para que se genere para un unico cliente)
    string tempTableQuery = "CREATE TEMPORARY TABLE `loanreport` "
                            "SELECT "
                            "Client.id_client, "
                            "CONCAT(client_name, ' ', client_lastname) AS full_name, "
                            "Loan.id_loan, loan_term, creation_date, id_loan_type, currency, principal, "
                            "interest_rate, monthly_payment, total_repayment, actual_debt, "
                            "id_payment, terms_completed, total_capital_amount, total_interest_amount, "
                            "total_capital_paid, total_interest_paid, capital_paid, interest_paid, made_on "
                            "FROM Client "
                            "INNER JOIN Loan ON Client.id_client = Loan.id_client "
                            "INNER JOIN Payment ON Loan.id_loan = Payment.id_loan;";

    // Logica para la exportacion
    try {
        sql::Statement* stmt = con->createStatement();

        // Query que crea la tabla temporal
        stmt->execute(tempTableQuery);

        // Seleccion de la tabla a la cual le extraeremos los datos
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM `loanreport`;");

        // Abre el archivo CSV para escribir
        std::ofstream outfile("LoanReport.txt");

        // Se configura un ancho para las columnas
        int width = 20;

        // Escribe los encabezados de las columnas
        // Se utilizan left y setw para mejor formato de visualizacion
        // Podria modificarse para que los datos esten transpuestos
        // es decir, en la primera columna los header y luego los datos
        // queda pendiente y para comentar
        outfile << left << setw(width) << "id_client"
                << left << setw(width) << "full_name"
                << left << setw(width) << "id_loan"
                << left << setw(width) << "loan_term"
                << left << setw(width) << "creation_date"
                << left << setw(width) << "id_loan_type"
                << left << setw(width) << "currency"
                << left << setw(width) << "principal"
                << left << setw(width) << "interest_rate"
                << left << setw(width) << "monthly_payment"
                << left << setw(width) << "total_repayment"
                << left << setw(width) << "actual_debt"
                << left << setw(width) << "id_payment"
                << left << setw(width) << "terms_completed"
                << left << setw(width) << "total_capital_amount"
                << left << setw(width) << "total_interest_amount"
                << left << setw(width) << "total_capital_paid"
                << left << setw(width) << "total_interest_paid"
                << left << setw(width) << "capital_paid"
                << left << setw(width) << "interest_paid"
                << left << setw(width) << "made_on"
                << endl;

        // Escribe los datos de la consulta en el archivo
        while (res->next()) {
            outfile << left << setw(width) << res->getInt("id_client")
                    << left << setw(width) << res->getString("full_name")
                    << left << setw(width) << res->getInt("id_loan")
                    << left << setw(width) << res->getInt("loan_term")
                    << left << setw(width) << res->getString("creation_date")
                    << left << setw(width) << res->getString("id_loan_type")
                    << left << setw(width) << res->getString("currency")
                    << left << setw(width) << res->getString("principal")
                    << left << setw(width) << res->getInt("interest_rate")
                    << left << setw(width) << res->getString("monthly_payment")
                    << left << setw(width) << res->getString("total_repayment")
                    << left << setw(width) << res->getString("actual_debt")
                    << left << setw(width) << res->getInt("id_payment")
                    << left << setw(width) << res->getInt("terms_completed")
                    << left << setw(width) << res->getString("total_capital_amount")
                    << left << setw(width) << res->getString("total_interest_amount")
                    << left << setw(width) << res->getString("total_capital_paid")
                    << left << setw(width) << res->getString("total_interest_paid")
                    << left << setw(width) << res->getString("capital_paid")
                    << left << setw(width) << res->getString("interest_paid")
                    << left << setw(width) << res->getString("made_on")
                    << endl;
        }

        // Cerrar el archivo
        outfile.close();

        // Borrar la tabla temporal
        stmt->execute("DROP TEMPORARY TABLE IF EXISTS `loanreport`;");

        // Mensaje de exito
        cout << "El Reporte de Prestamos ha sido creado con exito." << endl;

        // Liberacuib de recursos
        delete res;
        delete stmt;

    } catch (sql::SQLException& e) {
        cout << "ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}


// FUNCION QUE PRUEBA QUE SE PUEDEN UTILIZAR LOS METODOS DE LA BASE DE DATOS
void DBManager::testingVinculo() {
    cout << "Has establecido conexion con la DB." << endl;
}