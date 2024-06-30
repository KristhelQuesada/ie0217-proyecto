/**
 * @file Cliente.hpp
 * 
 * @brief Clase Cliente que representa un cliente de un banco.
 * 
 * Esta clase representa un cliente de un banco, con sus respectivos
 * datos personales y cuentas asociadas.
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

#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include <iostream>

#include "DBManager.hpp"


/**
 * @brief Clase Cliente
 * 
 * Esta clase representa un cliente de un banco, con sus respectivos
 * datos personales y cuentas asociadas.
 * 
*/
class Cliente {
private:
  std::string nombre;
  int idCliente;
  std::string apellido;
  int idCuentaColones;
  int idCuentaDolares;
  

public:

  // Constructor por defecto
  Cliente();

  // Constructor para inicializar un cliente

  /**
   * @brief Constructor de la clase Cliente
   * 
   * @param idCliente ID del cliente
   * @param nombre Nombre del cliente
   * @param apellido Apellido del cliente
   * @param idCuentaColones ID de la cuenta en colones
   * @param idCuentaDolares ID de la cuenta en dólares
   * 
   * Este constructor inicializa un objeto de la clase Cliente.
  */
  Cliente(int idCliente, const std::string& nombre, const std::string& apellido, int idCuentaColones, int idCuentaDolares);

  // Método para solicitar datos al usuario e inicializar el objeto

  /**
   * @brief Método para solicitar datos al usuario e inicializar el objeto
   * 
   * @param dbManager Referencia a un objeto de la clase DBManager
   * 
   * Este método solicita al usuario los datos necesarios para inicializar
   * un objeto de la clase Cliente.
  */
  void obtenerInformacion(DBManager& dbManager);

  // Método que imprime datos d eun cliente

  /**
   * @brief Método para imprimir los datos de un cliente
   * 
   * @param dbManager Referencia a un objeto de la clase DBManager
   * 
   * Este método imprime los datos de un cliente.
   *
  */
  void imprimirDatos(DBManager& dbManager);

  // Método para actualizar nombre y apellido del cliente

  /**
   * @brief Método para actualizar el nombre y apellido de un cliente
   * 
   * @param dbManager Referencia a un objeto de la clase DBManager
   * 
   * Este método solicita al usuario los datos necesarios para actualizar
   * el nombre y apellido de un cliente. Asimismo, se actualiza
   * el ID.
  */
  void actualizarDatos(DBManager& dbManager);

  // Metodo que elimina un cliente

  /**
   * @brief Método para eliminar un cliente
   * 
   * @param dbManager Referencia a un objeto de la clase DBManager
   * 
   * Este método elimina un cliente de la base de datos.
  */
  void eliminarCliente(DBManager& dbManager);
  
};

#endif // CLIENTE_HPP