#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>
#include <iostream>

#include "DBManager.hpp"

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
  Cliente(int idCliente, const std::string& nombre, const std::string& apellido, int idCuentaColones, int idCuentaDolares);

  // Método para solicitar datos al usuario e inicializar el objeto
  void obtenerInformacion(DBManager& dbManager);

  // Método que imprime datos d eun cliente
  void imprimirDatos(DBManager& dbManager);

  // Método para actualizar nombre y apellido del cliente
  void actualizarDatos(DBManager& dbManager);

  // Metodo que elimina un cliente
  void eliminarCliente(DBManager& dbManager);
  
};

#endif // CLIENTE_HPP