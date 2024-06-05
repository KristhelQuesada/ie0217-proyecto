#ifndef PRESTAMO
#define PRESTAMO

class Prestamo {
private:
    double montoPrestamo;
    int cuotasMeses;
    int interesAplicado;
    double montoPorCuota;
    double montoTotalPagar;
    double montoPorPagar;

public:
    Prestamo(double montoPrestamo, int cuotasMeses, int interesAplicado,
             double montoPorCuota, double montoTotalPagar, double montoPorPagar);

    void calcularPago(double solicitedLoan, int interes, int payments);  // calcula el metodo de pago del prestamo
    void obtenerInfo();     // despliega la informacion asociada al prestamo

};

#endif // PRESTAMO_HPP