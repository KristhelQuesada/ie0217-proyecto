#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

template<typename T>
class Cliente {
private:
    std::unordered_map<std::string, T> informacion;
    
public:
    Cliente(int idCliente, const std::string& nombre, const std::string& apellido);
    void obtenerInformacion();
    void actualizarDatos();
};

#endif // CLIENTE_HPP