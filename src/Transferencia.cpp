#include "Transferencia.hpp"
#include <iostream>

Transferencia::Transferencia(int id, double monto, const std::string& moneda, const std::string& detalle,
               int cuentaOrigen, int cuentaDestino, double balanceAnterior, double balancePosterior)
    : Transaccion(id, monto, moneda, detalle), cuentaOrigen(cuentaOrigen), cuentaDestino(cuentaDestino),
      balanceAnterior(balanceAnterior), balancePosterior(balancePosterior) {}

void Transferencia::ejecutar() {
  std::cout << "Realizando transferencia de " << monto << " " << moneda
              << " desde la cuenta " << cuentaOrigen << " a la cuenta " << cuentaDestino
              << ". Balance anterior: " << balanceAnterior
              << ", Balance posterior: " << balancePosterior << std::endl;
            // Implementación para actualizar base de datos
}

void Transferencia::solicitudInformacion() {
  // Solicitar tipo de transferencia
  std::cout << "¿Desea realizar una transferencia entre cuentas de la misma moneda (1) o diferente moneda (2)?: ";
  int tipoTransferencia;
  std::cin >> tipoTransferencia;

  // Obtener datos de las cuentas
  int idCliente, numeroCuentaOrigen, numeroCuentaDestino;
  double monto;
  std::string moneda;
  std::string detalle;

  // Solicitar datos para la transferencia
  std::cout << "Ingrese ID del cliente: ";
  std::cin >> idCliente;
  std::cout << "Ingrese número de cuenta de origen: ";
  std::cin >> numeroCuentaOrigen;
  std::cout << "Ingrese número de cuenta de destino: ";
  std::cin >> numeroCuentaDestino;
  std::cout << "Ingrese monto a transferir: ";
  std::cin >> monto;
  std::cout << "Ingrese moneda (CRC o USD): ";
  std::cin >> moneda;
  std::cout << "Ingrese detalle de la transferencia: ";
  std::getline(std::cin, detalle);

}
