/**
 * @file Prestamo.hpp
 * 
 * @brief Clase Prestamo 
 * 
 * Esta clase representa un préstamo de un cliente.
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

#ifndef PRESTAMO_HPP
#define PRESTAMO_HPP

#include "DBManager.hpp"

/**
 * @brief Clase Prestamo
 * 
 * Esta clase representa un préstamo de un cliente.
 * 
*/
class Prestamo {
private:
    int id_client;
    DBManager& db;
    // Atributo que contiene la informacion de un prestams en especifico
    std::map<std::string, std::string> loadedValues;

public:

    /**
     * @brief Constructor de la clase Prestamo
     * 
     * @param id_client ID del cliente que realiza la transacción
     * @param db Referencia a un objeto de la clase DBManager
     * 
     * Constructor de la clase Prestamo
    */
    Prestamo(int id_client, DBManager& db);

    // Metodos funcionalidad

    /**
     * @brief Método que crea un préstamo
     * 
     * Este método crea un préstamo.
    */
    void createLoan();

    /**
     * @brief Método que muestra los prestamos de un cliente
     * 
     * Este método muestra todos los prestamos de un cliente.
    */
    void viewAll();

    /**
     * @brief Método que muestra los prestamos de un cliente
     * 
     * Este método filtra los prestamos de un cliente.
    */
    void searchLoans();
};

#endif // PRESTAMO_HPP