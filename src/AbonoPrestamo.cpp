#include "AbonoPrestamo.hpp"
#include "Funciones.hpp"
#include <iostream>
#include <string>
using namespace std;

// Define que contiene la multa que se aplica por atraso
#define MULTA 0.01

// Constructor
AbonoPrestamo::AbonoPrestamo(int id_cliente, DBManager& db) 
    : Transaccion(id_cliente, db) {}

/*
Funcion que ejecuta el abono
*/
void AbonoPrestamo::ejecutar() {
  std:stringstream query;
  string getCurDate, getDueDate, final_query;
  string amount, input, loanID, remaining;
  double amount_sum, actual_debt, cuota;
  double totalCapitalPaid; 
  double totalInterestPaid;
  double plazosCompletados;
  bool isOnTime;
  int multa = MULTA;
  
  // Pregunta el ID del prestamo
  cout << "Ingrese el ID del prestamo: ";
  cin >> loanID;
  cin.ignore();

  // Verificar si hay que pagar aun
  query << "SELECT actual_debt FROM Loan WHERE id_loan=" << loanID;
  remaining = db.ejecutarConsulta(query.str());
  query.str("");

  if (remaining == "0.00") { // if not end and notify
    cout << "\nEl prestamo ya esta pago." << endl;

  } else if (remaining == "") {
    cout << "\nNo existe prestamo asociado al ID Prestamo ingresado" << endl;

  } else {
    // Si hay uqe pagar entonces...
    // Verifica fecha para saber si se cobra multa
    getCurDate = db.ejecutarConsulta("SELECT CURDATE() AS today;");
    getDueDate = calculateDueDate(loanID, db);
    isOnTime = verifyDate(getDueDate, getCurDate);

    query << "SELECT monthly_payment FROM Loan WHERE id_loan=" << loanID;
    amount = db.ejecutarConsulta(query.str());
    query.str("");
    cuota = stod(amount);

    if (isOnTime) {
      amount_sum = stod(amount); // cantidad sumable
    } else {
      amount_sum = stod(amount) + (amount_sum * multa); // multa aplicada
    }



    // Luego de definir el monto a cobrar, Imprime monto total de la cuota y
    // confirma transaccion
    query << "SELECT currency FROM Loan WHERE id_loan=" << loanID;

    cout << "El monto total a pagas es de " << amount_sum << " "
         << db.ejecutarConsulta(query.str()) <<  "\n"
         << "Se continua con el pago? [Y/N]: ";
    cin >> input;
    cin.ignore();
    query.str("");

    if (input == "Y" || input == "y") {
      // Calculo de los montos
      query << "SELECT actual_debt FROM Loan WHERE id_loan=" << loanID;
      double actualDebt = stod(db.ejecutarConsulta(query.str()));
      query.str("");
      double interestPaid = interesAmortizacion(loanID, db);
      double capitalPaid = cuota - interestPaid;

      query << "SELECT loan_term FROM Loan WHERE id_loan=" << loanID;
      double plazo = stod(db.ejecutarConsulta(query.str()));
      query.str("");
      
      query << "SELECT id_payment FROM Payment "
            << "WHERE id_loan=1 ORDER BY id_payment DESC LIMIT 1;";
      string lastPayment = db.ejecutarConsulta(query.str());
      query.str("");
    
      if (lastPayment == "") {
        totalCapitalPaid = capitalPaid;
        totalInterestPaid = interestPaid;
        plazosCompletados = 1;
      } else {
        query << "SELECT total_capital_paid FROM Payment "
              << "WHERE id_loan=1 ORDER BY id_payment DESC LIMIT 1;";
        totalCapitalPaid = stod(db.ejecutarConsulta(query.str()));
        query.str("");
        totalCapitalPaid += capitalPaid;
        
        query << "SELECT total_interest_paid FROM Payment "
              << "WHERE id_loan=1 ORDER BY id_payment DESC LIMIT 1;";
        totalInterestPaid = stod(db.ejecutarConsulta(query.str()));
        query.str("");
        totalInterestPaid += interestPaid;

        query << "SELECT terms_completed FROM Payment "
              << "WHERE id_loan=1 ORDER BY id_payment DESC LIMIT 1;";
        plazosCompletados = stod(db.ejecutarConsulta(query.str()));
        query.str("");
        plazosCompletados += 1;

        double actualDebt = stod(remaining);
        query << "SELECT total_capital_paid FROM Payment "
              << "WHERE id_loan=1 ORDER BY id_payment DESC LIMIT 1;";
        totalCapitalPaid = stod(db.ejecutarConsulta(query.str()));
        query.str("");
        actualDebt -= totalCapitalPaid;
      }




      // Query de ejecucion que debe hacer transaccion y actualizar actual_debt todo mediante
      query << "START TRANSACTION\n"
            << "INSERT INTO Payments (id_loan, terms_completed, "
            << "total_capital_paid, total_interest_paid, "
            << "capital_paid, interest_paid)"
            << "VALUES (" << loanID << ", " << plazosCompletados << ", "
            << totalCapitalPaid << ", " << totalInterestPaid << ", "
            << capitalPaid << ", " << interestPaid << ");\n"
            << "UPDATE Loan"
            << "SET actual_debt=" << actualDebt
            << "WHERE id_loan = 2;";
      final_query = query.str();


      // Ejecucion del Query
      db.ejecutarSQL(final_query);\

    } else {
      cout << "\n> Pago suspendido.";
    }
  }
}




/*
Funcion que calcula la fecha de pago
*/
string AbonoPrestamo::calculateDueDate(std::string loanID, DBManager& db) {
  int plazos_completados, plazo, year, month, day;
  stringstream query;
  string creation_date, loan_term_str, terms_completed_str;
  stringstream duedate;

  // Extraccion de datos de la DB
  query << "SELECT creation_date FROM Loan WHERE id_loan=" << loanID;
  creation_date = db.ejecutarConsulta(query.str());
  query.str("");

  query << "SELECT loan_term FROM Loan WHERE id_loan=" << loanID;
  loan_term_str = db.ejecutarConsulta(query.str());
  if (loan_term_str.empty()) {
    throw std::invalid_argument("loan_term is empty");
  }
  plazo = stoi(loan_term_str);
  query.str("");

  query << "SELECT terms_completed FROM Payment WHERE id_loan=" << loanID
        << " ORDER BY id_payment DESC LIMIT 1;";
  terms_completed_str = db.ejecutarConsulta(query.str());
  if (terms_completed_str.empty()) {
    plazos_completados = 0;
  } else {
    plazos_completados = stoi(terms_completed_str);
  }
  query.str("");

  // Verificar si creation_date tiene el formato esperado (YYYY-MM-DD)
  if (creation_date.length() != 10 || creation_date[4] != '-' || creation_date[7] != '-') {
    throw std::invalid_argument("Invalid creation_date format");
  }

  // Extraccion de datos de la fecha
  year = stoi(creation_date.substr(0, 4));
  month = stoi(creation_date.substr(5, 2));
  day = stoi(creation_date.substr(8, 2));

  // Ver cuantos meses se avanza
  month = month + (plazo - plazos_completados);

  // Formatear la fecha al distribuir meses en anios
  while (month > 12) {
    month -= 12;
    year += 1;
  }

  // Crear fecha
  duedate << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day;

  // Retornar fecha
  return duedate.str();
}



/*
Funcion que calcula el interes de amortizacion
*/
double AbonoPrestamo::interesAmortizacion(string loanID, DBManager& db) {
  stringstream query;
  double saldo, principal, interes, cuota;

  query << "SELECT actual_debt FROM Loan WHERE id_loan=" << loanID;
  saldo = stod(query.str());
  query.str("");

  query << "SELECT principal FROM Loan WHERE id_loan=" << loanID;
  principal = stod(query.str());
  query.str("");

  query << "SELECT monthly_payment FROM Loan WHERE id_loan=" << loanID;
  cuota = stod(query.str());
  query.str("");

  if (saldo == principal) {
    return cuota;
  } else {
    query << "SELECT interest_rate FROM Loan WHERE id_loan=" << loanID;
    interes = stod(query.str());
    return saldo*(interes/12);
  }
}
