#include "CDP.hpp"
#include "Funciones.hpp"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

enum cdpFilters {
    ID_FILTER = 1,
    YEAR_FILTER,
    MAX_FILTER // para saber cuantas opciones tenemos
};

// CONSTRUCTOR DE LA CLASE CDP
CDP::CDP(int id_client, DBManager& db) : id_client(id_client), db(db) {
    string id_client_str = to_string(id_client);

    relatedInfo["id_cdp"]         = "";
    relatedInfo["id_client"]      = id_client_str;
    relatedInfo["creation_date"]  = "";
    relatedInfo["maturity_date"]  = "";
    relatedInfo["interest_rate"]  = "";
    relatedInfo["principal"]      = "";
    relatedInfo["total_repayment"]= "";
};

// METODO QUE PERMITE CREAR UN CERTIFICADO DE DEPOSITO
void CDP::createCDP() {
    // Variables
    string final_query;
    stringstream query;
    map<string, string> data = calculateCDP();

    // Creacion del query
    query << "INSERT INTO CDP(id_client, creation_date, maturity_date, interest_rate, principal, "
          << "total_repayment) VALUES ("
          << this->id_client << ", '"
          << data["creation_date"] << "', '"
          << data["maturity_date"] << "', "
          << data["interest_rate"] << ", "
          << data["principal"] << ", "
          << data["total_repayment"] << ");";
    final_query = query.str(); // pasa el objeto stringstream -> string

    // Ejecucion del query
    db.ejecutarSQL(final_query);
}

// METODO QUE MUESTRA LA INFORMACION ACTUAL DE TODOS LOS CDP ASOCIADOS AL CLIENTE
void CDP::viewAll() {
    // Variables y mensaje inicial
    string final_query;
    stringstream query;
    cout << "\n\n>> Lista de Certificados de Depósito" << endl;

    // Creacion del query
    query << "SELECT * FROM CDP "
          << "WHERE id_client=" << this->id_client << ";";

    final_query = query.str();

    // Ejecucion del query
    db.ejecutarConsulta(final_query, this->relatedInfo);
}

// METODO QUE MUESTRA LA INFORMACION ACTUAL RELACIONADA A UN SOLO CDP
void CDP::searchCDP() {
    // Variables
    int option;
    string input, filter, final_query;
    stringstream query;

    // Metodo de busqueda
    cout << "------------------------------------------" << endl;
    cout << "            Filtro de Busqueda            " << endl;
    cout << "------------------------------------------" << endl;
    cout << "1. ID del CDP" << endl;
    cout << "2. Anio de creacion" << endl;
    cout << "Desea buscar sus CDP por: ";
    cin >> input;
    cout << "------------------------------------------" << endl;
    option = verifyMenuOption(input, MAX_FILTER);
    cin.ignore();

    // Retorno de query segun la busqueda
    switch (option) {
        case ID_FILTER:
            cout << "Indique el ID del CDP: ";
            cin >> filter;
            cin.ignore();
            query << "SELECT * FROM CDP WHERE id_client=" << this->id_client
                  << " AND id_cdp=" << filter << ";";
            break;
        case YEAR_FILTER:
            cout << "Indique el anio de creacion del CDP: ";
            cin >> filter;
            cin.ignore();
            query << "SELECT * FROM CDP WHERE id_client=" << this->id_client
                  << " AND YEAR(creation_date)=" << filter << ";";
            break;
        default:
            cout << "La opcion para el filtro de busqueda ingresado no es valida." << endl;
            break;
    }

    final_query = query.str();

    // Ejecucion del query
    db.ejecutarConsulta(final_query, this->relatedInfo);
}
