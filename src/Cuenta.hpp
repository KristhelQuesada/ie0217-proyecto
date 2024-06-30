/**
 * @file Cuenta.hpp
 * 
 * @brief Archivo de cabecera de la clase Cuenta
 * 
 * Este archivo define la clase Cuenta con sus atributos y métodos.
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

#ifndef CUENTA_HPP       // Evalúa si la variable está definida
#define CUENTA_HPP       // Define una variable si no la hay

#include <string>        // Manejo de cadenas de caracteres
#include <ctime>         // Funciones relacionadas con el tiempo
#include <iostream>      // Mostrar información en consola

#include "DBManager.hpp" // Manejo de la conexión a la base de datos

// Clase que crea un objeto cuenta

/**
 * @brief Clase Cuenta
 * 
 * Esta clase representa una cuenta de un cliente en un banco.
 * 
*/
class Cuenta {
private:

    // Atributos
    int idCliente;
    int idCuenta;
    double saldo;
    std::string moneda;
    std::string fechaApertura;
   

public:

    // Constructor por defecto
    Cuenta();

    // Constructor para inicializar una cuenta

    /**
     * @brief Constructor de la clase Cuenta
     * 
     * @param idCliente ID del cliente al que pertenece la cuenta
     * 
     * @param idCuenta ID de la cuenta
     * 
     * @param moneda Tipo de moneda de la cuenta
     * 
     * @param saldo Saldo de la cuenta
     * 
     * @param fechaApertura Fecha de apertura de la cuenta
     * 
     * Este constructor inicializa un objeto de la clase Cuenta.
     * 
    */
    Cuenta(int idCliente, int idCuenta, const std::string& moneda, double saldo, const std::string& fechaApertura);

    // Método para obtener información detallada de la cuenta

    /**
     * @brief Método para obtener información detallada de la cuenta
     * 
     * @param dbManager Referencia a un objeto de la clase DBManager
     * 
     * Este método obtiene información detallada de la cuenta.
     * 
    */
    void obtenerInformacion(DBManager& dbManager);

    // Método para eliminar cuenta

    /**
     * @brief Método para eliminar cuenta
     * 
     * @param dbManager Referencia a un objeto de la clase DBManager
     * 
     * Este método elimina una cuenta.
     * 
    */
    void eliminarCuenta(DBManager& dbManager);
};

#endif // CUENTA_HPP