/**
 * @file Deposito.hpp
 * 
 * @brief Clase Deposito
 * 
 * Esta clase representa una transacción de depósito.
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

#ifndef DEPOSITO_HPP
#define DEPOSITO_HPP

#include "Transaccion.hpp"


/**
 * @brief Clase Deposito
 * 
 * Esta clase representa una transacción de depósito.
 * 
*/
class Deposito : public Transaccion {
private:
    int cuentaDestino;
    double balanceAnterior;
    double balancePosterior;

public:

    /**
     * @brief Constructor de la clase Deposito
     * 
     * @param id_client ID del cliente que realiza la transacción
     * @param db Referencia a un objeto de la clase DBManager
    
    */
    Deposito(int id_client, DBManager& db);
    // Se implementa el método de depósito

    /**
     * @brief Método que ejecuta la transacción de depósito
     * 
     * Este método ejecuta la transacción de depósito.
    */
    void ejecutar() override; 
};

#endif // DEPOSITO_HPP


