#ifndef MENUS_HPP
#define MENUS_HPP



/*
--------------------------------
           Bibliotecas
--------------------------------
*/
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "DBManager.hpp"



/*
--------------------------------
             ENUMS
--------------------------------
*/
/**
 * @brief Enumeración de las opciones de costumer service.
 * 
 * Esta enumeración lista las opciones validas que pueden ser
 * seleccionadas dentro del menu de goMenu() donde se selecciona
 * el tipo de tramite de atencion al cliente que quiere crearse.
 */
enum opcionesCS {
    PLATAFORMA = 1,
    TRANSACCION,
    DOC_REQUEST,
    FINALIZAR_CS,
    CS_MAX // para saber cuantas opciones tenemos
};

/**
 * @brief Enumeración de tipos de transacciones bancarias.
 * 
 * Esta enumeración lista las opciones validas que pueden ser
 * seleccionadas dentro del menu de begin_transaction() donde se
 * selecciona el tipo de transaccion disponible en el sistema.
 */
enum transacciones {
    DEPOSIT = 1,
    WITHDRAWAL,
    TRANSFER,
    LOAN_PAYMENT,
    TRAN_MAX // para saber cuantas opciones tenemos
};

/**
 * @brief Enumeración de las opciones de plataformar.
 * 
 * Esta enumeración lista las opciones validas y existentes que
 * pueden realizarse en plataforma, u son seleccionadas dentro
 * de la funcion go_plataforma().
 */
enum opt_platform {
    CLIENTE = 1,
    LOAN,
    CerDP,
    RETURN_CS,
    OPT_PLAT_MAX // para saber cuantas opciones tenemos
};

/**
 * @brief Enumeración de tipos registros que pueden consultarse.
 * 
 * Esta enumeración lista los documentos que pueden ser solicitados
 * por un cliente en ventanilla, y su seleccion se encuentra dentro
 * del menu go_request_docs()
 */
enum docs_requested {
    RDP = 1,
    RDT,
    DOCS_MAX // para saber cuantas opciones tenemos
};



/*
--------------------------------
           Funciones
--------------------------------
*/
void menuCS(DBManager& db);
void menuPlatform(int id_client, DBManager& db);
void menuDocuments(int id_client, DBManager& db);
void menuTransactions(int id_client, DBManager& db);

#endif // MENUS_HPP