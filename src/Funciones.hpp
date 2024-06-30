/**
 * @file Funciones.hpp
 * 
 * @brief Funciones de utilidad para el manejo de datos y menus
 * 
 * Este archivo contiene las funciones de utilidad que se utilizan
 * en el manejo de datos y menus de la aplicacion.
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