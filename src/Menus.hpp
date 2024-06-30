/**
 * @file Menus.hpp
 * 
 * @brief Archivo de cabecera con las funciones de los menus.
 * 
 * Este archivo de cabecera contiene las funciones que se encargan
 * de mostrar los menus de la aplicacion y de manejar las opciones
 * seleccionadas por el usuario.
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
    RETURN_CS2,
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
    RETURN_CS3,
    DOCS_MAX // para saber cuantas opciones tenemos
};



/*
--------------------------------
           Funciones
--------------------------------
*/

/**
 * @brief Funcion que se encarga de revisar la entrada de un usuario
 * para validar su opcion en el menu, donde funciona como buffer en
 * caso de entradas validas y como limitador en caso de invalidez.
*/
void menuCS(DBManager& db);

/**
 * @brief Funcion que se encarga de revisar la entrada de un usuario
 * para validar su opcion en el menu, donde funciona como buffer en
 * caso de entradas validas y como limitador en caso de invalidez.
*/
void menuPlatform(int id_client, DBManager& db);

/**
 * @brief Funcion que se encarga de revisar la entrada de un usuario
 * para validar su opcion en el menu, donde funciona como buffer en
 * caso de entradas validas y como limitador en caso de invalidez.
*/
void menuDocuments(int id_client, DBManager& db);

/**
 * @brief Funcion que se encarga de revisar la entrada de un usuario
 * para validar su opcion en el menu, donde funciona como buffer en
 * caso de entradas validas y como limitador en caso de invalidez.
*/
void menuTransactions(int id_client, DBManager& db);

#endif // MENUS_HPP