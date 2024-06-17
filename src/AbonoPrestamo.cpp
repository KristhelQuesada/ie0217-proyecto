#include "AbonoPrestamo.hpp"
#include "Funciones.hpp"
#include <iostream>
#include <string>
using namespace std;

// Constructor
AbonoPrestamo::AbonoPrestamo(int id_cliente, DBManager& db) 
    : Transaccion(id_cliente, db) {}

// Funcion que ejecuta el abono
void AbonoPrestamo::ejecutar() {
  string getCurDate, getLoanDate, query, final_query;
  bool isOnTime;

  // Verifica fecha para saber si se cobra multa
  //getCurDate = db.ejecutarConsulta("SELECT CURDATE() AS current_date");
  //getLoanDate = db.ejecutarConsulta()
  //isOnTime = veru

  cout << "Im working";

  // Imprime monto total de la cuota
  // Solicita monto
  // Query de ejecucion que debe hacer transaccion y actualizar actual_debt todo mediante
  // un transaction
}