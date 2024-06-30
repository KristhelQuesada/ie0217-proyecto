#include "DBManager.hpp"
#include <iostream>
#include <fstream> // Libreria para que permite el uso de outfile para generar una exportacion de datos
#include <iomanip> // Libreria que permite que sean mas legibles los datos que se exportan al archivo .txt
#include <string>
#include <vector>
using namespace std;
using namespace sql;


/*
------------------------------------------------------------------------------------
              Funciones que permiten la conexion y desconexion de la DB
------------------------------------------------------------------------------------
*/
// CONSTRUCTOR QUE CONECTA CON LA DB AL INICIAR UNA INSTANCIA
DBManager::DBManager(const std::string& connStr) : connectionString(connStr) {
    std::cout << connStr << endl;
    this->conectar();
}



// DESTRUCTOR QUE FINALIZA LA CONEXION CON LA DB AL FINALIZAR EL PROGRAMA
DBManager::~DBManager() {
    // Elimina la conexion
    std::cout << "Base de datos desconectada." << endl;
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
        std::cout << "Conexión establecida exitosamente." << endl;

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
            std::cout << "---------------------------------------------" << endl;
            while (it_map != tableInfo.end()) {
                std::cout << "> " << it_map->second << ": " << res->getString(it_map->first) << endl;
                ++it_map;
            }
            std::cout << "---------------------------------------------" << endl;
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
            std::cout << "  - ID del Préstamo       : " << res->getString("id_loan") << endl;
            std::cout << "-------------- Prestamo " << contador << " --------------" << endl;
            std::cout << "  - ID del Cliente        : " << res->getString("id_client") << endl;
            std::cout << "  - Fecha de Creación     : " << res->getString("creation_date") << endl;
            std::cout << "  - Tipo de Préstamo      : " << res->getString("id_loan_type") << endl;
            std::cout << "  - Divisa                : " << res->getString("currency") << endl;
            std::cout << "  - Monto Solicitado      : " << res->getString("principal") << endl;
            std::cout << "  - Tasa de Interés       : " << res->getString("interest_rate") << endl;
            std::cout << "  - Plazo                 : " << res->getString("loan_term") << endl;
            std::cout << "  - Cuota Mensual         : " << res->getString("monthly_payment") << endl;
            std::cout << "  - Monto Total a Pagar   : " << res->getString("total_repayment") << endl;
            std::cout << "  - Monto Actual Pagado   : " << res->getString("actual_debt") << "\n" << endl;
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
    std::cout << "Ejecutando consulta: " << consulta << endl;

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
    std::cout << "Ejecutando consulta: " << consulta << endl;

    try {
        Statement *stmt = con->createStatement();
        ResultSet *res = stmt->executeQuery(consulta);

        // Asumimos que solo nos interesa la primera fila para el retiro
        if (res->next()) {
            datosConsulta["balance"] = to_string(res->getDouble("balance"));
            datosConsulta["currency"] = res->getString("currency");
        }

        delete res;
        delete stmt;
    } catch (SQLException &e) {
        this->manejarErrores(e);
    }

    return datosConsulta;
}

// Método para ejecutar una consulta de balance y moneda de una cuenta específica
std::map<std::string, std::string> DBManager::ejecutarConsultaTransferencia(const std::string& consulta) {
    std::map<std::string, std::string> datosConsulta;

    try {
        Statement *stmt = con->createStatement();
        ResultSet *res = stmt->executeQuery(consulta);

        if (res->next()) {
            datosConsulta["balance"] = std::to_string(res->getDouble("balance"));
            datosConsulta["currency"] = res->getString("currency");
        }

        delete res;
        delete stmt;
    } catch (SQLException &e) {
        std::cerr << "Error de SQL: " << e.what() << std::endl;
        std::cerr << "Código de error SQL: " << e.getErrorCode() << std::endl;
        }

        return datosConsulta;
    }





/*
------------------------------------------------------------------------------------
              Implementación de obtenerTipoDeCambio
------------------------------------------------------------------------------------
*/
double DBManager::obtenerTipoDeCambio(const std::string& monedaOrigen, const std::string& monedaDestino) {
    // Definir tipos de cambio
    const double USD_TO_CRC = 523.50;
    const double CRC_TO_USD = 0.0019;

    if (monedaOrigen == "USD" && monedaDestino == "CRC") {
        return USD_TO_CRC;
    } else if (monedaOrigen == "CRC" && monedaDestino == "USD") {
        return CRC_TO_USD;
    } else if (monedaOrigen == monedaDestino) {
        return 1.0; // Misma moneda, tipo de cambio 1 a 1
    } else {
        throw std::invalid_argument("Tipo de cambio no soportado para las monedas especificadas.");
    }
}


string DBManager::determinarCuentaID(string& idCliente) {
    string queryAccount, currency, account;

    // Obtener la cantidad de cuentas asociadas al DB
    string queryContadorCuentas = "SELECT COUNT(*) FROM BankAccount WHERE id_client=" + idCliente;
    int contadorCuentas = stoi(this->ejecutarConsulta(queryContadorCuentas));
    bool isValid;

    // Retornar el idAccount
    if (contadorCuentas == 0) {
        return queryAccount = "0";
    } else if (contadorCuentas == 1) {
        queryAccount = "SELECT id_account FROM BankAccount WHERE id_client=" + idCliente;
        
    } else {

        while(!isValid) {}
            std::cout << "Con cual cuenta se procede (USD/CRC): ";
            cin >> currency;

            if (currency == "USD" || currency == "CRC") {
                queryAccount = "SELECT id_account FROM BankAccount WHERE id_client=" + idCliente +
                               " AND currency=" + currency + ";";
                isValid = true;

            } else {
                std::cout << "Ingrese una divisa correcta.\n";
            }
    }

    return this->ejecutarConsulta(queryAccount);
}


/*
------------------------------------------------------------------------------------
     Funcion que permite verificar si lo que el usuario ingreso se asocia a
     su informacion o esta intentando acceder a informacion de otra persona
                    Es util en la impresion de documentos
------------------------------------------------------------------------------------
*/
bool DBManager::verificarPertenencia(const string& tabla, const string& idColumna, const string& idAccount, const string& idClient){
    string queryAccount = "SELECT id_client FROM " + tabla + " WHERE " + idColumna + "=" + idAccount;
    string toCheckOwner = this->ejecutarConsulta(queryAccount);

    if (idClient == toCheckOwner) {
        return true;
    } else {
        return false;
    }
}



/*
------------------------------------------------------------------------------------
     Funcion que permite ejecutar queries como CREATE, INSERT, UPDATE y DELETE
                  es decir, que no requieren retorno de datos
------------------------------------------------------------------------------------
*/
// Realiza el query mas no mediante transaccion
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

// Funcion que permite iniciar una transaccion de SQL;
void DBManager::ejecutarTransactionSQL(const std::vector<string>& querySet) {
    // Funciona, al correr todas las pruebas se debe eliminar/comentar esta linea
    //std::cout << "Ejecutando consulta SQL: " << consulta << std::endl;
    
    
    try {
        sql::Statement *stmt = con->createStatement();
        stmt->executeUpdate("START TRANSACTION; ");

        // Ejecutar cada query que contenga el vector
        for (const auto& query : querySet) {
            cout << "Ejecutando consulta SQL: " << query << endl;
            stmt->executeUpdate(query);
        }

        stmt->executeUpdate("COMMIT;");
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
        Funcion que permite deplegar el registro de transacciones asociado
         a una una cuenta especifica tanto por origin como target account
------------------------------------------------------------------------------------
*/
void DBManager::desplegarRegistroTransacciones(string& accountID) {
    string consulta = "SELECT * FROM Transaction WHERE origin_account=" + accountID +
                      " OR target_account=" + accountID + ";";

    cout << "Ejecutando consulta: " << consulta << endl; // pending to delete/comment

    try {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery(consulta);

        int contador = 1; // Lleva la cuenta de la cantidad de Prestamos del Cliente
        
        cout << "_________________________________________________________\n";
        cout << "                REGISTRO DE TRANSACCIONES                \n" << endl;


        while (res->next()) {
            cout << "-------------- Transacción " << contador << " --------------" << endl;
            cout << "  - ID Transacción      : " << res->getString("id_transaction") << endl;
            cout << "  - Fecha de Ejecución  : " << res->getString("date_and_time") << endl;
            cout << "  - Tipo de Transacción : " << res->getString("transaction_type") << endl;
            cout << "  - Divisa              : " << res->getString("currency") << endl;
            cout << "  - Monto               : " << res->getString("transaction_amount") << endl;
            cout << "  - Cuenta de Origen    : " << res->getString("origin_account") << endl;
            cout << "  - Cuenta Destino      : " << res->getString("target_account") << endl;
            cout << "  - Detalle             : " << res->getString("detail") << endl;
            cout << "  - Saldo Anterior      : " << res->getString("previous_qty") << endl;
            cout << "  - Saldo Posterior     : " << res->getString("present_qty") << "\n" << endl;
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
      Funciones que permiten ejecutar el reporte de prestamos. Se implementa
         de manera individual porque se requiere de exportacion de datos
------------------------------------------------------------------------------------
*/
void DBManager::exportLoanReport(std::string& idLoan) {
    // Impresion inicial
    cout << "Ejecutando exportación del Reporte de Préstamos: " << endl;

    // Query que genera la tabla temporal (aun tengo que agregarle un where para que se genere para un unico cliente)
    string tempTableQuery = "CREATE TEMPORARY TABLE `loanreport` "
                            "SELECT "
                            "Client.id_client, "
                            "CONCAT(client_name, ' ', client_lastname) AS Cliente, "
                            "Loan.id_loan, loan_term, creation_date, id_loan_type, "
                            "CONCAT(principal, ' (', currency, ')') AS MontoSolicitado, "
                            "interest_rate, monthly_payment, total_repayment, actual_debt, "
                            "id_payment, terms_completed, total_capital_paid, total_interest_paid, "
                            "capital_paid, interest_paid, made_on "
                            "FROM Client "
                            "INNER JOIN Loan ON Client.id_client = Loan.id_client "
                            "INNER JOIN Payment ON Loan.id_loan = Payment.id_loan "
                            "WHERE Loan.id_loan=" + idLoan + ";";



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
        int shortwidth = 12;
        int width = 20;

        // Escribe los encabezados de las columnas
        // Se utilizan left y setw para mejor formato de visualizacion
        // Podria modificarse para que los datos esten transpuestos
        // es decir, en la primera columna los header y luego los datos
        // queda pendiente y para comentar
        outfile << left << setw(shortwidth) << "ID"
                << left << setw(width) << "Cliente"
                << left << setw(shortwidth) << "ID Préstamo"
                << left << setw(shortwidth) << "Cuotas"
                << left << setw(width) << "Creación"
                << left << setw(width) << "Tipo de Préstamo"
                << left << setw(width) << "Monto Solicitado"
                << left << setw(shortwidth) << "Interés"
                << left << setw(width) << "Cuota Mensual"
                << left << setw(width) << "Deuda Total"
                << left << setw(width) << "Deuda Actual"
                << left << setw(shortwidth) << "ID del Abono"
                << left << setw(shortwidth) << "Cuotas pagas"
                << left << setw(width) << "Capital Actual"
                << left << setw(width) << "Intereses Actual"
                << left << setw(width) << "Capital abonado"
                << left << setw(width) << "Interés abonado"
                << left << setw(width) << "Fecha del Abono"
                << endl;

        // Escribe los datos de la consulta en el archivo
        while (res->next()) {
            outfile << left << setw(shortwidth) << res->getInt("id_client")
                    << left << setw(width) << res->getString("Cliente")
                    << left << setw(shortwidth) << res->getInt("id_loan")
                    << left << setw(shortwidth) << res->getInt("loan_term")
                    << left << setw(width) << res->getString("creation_date")
                    << left << setw(width) << res->getString("id_loan_type")
                    << left << setw(width) << res->getString("MontoSolicitado")
                    << left << setw(shortwidth) << res->getInt("interest_rate")
                    << left << setw(width) << res->getString("monthly_payment")
                    << left << setw(width) << res->getString("total_repayment")
                    << left << setw(width) << res->getString("actual_debt")
                    << left << setw(shortwidth) << res->getInt("id_payment")
                    << left << setw(shortwidth) << res->getInt("terms_completed")
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
        cout << "El Reporte de Préstamos ha sido creado con éxito." << endl;

        // Liberacion de recursos
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
    cout << "Has establecido conexión con la DB." << endl;
}