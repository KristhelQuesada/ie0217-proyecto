/**
 * @brief Clase abstracta Transaccion
 * 
 * Esta clase representa una transacción bancaria.
 * 
 * Las clases derivadas de esta clase deben implementar el método ejecutar().
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

#ifndef TRANSACCION_HPP
#define TRANSACCION_HPP

#include "DBManager.hpp"


/**
 * @brief Clase abstracta Transaccion
 * 
 * Esta clase representa una transacción bancaria.
 * 
 * Las clases derivadas de esta clase deben implementar el método ejecutar().
*/
class Transaccion {
protected:
    int id_client;
    DBManager& db;

public:

    /**
     * @brief Constructor de la clase Transaccion
     * 
     * @param id_client ID del cliente
     * @param db Referencia a un objeto de la clase DBManager
     * 
     * Constructor de la clase Transaccion
    */
    Transaccion(int id_client, DBManager& db);

    /**
     * @brief Método para ejecutar la transacción
     *
     * Método virtual puro para ser implementado por clases derivadas
     *  
    */
    virtual void ejecutar() = 0; // Método virtual puro para ser implementado por clases derivadas
};

#endif // TRANSACCION_HPP