/**
 * @file CDP.hpp
 * 
 * @brief Archivo que contiene la definicion de la clase CDP
 * 
 * Esta clase representa un Certificado de Depósito (CDP).
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


#ifndef CDP_HPP
#define CDP_HPP

#include "DBManager.hpp"

/**
 * @brief Clase CDP
 * 
 * Esta clase representa un Certificado de Depósito (CDP).
 * 
*/
class CDP {
private:
    int id_account;
    int id_client;
    DBManager& db;
    // Atributo que contiene la informacion de un cdp en especifico
    std::map<std::string, std::string> relatedInfo;
    
public:

    /**
     * @brief Constructor de la clase CDP
     * 
     * @param id_client ID del cliente que realiza la transacción
     * @param db Referencia a un objeto de la clase DBManager
    */
    CDP(int id_client, DBManager& db);

    // Metodos funcionalidad

    /**
     * @brief Metodo para crear un CDP
     * 
     * Este metodo solicita al usuario los datos necesarios para
     * crear un CDP y lo inserta en la base de datos.
     * 
    */
    void createCDP();

    /**
     * @brief Metodo para ver todos los CDP
     * 
     * Este metodo imprime en pantalla todos los CDP 
     * de un cliente.
    */
    void viewAll();

    /**
     * @brief Metodo para buscar un CDP
     * 
     * Este metodo solicita al usuario el ID de un CDP
     * y muestra en pantalla la informacion de ese CDP.
    */
    void searchCDP();
};

#endif // CDP_HPP