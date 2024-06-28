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

std::pair<float, float> getInterestRateRange(const string& loanType) {
    if (loanType == "HP") { // Préstamos Hipotecarios
        return {0.10, 0.12};
    } else if (loanType == "PR") { // Préstamos Prendarios
        return {0.15, 0.18};
    } else if (loanType == "PE") { // Préstamos Personales
        return {0.20, 0.25};
    } else {
        throw std::invalid_argument("Tipo de préstamo no válido");
    }
}

// CONSTRUCTOR DE LA CLASE PRESTAMO
Prestamo::Prestamo(int id_client, DBManager& db) : id_client(id_client), db(db) {
    string id_client_str = to_string(id_client);

    relatedInfo["id_loan"]         = "ID Prestamo";
    relatedInfo["id_client"]       = "ID Cliente";
    relatedInfo["loan_term"]       = "Plazo";
    relatedInfo["creation_date"]   = "Fecha de Creacion";
    relatedInfo["id_loan_type"]    = "Tipo de Prestamo";
    relatedInfo["currency"]        = "Divisa";
    relatedInfo["principal"]       = "Monto Solicitado";
    relatedInfo["interest_rate"]   = "Tasa de Interés";
    relatedInfo["monthly_payment"] = "Cuota Mensual";
    relatedInfo["total_repayment"] = "Monto total a pagar";
    relatedInfo["actual_debt"]     = "Monto actual pagado";
};



// METODO QUE PERMITE CREAR UN TIPO DE PRESTAMO
void Prestamo::createLoan() {
    // Variables
    string final_query;
    stringstream query;
    map<string, string> data = calculateLoan();
    
    // Obtener el rango de tasas de interés basado en el tipo de préstamo
    auto interestRateRange = getInterestRateRange(data["id_loan_type"]);
    float defaultInterestRate = (interestRateRange.first + interestRateRange.second) / 2;
    
    // Solicitar al usuario que seleccione una tasa de interés
    float interestRate;
    cout << "Seleccione una tasa de interés entre " << interestRateRange.first * 100 << "% y " 
         << interestRateRange.second * 100 << "% (deje en blanco para usar la tasa predeterminada de " 
         << defaultInterestRate * 100 << "%): ";
    string input;
    getline(cin, input);
    
    if (input.empty()) {
        interestRate = defaultInterestRate;
    } else {
        interestRate = stof(input) / 100.0;
        if (interestRate < interestRateRange.first || interestRate > interestRateRange.second) {
            cout << "La tasa de interés seleccionada está fuera del rango permitido. Usando la tasa predeterminada de " 
                 << defaultInterestRate * 100 << "%." << endl;
            interestRate = defaultInterestRate;
        }
    }
    
    // Crear el query
    query << "INSERT INTO Loan(id_client, loan_term, id_loan_type, currency, principal, "
          << "interest_rate, monthly_payment, total_repayment, actual_debt) VALUES ("
          << this->id_client << ", "
          << data["loan_term"] << ", '"
          << data["id_loan_type"] << "', '"
          << data["currency"] << "', "
          << data["principal"] << ", "
          << interestRate << ", "
          << data["monthly_payment"] << ", "
          << data["total_repayment"] << ", "
          << data["total_repayment"] << ");"; // al inicio actual_debt = total_repayment
    final_query = query.str();                // pasa el objeto stringstream -> string

    // Ejecución del query
    db.ejecutarSQL(final_query);
    cout << "\nEl préstamo ha sido creado con éxito!" <<  endl;
}

// METODO QUE MUESTRA LA INFORMACION ACTUAL DE TODOS LOS PRESTAMOS ASOCIADOS AL CLIENTE
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



// METODO QUE MUESTRA LA INFORMACION ACTUAL RELACIONADA A UN SOLO PRESTAMO
void Prestamo::searchLoans() {
    // Variables
    int option;
    string input, filter, final_query;
    std::stringstream query;


    // Metodo de busqueda
    cout << "------------------------------------------" << endl;
    cout << "            Filtro de Busqueda            " << endl;
    cout << "------------------------------------------" << endl;
    cout << "1. ID del prestamo" << endl;
    cout << "2. Tipo de prestamo" << endl;
    cout << "3. Anio de creacion" << endl;
    cout << "4. Divisa" << endl;
    cout << "Desea buscar sus prestamos por:";
    cin >> input;
    cout << "------------------------------------------" << endl;
    option = verifyMenuOption(input, MAX_FILTER);
    cin.ignore();


    // Retorno de query segun la busqueda
    switch (option) {
        case ID_FILTER:
            cout << "Indique el ID del prestamo: ";
            cin >> filter;
            cin.ignore();
            query << "SELECT * FROM Loan WHERE id_client=" << this->id_client
                  << " AND id_loan=" << filter << ";";
            break;
        case LOANTYPE_FILTER:
            cout << "Indique el tipo de prestamo [PE/PR/HP]: ";
            cin >> filter;
            cin.ignore();
            query << "SELECT * FROM Loan WHERE id_client=" << this->id_client
                  << " AND id_loan_type='" << filter << "';";
            break;
        case YEAR_FILTER:
        cout << "Indique el anio de creacion del prestamo: ";
            cin >> filter;
            cin.ignore();
            query << "SELECT * FROM Loan WHERE id_client=" << this->id_client
                  << " AND YEAR(creation_date)=" << filter << ";";
            break;
        case CURRENCY_FILTER:
            cout << "Indique la divisa del prestamo: ";
            cin >> filter;
            cin.ignore();
            query << "SELECT * FROM Loan WHERE id_client=" << this->id_client
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


void Prestamo::extractOneData() {
    string columna = "principal";
    std::stringstream query;
    string data, final_query;

    // Construccion del query
    query << "SELECT " << columna 
          << " FROM Loan WHERE id_client=" 
          << this->id_client;
    

    // Fin de la funcion
    final_query = query.str();
    data = db.ejecutarConsulta(final_query, columna);
    cout << "Data de OneData: " << data << endl;
}


void Prestamo::extractAllData() {
    std::stringstream query;
    std::string loanID, final_query;

    cout << "Seleccione el ID del Prestamos: ";
    cin >> loanID;
    cin.ignore();

    // Construccion del query
    query << "SELECT * FROM Loan WHERE id_loan=" 
          << loanID;
    

    // Fin de la funcion
    final_query = query.str();
    this->loadedValues = db.cargarDatos(final_query, this->relatedInfo);
    
    // Imprimir datos
    for (const auto& pair : this->loadedValues) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}