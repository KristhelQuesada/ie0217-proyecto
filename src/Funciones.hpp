#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "DBManager.hpp"

// ENUMS
enum loanTypes {
    PERSONAL = 1,
    PRENDARIO,
    HIPOTECARIO,
    LOAN_TYPE_MAX // para saber cuantas opciones tenemos
};

enum opcionesCS {
    PLATAFORMA = 1,
    DOC_REQUEST,
    TRANSACCION,
    FINALIZAR_CS,
    CS_MAX // para saber cuantas opciones tenemos
};

enum transacciones {
    DEPOSIT = 1,
    WITHDRAWAL,
    TRANSFER,
    LOAN_PAYMENT,
    TRAN_MAX // para saber cuantas opciones tenemos
};

enum opt_platform {
    CLIENTE = 1,
    LOAN,
    CDP,
    RETURN_CS,
    OPT_PLAT_MAX // para saber cuantas opciones tenemos
};

enum docs_requested {
    RDP = 1,
    RDT,
    DOCS_MAX // para saber cuantas opciones tenemos
};

// Prototipo de las funciones a desarrollar en Funciones.cpp
/**
 * @brief Funcion que se encarga de revisar la entrada de un usuario
 * para validar su opcion en el menu.
 * @param input Entrada tipo string recibida del usuario
 * @return Un valor entero fuera del rango de las opciones permitidas
 * del menu
 */
int verifyMenuOption(std::string input, int out_range);
bool verifyDate(std::string due_date, std::string payment_date);
std::string to_string_with_precision(double value, int precision);

// Menus del menu principal
std::map<std::string, std::string> calculateLoan();
void goMenuCS(DBManager& db);

// Menus del menu de atencion al cliente
void go_plataforma(int id_client, DBManager& db);
void go_request_docs(int id_client, DBManager& db);
void begin_transaction(int id_client, DBManager& db);



#endif // FUNCIONES_HPP