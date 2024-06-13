#ifndef CUENTA_HPP
#define CUENTA_HPP

#include <unordered_map>
#include <string>
#include <ctime>

template<typename T>
class Cuenta {

private:
    std::unordered_map<std::string, T> detallesCuenta;

public:
    Cuenta(int idCuenta, const std::string& tipoCuenta, const std::string& moneda, double saldo, 
        const std::string& estado, const std::tm& fechaApertura);
    void obtenerInformacion();
    void actualizarDatos();

};

#endif // CUENTA_HPP
