/**
 * @file Transferencia.hpp
 * 
 * @brief Clase Transferencia
 * 
 * Esta clase representa una transacción de transferencia entre cuentas.
 * 
 * MIT License
 * 
 * Copyright (c) 2024 Oscar Porras Silesky / Kristhel Quesada Lopez / Antony Brenes Rodriguez
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

#ifndef TRANSFERENCIA_HPP
#define TRANSFERENCIA_HPP

#include "Transaccion.hpp"
#include "DBManager.hpp"


/**
 * @brief Clase Transferencia
 * 
 * Esta clase representa una transacción de transferencia entre cuentas.
 * 
*/
class Transferencia : public Transaccion {
private:
    
    double monto;
    int cuentaOrigen, cuentaDestino;
    std::string monedaOrigen, monedaDestino;
    double balanceAnterior, balancePosterior;

public:
    // Constructor

    /**
     * @brief Constructor de la clase Transferencia
     * 
     * @param id_client ID del cliente
     * @param db Referencia a un objeto de la clase DBManager
     * 
     * Constructor de la clase Transferencia
    */
    Transferencia(int id_client, DBManager& db);

    // Implementa el método de transferencia

    /**
     * @brief Método que ejecuta la transacción de transferencia
     * 
     * Este método ejecuta la transacción de transferencia.
    */
    void ejecutar() override;

};

#endif // TRANSFERENCIA_HPP