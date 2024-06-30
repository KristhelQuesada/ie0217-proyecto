#include "Prestamo.hpp"
#include "Funciones.hpp"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

enum loanFilters {
    ID_FILTER = 1,
    LOANTYPE_FILTER,
    YEAR_FILTER,
    CURRENCY_FILTER,
    MAX_FILTER // para saber cuantas opciones tenemos
};



/*
------------------------------------------------------------------
             Funcion que permite crear un prestamo
------------------------------------------------------------------
*/
Prestamo::Prestamo(int id_client, DBManager& db) : id_client(id_client), db(db) {};



/*
------------------------------------------------------------------
             Funcion que permite crear un prestamo
------------------------------------------------------------------
*/
void Prestamo::createLoan() {
    // Variables
    string final_query;
    stringstream query;
    map<string, string> data = calculateLoan();

    // Verificar si el mapa data está vacío, lo cual indica que el usuario seleccionó salir
    if (data.empty()) {
        cout << "Operación cancelada. No se creó ningún préstamo." << endl;
        return;
    }

    // Crear el query
    query << "INSERT INTO Loan(id_client, loan_term, id_loan_type, currency, principal, "
          << "interest_rate, monthly_payment, total_repayment, actual_debt) VALUES ("
          << this->id_client << ", "
          << data["loan_term"] << ", '"
          << data["id_loan_type"] << "', '"
          << data["currency"] << "', "
          << data["principal"] << ", "
          << data["interest_rate"] << ", "
          << data["monthly_payment"] << ", "
          << data["total_repayment"] << ", "
          << data["total_repayment"] << ");"; // al inicio actual_debt = total_repayment
    final_query = query.str();                // pasa el objeto stringstream -> string

    // Ejecución del query con manejo de excepciones
    try {
        db.ejecutarSQL(final_query);
        cout << "\nEl préstamo ha sido creado con éxito!" << endl;
    } catch (const std::exception& e) {
        cerr << "Error al crear el préstamo: " << e.what() << endl;
    }
}




/*
------------------------------------------------------------------
    Funcion que despliega la informacion actual de todos los
                prestamos asociados al cliente
------------------------------------------------------------------
*/
void Prestamo::viewAll() {
    // Variables y mensaje inicial
    string final_query;
    stringstream query;
    cout << "\n\n>> Lista de Prestamos" << endl;

    // Creacion del query
    query << "SELECT * FROM Loan "
          << "WHERE id_client=" << this->id_client << ";";

    final_query = query.str();

    // Ejecucion del query
    db.desplegarPrestamos(final_query);
}



/*
------------------------------------------------------------------
    Funcion que muestra los prestamos del cliente asociados
              a un filtro o busqueda especifica
------------------------------------------------------------------
*/
void Prestamo::searchLoans() {
    // Delcaracion de variables
    int option;
    string input, filter, final_query;
    std::stringstream query;

    // Inicializacion de variables
    string initialPrompt = "SELECT * FROM Loan WHERE id_client=";


    // Metodo de busqueda
    cout << "=========== Filtro de Busqueda ===========" << endl;
    cout << "   1. ID del prestamo" << endl;
    cout << "   2. Tipo de prestamo" << endl;
    cout << "   3. Anio de creacion" << endl;
    cout << "   4. Divisa" << endl;
    cout << "   Desea buscar sus prestamos por:";
    cin >> input;
    cout << "==========================================" << endl;
    option = verifyMenuOption(input, MAX_FILTER);
    cin.ignore();


    // Retorno de query segun la busqueda
    switch (option) {
        case ID_FILTER:
            cout << "Indique el ID del prestamo: ";
            cin >> filter;
            cin.ignore();
            query << initialPrompt << this->id_client
                  << " AND id_loan=" << filter << ";";
            break;


        case LOANTYPE_FILTER:
            cout << "Indique el tipo de prestamo [PE/PR/HP]: ";
            cin >> filter;
            cin.ignore();
            query << initialPrompt << this->id_client
                  << " AND id_loan_type='" << filter << "';";
            break;


        case YEAR_FILTER:
        cout << "Indique el anio de creacion del prestamo: ";
            cin >> filter;
            cin.ignore();
            query << initialPrompt << this->id_client
                  << " AND YEAR(creation_date)=" << filter << ";";
            break;


        case CURRENCY_FILTER:
            cout << "Indique la divisa del prestamo: ";
            cin >> filter;
            cin.ignore();
            query << initialPrompt << this->id_client
                  << " AND currency=" << filter << ";";
            break;


        default:
            cout << "La opcion para el filtro de busqueda ingresado no es valida." << endl;
            break;
    }

    final_query = query.str();

    // Ejecucion del query
    db.desplegarPrestamos(final_query);
    
}