#include "Transaccion.hpp"
#include <iostream>
using namespace std;


// Constructor
Transaccion::Transaccion(int id_client, DBManager& db) : id_client(id_client), db(db) {};