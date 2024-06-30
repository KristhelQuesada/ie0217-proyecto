/**
 * @file Sistema.hpp
 * 
 * @brief Clase Sistema
 * 
 * Esta clase representa el sistema de un banco, con sus respectivas
 * funcionalidades y datos asociados.
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

#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
#include "Cliente.hpp"
#include "Cuenta.hpp"
#include "Prestamo.hpp"
#include "Transaccion.hpp"
#include "DBManager.hpp"


/**
 * @brief Clase Sistema
 * 
 * Esta clase representa el sistema de un banco, con sus respectivas
 * funcionalidades y datos asociados.
*/
class Sistema {
private:
    std::string database;
    DBManager dbManager;

public:

    /**
     * @brief Constructor de la clase Sistema
     * 
     * @param dbPath Ruta de la base de datos
     * 
     * Constructor de la clase Sistema
    */
    Sistema(const std::string& dbPath);

};

#endif // SISTEMA_HPP
