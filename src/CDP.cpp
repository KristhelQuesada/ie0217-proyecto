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
CDP::CDP(int id_account, DBManager& db) : id_account(id_account), db(db) {
    string id_account_str = to_string(id_account);

    relatedInfo["id_deposit_certificate"] = "";
    relatedInfo["id_account"] = id_account_str;
    relatedInfo["cdp_term"] = "";
    relatedInfo["deadline"] = "";
    relatedInfo["principal"] = "";
    relatedInfo["interest_rate"] = "";
    relatedInfo["capitalization_freq"] = "";
    relatedInfo["interest_penalty"] = "";
    relatedInfo["final_amount"] = "";
};

// METODO QUE PERMITE CREAR UN CERTIFICADO DE DEPOSITO
void CDP::createCDP() {
    // Variables
    string final_query;
    stringstream query;
    map<string, string> data = calculateCDP();

    // Creacion del query
    query << "INSERT INTO DepositCertificate(id_account, deadline, principal, interest_rate, "
          << "capitalization_freq, interest_penalty, final_amount) VALUES ("
          << this->id_account << ", '"
          << data["deadline"] << "', "
          << data["principal"] << ", "
          << data["interest_rate"] << ", "
          << data["capitalization_freq"] << ", "
          << data["interest_penalty"] << ", "
          << data["final_amount"] << ");";
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
    query << "SELECT * FROM DepositCertificate "
          << "WHERE id_client=" << this->id_account << ";";

    final_query = query.str();

    // Ejecucion del query
    db.desplegarCDP(final_query);
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
            query << "SELECT * FROM DepositCertificate WHERE id_account=" << this->id_account
                  << " AND id_deposit_certificate=" << filter << ";";
            break;
        case YEAR_FILTER:
            cout << "Indique el anio de creacion del CDP: ";
            cin >> filter;
            cin.ignore();
            query << "SELECT * FROM DepositCertificate WHERE id_account=" << this->id_account
                  << " AND YEAR(deadline)=" << filter << ";";
            break;
        default:
            cout << "La opcion para el filtro de busqueda ingresado no es valida." << endl;
            break;
    }

    final_query = query.str();

    // Ejecucion del query
    db.desplegarCDP(final_query);
}