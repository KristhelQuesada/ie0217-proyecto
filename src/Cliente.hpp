#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

#include "DBManager.hpp"

template<typename T>
class Cliente {
private:
  std::map<std::string, T> informacion; // Mapa para almacenar la información del cliente

public:
  // Constructor para inicializar un cliente
  Cliente(int idCliente, const std::string& nombre, const std::string& apellido, int idCuentaColones, int idCuentaDolares);

  // Métodos para obtener y establecer el ID del cliente
  T getIdCliente() const;
  void setIdCliente(T idCliente);

  // Métodos para obtener y establecer el nombre del cliente
  const std::string& getNombreCliente() const;
  void setNombreCliente(const std::string& nombre);

  // Métodos para obtener y establecer el apellido del cliente
  const std::string& getApellidoCliente() const;
  void setApellidoCliente(const std::string& apellido);

  // Métodos para obtener y establecer el ID de la cuenta en colones
  T getIdCuentaColones() const;
  void setIdCuentaColones(T idCuentaColones);

  // Métodos para obtener y establecer el ID de la cuenta en dólares
  T getIdCuentaDolares() const;
  void setIdCuentaDolares(T idCuentaColones);

  // Método para obtener toda la información del cliente
  std::map<std::string, T> getInformacion() const;

  // Método para solicitar datos al usuario e inicializar el objeto
  void obtenerInformacion();

  // Función para insertar datos en la base de datos
  bool insertarInformacionBaseDeDatos(DBManager& dbManager);
  
  // Método para actualizar nombre y apellido del cliente
  void actualizarDatos(DBManager& dbManager);

  // Método para eliminar datos del cliente
  bool elminarInformacionBaseDeDatos(DBManager& dbManager);
  
};

#endif // CLIENTE_HPP