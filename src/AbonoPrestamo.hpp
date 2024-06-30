/**
 *
 * Proyecto IIE0217
 * 
 * @file AbonoPrestamo.hpp
 * @brief Archivo de cabecera de la clase AbonoPrestamo
 * 
 * Esta clase representa una transacción de abono a un préstamo.
 * 
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


#ifndef ABONO_PRESTAMO_HPP
#define ABONO_PRESTAMO_HPP

#include "Transaccion.hpp"
#include <string>

/**
 * @brief Clase AbonoPrestamo
 * 
 * Esta clase representa una transacción de abono a un préstamo.
 * 
*/
class AbonoPrestamo : public Transaccion {
private:
    std::map<std::string, std::string> loanData;
    std::map<std::string, std::string> lastPayment;
    std::map<std::string, std::string> accountData;

public:

    /**
     * @brief Constructor de la clase AbonoPrestamo
     * 
     * @param id_client ID del cliente que realiza la transacción
     * @param db Referencia a un objeto de la clase DBManager
    */
    AbonoPrestamo(int id_client, DBManager& db);

    /**
     * @brief Método para ejecutar la transacción de abono a un préstamo
     * 
     * Este método ejecuta la transacción de abono a un préstamo.
    */
    void ejecutar() override; // Implementa el método de depósito

    // Funciones de calculo

    /**
     * @brief Método para calcular la fecha de vencimiento de un préstamo
     * 
     * Este método calcula la fecha de vencimiento de un préstamo.
     * @return Fecha de vencimiento del préstamo
    */
    std::string calcularDueDate();

    /**
     * @brief Método para calcular el monto de la cuota de un préstamo
     * 
     * @param capitalPagado Monto del capital pagado
     * @param principal Monto del principal
     * @param interes Monto del interés
     * 
     * Este método calcula el monto de la cuota de un préstamo.
     * @return Monto de la cuota del préstamo
    */
    double interesAmortizacion(double capitalPagado,
                               double principal, double interes);

    // Funciones de extraccion de datos

    /**
     * @brief Método para extraer datos de un préstamo
     * 
     * @param loanID ID del préstamo
    */
    void extraerDatos(std::string& loanID);

    /**
     * @brief Método para setear las columnas de la tabla de préstamos
     * 
     * Este método setea las columnas de la tabla de préstamos.
    */
    void setColumnas();

    // Funciones de verificacion

    /**
     * @brief Método para verificar la existencia de un préstamo
     * 
     * Este método verifica la existencia de un préstamo.
    */
    bool verificarExistencia();

    /**
     * @brief Método para verificar la puntualidad de un préstamo
     * 
     * Este método verifica la puntualidad de un préstamo.
    */
    bool verificarPuntualidad();

    bool confirmarMetodoDePago();

    double getNewBalanceAccount(const double& pago);
    double getCurrencyChange(const string& divisaPrestamo);
    bool AbonoPrestamo::confirmarFondos(const double& pagoConv);

};

#endif // ABONO_PRESTAMO_HPP
