#include "AbonoPrestamo.hpp"
#include <iostream>
using namespace std;

// Constructor
Prestamo::Prestamo(double montoPrestamo, int cuotasMeses, int interesAplicado, 
                   double montoPorCuota, double montoTotalPagar, double montoPorPagar)
    : montoPrestamo(montoPrestamo), cuotasMeses(cuotasMeses), interesAplicado(interesAplicado),
      montoPorCuota(montoPorCuota), montoTotalPagar(montoTotalPagar), montoPorPagar(montoPorPagar) {}

// calcula el metodo de pago del prestamo
void Prestamo::calcularPago(double solicitedLoan, int interes, int payments) {
    cout << "La metodologia de pago para el monto de " << solicitedLoan
         << "a " << interes << "% de intereses y en " << payments << "cuotas"
         << "es de: " << endl;
}

// muestra la informacion de la cuota realizada
void Prestamo::obtenerInfo() {    // despliega la informacion asociada al prestamo
    cout << "El estado actual del prestamo es: " << endl;
}