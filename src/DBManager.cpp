#include "DBManager.hpp"
#include <iostream>
#include <fstream> // Libreria para que permite el uso de outfile para generar una exportacion de datos
#include <iomanip> // Libreria que permite que sean mas legibles los datos que se exportan al archivo .txt
using namespace std;
using namespace sql;


/*
------------------------------------------------------------------------------------
              Funciones que permiten la conexion y desconexion de la DB
------------------------------------------------------------------------------------
*/
// CONSTRUCTOR QUE CONECTA CON LA DB AL INICIAR UNA INSTANCIA
DBManager::DBManager(const std::string& connStr) : connectionString(connStr) {
    cout << connStr << endl;
    this->conectar();
}



// DESTRUCTOR QUE FINALIZA LA CONEXION CON LA DB AL FINALIZAR EL PROGRAMA
DBManager::~DBManager() {
    // Elimina la conexion
    cout << "Base de datos desconectada." << endl;
    delete con;
}



// FUNCION QUE CONTIENE LA LOGICA PARA IMPLEMENTAR LA CONEXION A LA DB
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
        this->manejarErrores(e);
    }
}






/*
------------------------------------------------------------------------------------
      Funciones que permiten desplegar informacion sin retorno de datos
------------------------------------------------------------------------------------
*/
// Analizar si es util o no
void DBManager::desplegarConsulta(const std::string& consulta, std::map<std::string, std::string> tableInfo) {
    // Esto debe comentarse tras la verificacion
    std::cout << "Ejecutando consulta: " << consulta << "\n" << std::endl;

    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery(consulta);

        // Crear un iterador del mapa que viene por paramtero
        map<string, string>::iterator it_map = tableInfo.begin();

        // Siempre que haya records asociados a la consulta
        while (res->next()) {
            cout << "---------------------------------------------" << endl;
            while (it_map != tableInfo.end()) {
                cout << "> " << it_map->second << ": " << res->getString(it_map->first) << endl;
                ++it_map;
            }
            cout << "---------------------------------------------" << endl;
        }   

        delete res;
        delete stmt;
        
    } catch (sql::SQLException &e) {
        this->manejarErrores(e);
    }
}


// Este método ejecuta una consulta SQL y devuelve el resultado
void DBManager::desplegarPrestamos(const std::string& consulta) {
    std::cout << "Ejecutando consulta: " << consulta << std::endl; // pending to delete/comment

    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery(consulta);

        int contador = 1; // Lleva la cuenta de la cantidad de Prestamos del Cliente

        while (res->next()) {
            cout << "-------------- Prestamo " << contador << " --------------" << endl;
            cout << "  - ID del Préstamo       : " << res->getString("id_loan") << endl;
            cout << "  - ID del Cliente        : " << res->getString("id_client") << endl;
            cout << "  - Fecha de Creación     : " << res->getString("creation_date") << endl;
            cout << "  - Tipo de Préstamo      : " << res->getString("id_loan_type") << endl;
            cout << "  - Divisa                : " << res->getString("currency") << endl;
            cout << "  - Monto Solicitado      : " << res->getString("principal") << endl;
            cout << "  - Tasa de Interés       : " << res->getString("interest_rate") << endl;
            cout << "  - Plazo                 : " << res->getString("loan_term") << endl;
            cout << "  - Cuota Mensual         : " << res->getString("monthly_payment") << endl;
            cout << "  - Monto Total a Pagar   : " << res->getString("total_repayment") << endl;
            cout << "  - Monto Actual Pagado   : " << res->getString("actual_debt") << "\n" << endl;
            contador++;
        }   

        delete res;
        delete stmt;
        
    } catch (sql::SQLException &e) {
        this->manejarErrores(e);
    }
}

// Este método ejecuta una consulta SQL y devuelve el resultado
void DBManager::desplegarCDP(const std::string& consulta) {
    std::cout << "Ejecutando consulta: " << consulta << std::endl; // Considerar eliminar/comentar

    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery(consulta);

        int contador = 1; // Lleva la cuenta de la cantidad de CDP del Cliente

        while (res->next()) {
            std::cout << "-------------- CDP " << contador << " --------------" << std::endl;
            std::cout << "  - ID del Certificado   : " << res->getString("id_deposit_certificate") << std::endl;
            std::cout << "  - ID de la Cuenta       : " << res->getString("id_account") << std::endl;
            std::cout << "  - Plazo               : " << res->getString("cdp_term") << std::endl;
            std::cout << "  - Fecha de Creación     : " << res->getString("startline") << std::endl;
            std::cout << "  - Fecha de Vencimiento  : " << res->getString("deadline") << std::endl;
            std::cout << "  - Capital Principal     : " << res->getString("principal") << std::endl;
            std::cout << "  - Tasa de Interés       : " << res->getString("interest_rate") << std::endl;
            std::cout << "  - Frecuencia de Cap.    : " << res->getString("capitalization_freq") << std::endl;
            std::cout << "  - Penalización de Int.  : " << res->getString("interest_penalty") << std::endl;
            std::cout << "  - Monto Final           : " << res->getString("final_amount") << "\n" << std::endl;
            contador++;
        }

        delete res;
        delete stmt;

    } catch (sql::SQLException &e) {
        this->manejarErrores(e);
    }
}


/*
------------------------------------------------------------------------------------
        Funciones que permiten retornar informacion, de a dato o completo
------------------------------------------------------------------------------------
*/
// Funcion que retorna un unico dato consultado
std::string DBManager::ejecutarConsulta(const std::string& consulta) {
    std::cout << "Ejecutando consulta: " << consulta << "\n" << std::endl;
    std::string data;

    // Se prueba con el ejemplo inicial de la tabla Client
    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery(consulta);

        // Mientras siga habiendo un record en la tabla consultada entonces ejecute
        while (res->next()) {
            data = res->getString(1); // 1 indica primera columna
        }

        return data;
        delete res;
        delete stmt;
        
    } catch (sql::SQLException &e) {
        this->manejarErrores(e);
        data = "Hubo un error en la consulta.";
    }

    return data;
}


// Funcion que permite cargar datos asociados a un record de tabla por completo
std::map<std::string, std::string> DBManager::cargarDatos(const std::string& consulta, std::map<std::string, std::string> tableInfo) {
    // Eliminar/Comentar esto cuando se hayan realizado todas las pruebas
    cout << "Ejecutando consulta: " << consulta << endl;

    std::map<std::string, std::string> datosConsulta; // Mapa de retorno
    map<string, string>::iterator it_map = tableInfo.begin();// Iterador del mapa argumento

    try {
        Statement *stmt = con->createStatement();
        ResultSet *res = stmt->executeQuery(consulta);

        if (res->next()) { // Se espera que solo se ejecute una vez
            while (it_map != tableInfo.end()) { // mientras haya aun info ejecute
                datosConsulta[it_map->first] = res->getString(it_map->first); // ingresar datos
                ++it_map;
            }
        }

        delete res;
        delete stmt;

    } catch (SQLException &e) {
        this->manejarErrores(e);
    }

    return datosConsulta;
}


// Funcion util para las clases Retiro y Deposito
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
        this->manejarErrores(e);
    }

    return datosConsulta;
}





/*
------------------------------------------------------------------------------------
     Funcion que permite ejecutar queries como CREATE, INSERT, UPDATE y DELETE
                  es decir, que no requieren retorno de datos
------------------------------------------------------------------------------------
*/
void DBManager::ejecutarSQL(const std::string& consulta) {
    // Funciona, al correr todas las pruebas se debe eliminar/comentar esta linea
    std::cout << "Ejecutando SQL: " << consulta << std::endl;
    
    
    try {
        sql::Statement *stmt = con->createStatement();
        stmt->executeUpdate(consulta);  // para sentencias INSERT, UPDATE, DELETE
        delete stmt;
        
    } catch (sql::SQLException &e) {
        this->manejarErrores(e);
    } 
}




/*
------------------------------------------------------------------------------------
        Funcion que permite deplegar la informacion asociada al error que
                    pueda generarse al ejecutar un query
------------------------------------------------------------------------------------
*/
void DBManager::manejarErrores(const sql::SQLException &e) {
    //std::cerr << "Error en la base de datos: " << e.what() << std::endl;
    cout << "ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}




/*
------------------------------------------------------------------------------------
      Funciones que permiten ejecutar el reporte de prestamos. Se implementa
         de manera individual porque se requiere de exportacion de datos
------------------------------------------------------------------------------------
*/
// Solo falta agregarle un WHERE al query y parametrizar para que quede general y se
//  consulte por persona.
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
        this->manejarErrores(e);
    }
}


/*
------------------------------------------------------------------------------------
        Funcion que prueba si el vinculo  ha sido establecido sin necesidad
         de ejecutar otras funciones mas complejar. Si esta sirve se asume
                               que el resto tambien
------------------------------------------------------------------------------------
*/
void DBManager::testingVinculo() {
    cout << "Has establecido conexion con la DB." << endl;
}