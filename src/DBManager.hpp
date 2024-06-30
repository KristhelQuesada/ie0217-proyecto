/**
 * @file DBManager.hpp
 * 
 * @brief Clase DBManager
 * 
 * Esta clase permite la conexión con la base de datos y la ejecución de queries.
 * 
 * MIT License
 * 
 * Copyright (c) 2024 Oscar Porras Silesky / Kristhel Quesada Lopez / Antony Brenes 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
*/

#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

// Librerias convecinales de C++
#include <string>
#include <stdexcept>
#include <vector>

// Librerías necesarias para la conexión con la base de datos como <mysql/mysql.h> para MySQL
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <map>


/**
 * @brief Clase DBManager
 * 
 * Esta clase permite la conexión con la base de datos y la ejecución de queries.
 * 
*/
class DBManager {
private:
    // Atributos previo
    std::string connectionString;

    // Aributos para mantener la sesion activa
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

public:
    /*
    ------------------------------------------------------------------------------------
                  Funciones que permiten la conexion y desconexion de la DB
    ------------------------------------------------------------------------------------
    */
    /**
     * @brief Constructor de la clase que permite la conexion con el servidor al instanciar
     * un objeto de la clase mediante la funcion de conectar().
     * @param input Se espera la contrasenia de la DB
     * @return No retorna valores
     */
    DBManager(const std::string& connStr);

    /**
     * @brief Destructor de la clase que permite finalizar la conexion con el servidor.
     * @param input No recibe parametros
     * @return No retorna valores
     */
    ~DBManager();

    /**
     * @brief Funcion que ejecuta la logica para conectar la DB.
     * @param input No recibe parametros
     * @return No retorna valores
     */
    void conectar();



    /*
    ------------------------------------------------------------------------------------
          Funciones que permiten desplegar informacion sin retorno de datos
    ------------------------------------------------------------------------------------
    */
    /**
     * @brief Funcion que despliega toda la informacion asociada a una consulta
     * en crudo por lo que puede resultar conveniente para revisiones o formas generales
     * de despliegue de datos.
     * @param input
     * @return
     */
    void desplegarConsulta(const std::string& consulta, std::map<std::string, std::string> tableInfo);

    /**
     * @brief Funcion que ejecuta la logica para conectar la DB.
     * @param input
     * @return
     */
    void desplegarPrestamos(const std::string& consulta);

    /**
     * @brief Funcion que ejecuta la logica para conectar la DB.
     * @param input
     * @return
     */
    void desplegarCDP(const std::string& consulta);
    
    /**
     * @brief Funcion que ejecuta la logica para conectar la DB.
     * @param input
     * @return
     */
    void desplegarRegistroTransacciones(std::string& accountID);
    



    /*
    ------------------------------------------------------------------------------------
            Funciones que permiten retornar informacion, de a dato o completo
    ------------------------------------------------------------------------------------
    */

    std::string ejecutarConsulta(const std::string& consulta);
    std::map<std::string, std::string> ejecutarConsultaRetiroDeposito(const std::string& consulta);
    std::map<std::string, std::string> ejecutarConsultaTransferencia(const std::string& consulta);
    double obtenerTipoDeCambio(const std::string& monedaOrigen, const std::string& monedaDestino);
    std::map<std::string, std::string> cargarDatos(const std::string& consulta, std::map<std::string, std::string> tableInfo);
    std::string determinarCuentaID(std::string& idCliente);
    bool verificarPertenencia(const std::string& tabla, const std::string& idColumna, const std::string& idAccount, const std::string& idCliente);

    


    /*
    ------------------------------------------------------------------------------------
         Funcion que permite ejecutar queries como CREATE, INSERT, UPDATE y DELETE
                      es decir, que no requieren retorno de datos
    ------------------------------------------------------------------------------------
    */
    void ejecutarSQL(const std::string& comandoSQL);
    void ejecutarTransactionSQL(const std::vector<string>& querySet);




    /*
    ------------------------------------------------------------------------------------
                       Funcion que permiten verificar pertenencias
    ------------------------------------------------------------------------------------
    */
    string determinarCuentaID(string& idCliente);
    bool verificarPertenencia(const string& tabla, const string& idColumna, const std::string& idAccount);




    /*
    ------------------------------------------------------------------------------------
          Funciones que permiten ejecutar el reporte de prestamos. Se implementa
             de manera individual porque se requiere de exportacion de datos
    ------------------------------------------------------------------------------------
    */
    void exportLoanReport(std::string& idLoan);




    /*
    ------------------------------------------------------------------------------------
            Funcion que permite deplegar la informacion asociada al error que
                        pueda generarse al ejecutar un query
    ------------------------------------------------------------------------------------
    */
    void manejarErrores(const sql::SQLException &e);




    /*
    ------------------------------------------------------------------------------------
            Funcion que prueba si el vinculo  ha sido establecido sin necesidad
             de ejecutar otras funciones mas complejar. Si esta sirve se asume
                                   que el resto tambien
    ------------------------------------------------------------------------------------
    */
    void testingVinculo();
};


#endif // DBMANAGER_HPP