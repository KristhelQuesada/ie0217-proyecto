#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP



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
using namespace std;



/*
--------------------------------
             ENUMS
--------------------------------
*/
/**
 * @brief Enumeración de tipos de prestamo a consultar.
 * 
 * Esta enumeración lista las opciones validas que pueden ser
 * seleccionadas dentro del menu de calculateLoan()
 */
enum loanTypes {
    PERSONAL = 1,
    PRENDARIO,
    HIPOTECARIO,
    LOAN_TYPE_MAX // para saber cuantas opciones tenemos
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
 * @param input Entrada tipo string recibida del usuario
 * @param input Valor minimo fuera del rango de opciones
 * @return Valor entero dentro (if valid) o fuera (if not valid) del rango
 */
int verifyMenuOption(std::string input, int out_range);             // Funcion general

/**
 * @brief Funcion que compara dos fechas para saber si se hizo el cobro antes o
 * despues de la fecha esperada (due_date) con fechas en el formato YYYY-MM-DD.
 * @param input due_date: Fechas tipo string que indica la fecha limite de pago
 * @param input payment_date: Fechas tipo string que indica el dia que se realiza el pago.
 * @return Booleano que indica 1 si el pago estuvo a tiempo, de lo contrario retorna un 0.
 */
bool verifyDate(std::string due_date, std::string payment_date);    // Funcion general

/**
 * @brief Funcion que formatea un double a una precision de decimales que se le especifique
 * convirtiendo dicho formato a string.
 * @param input value: double que indica la cantidad a formatear.
 * @param input precision: int que indica la cantidad de decimales a mostrar.
 * @return String equivalente al valor double formateado.
 */
std::string to_string_with_precision(double value, int precision);  // Funcion general

/**
 * @brief Funcion que se encarga de revisar la entrada de un usuario
 * para validar su opcion en el menu.
 * @param input Entrada tipo string recibida del usuario
 * @return Un valor entero fuera del rango de las opciones permitidas
 * del menu
 */
std::map<std::string, std::string> calculateLoan();                 // FUncion del menu principal



/**
 * @brief Funcion que se encarga de revisar la entrada de un usuario
 * para validar su opcion en el menu.
 * @param input Entrada tipo string recibida del usuario
 * @return Un valor entero fuera del rango de las opciones permitidas
 * del menu
 */
std::map<std::string, std::string> calculateCDP();                 // FUncion del menu principal



#endif // FUNCIONES_HPP