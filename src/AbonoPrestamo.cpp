#include "AbonoPrestamo.hpp"
#include "Funciones.hpp"
#include <iostream>
#include <string>
using namespace std;

// Define que contiene la multa que se aplica por atraso
#define MULTA 0.020

/*
----------------------------------------------------------
                    Constructor
----------------------------------------------------------
*/
AbonoPrestamo::AbonoPrestamo(int id_cliente, DBManager& db) 
    : Transaccion(id_cliente, db) {}


/*
----------------------------------------------------------
            Funcion que ejecuta el abono
----------------------------------------------------------
*/
void AbonoPrestamo::ejecutar() {
    // Declaracion de variables
    bool existe, isOnTime;
    string input, final_query;
    stringstream queryInsert, queryUpdate;
    double pago;


    // 1. Solicitud del ID del prestamo, verificacion de
    // existencia y extraccio de datos
    existe = verificarExistencia();


    // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    if (existe) {
        // Inicializar variables
        string divisa      = this->loanData["currency"];
        double loanTerm    = stod(this->loanData["loan_term"]);       // is int
        double interes     = stod(this->loanData["interest_rate"]);   // is int
        double pagoMensual = stod(this->loanData["monthly_payment"]);
        double deudaActual = stod(this->loanData["actual_debt"]);
        double principal   = stod(this->loanData["principal"]);
        double repayment   = stod(this->loanData["total_repayment"]);

        double cuotasPagadas     = stod(this->lastPayment["terms_completed"]);    // is intdouble
        double totalCapitalPaid  = stod(this->lastPayment["total_capital_paid"]);
        double totalInterestPaid = stod(this->lastPayment["total_interest_paid"]);
        double capitalPaid       = stod(this->lastPayment["capital_paid"]);
        double interestPaid      = stod(this->lastPayment["interest_paid"]);

        string beginTransactionSQL = "START TRANSACTION; ";
        string endTransactionSQL   = "COMMIT; ";

        // 2. Verificar el cobro por multa
        isOnTime = verificarPuntualidad();

        if (!isOnTime) {
            pago = pagoMensual + (pagoMensual*MULTA);
        } else {
            pago = pagoMensual;
        }


        // 3. Confirmar transaccion
        cout << "El monto total a pagar es de " << pagoMensual << " "
             << divisa << ".\n" << "Desea continuar con el pago? [Y/N]: ";
        cin >> input;

        // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        if (input == "Y" || input == "y") {
            // 4. Actualizar datos del presente abono
            cuotasPagadas += 1; 
            interestPaid = interesAmortizacion(totalCapitalPaid, principal, interes);
            capitalPaid = pagoMensual - interestPaid;

            totalInterestPaid += interestPaid;
            totalCapitalPaid += capitalPaid;


            // 5. Actualizar datos del prestamo
            deudaActual -= pagoMensual;


            // 6. Crear el queries
            queryInsert << "INSERT INTO Payment (id_loan, terms_completed, "
                        << "total_capital_paid, total_interest_paid, capital_paid, interest_paid) "
                        << "VALUES ("
                        << this->lastPayment["id_loan"] << ", "
                        << to_string_with_precision(cuotasPagadas, 0) << ", "
                        << to_string_with_precision(totalCapitalPaid, 2) << ", "
                        << to_string_with_precision(totalInterestPaid, 2) << ", "
                        << to_string_with_precision(capitalPaid, 2) << ", "
                        << to_string_with_precision(interestPaid, 2) << "); ";

            queryUpdate << "UPDATE Loan SET actual_debt="
                        << to_string_with_precision(deudaActual, 2) << " WHERE id_loan="
                        << this->lastPayment["id_loan"] << ";";


            // 7. Ejecutar el cambio
            db.ejecutarSQL(beginTransactionSQL);

            final_query = queryInsert.str();
            db.ejecutarSQL(final_query);

            final_query = queryUpdate.str();
            db.ejecutarSQL(final_query);

            db.ejecutarSQL(endTransactionSQL);


        // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        } else {
            // Afinar respuesta
            cout << "No se decidio continuar con el pago" << endl;
        }


    // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    } else {
        // Aca sepuede preguntar si se quiere consultar de nuevo
        cout << "if existe de ejecutar" << endl;
    }
}




/*
----------------------------------------------------------
   Funcion que permite verificar si el prestamo existe
----------------------------------------------------------
*/
bool AbonoPrestamo::verificarExistencia() {
    string query = "SELECT actual_debt FROM Loan WHERE id_loan=";
    string loanID, dbOutput;

    cout << "Ingrese el ID del prestamo: ";
    cin >> loanID;
    cin.ignore();

    query += loanID;
    dbOutput = db.ejecutarConsulta(query);

    if (dbOutput == "0.00") {
        cout << "\nEl prestamo ya ha sido pagado.";
        return false;
    } else if (dbOutput == "") {
        cout << "\nNo existe prestamo asociado al ID ingresado.";
        return false;
    } else {
        this->setColumnas();
        this->extraerDatos(loanID);
        return true;
    }
};



/*
----------------------------------------------------------
     Funcion que permite la extraccion de los datos
----------------------------------------------------------
*/
void AbonoPrestamo::extraerDatos(string& loanID) {
    string queryLoan = "SELECT * FROM Loan WHERE id_loan=";
    string queryPayment1 = "SELECT * FROM Payment WHERE id_loan=";
    string queryPayment2 = " ORDER BY id_payment DESC LIMIT 1;";
    string final_query;

    // Cargar la informacion del prestamo
    final_query = queryLoan + loanID;
    this->loanData = db.cargarDatos(final_query, this->loanData);
    
    // Verificar si es primer pago para inicializar valores
    string deudaActual = this->loanData["actual_debt"];
    string deudaTotal = this->loanData["total_repayment"];

    if (deudaActual == deudaTotal) {
        // Inicializar pago 0
        this->lastPayment["id_loan"]             = loanID;
        this->lastPayment["terms_completed"]     = "0";
        this->lastPayment["total_capital_paid"]  = "0.00";
        this->lastPayment["total_interest_paid"] = "0.00";
        this->lastPayment["capital_paid"]        = "0.00";
        this->lastPayment["interest_paid"]       = "0.00";
    } else {
        // Cargar la informacion del ultimo pago
        final_query = queryPayment1 + loanID + queryPayment2;
        this->lastPayment = db.cargarDatos(final_query, this->lastPayment);
    }
}




/*
----------------------------------------------------------
     Funcion que permite inicializar los mapas
        con las columnas que quiero extraer
----------------------------------------------------------
*/
void AbonoPrestamo::setColumnas() {
    // Inicializar  nombre de las columnas asociado a Loan
    this->loanData["loan_term"]       = "";
    this->loanData["creation_date"]   = "";
    this->loanData["currency"]        = "";
    this->loanData["principal"]       = "";
    this->loanData["interest_rate"]   = "";
    this->loanData["monthly_payment"] = "";
    this->loanData["total_repayment"] = "";
    this->loanData["actual_debt"]     = "";


    // Inicializar nombre de las columnas asociadas a Payment
    this->lastPayment["id_loan"]             = "";
    this->lastPayment["terms_completed"]     = "";
    this->lastPayment["total_capital_paid"]  = "";
    this->lastPayment["total_interest_paid"] = "";
    this->lastPayment["capital_paid"]        = "";
    this->lastPayment["interest_paid"]       = "";
}




/*
----------------------------------------------------------
  Funcion que permite verificar si el pago esta a tiempo
----------------------------------------------------------
*/
bool AbonoPrestamo::verificarPuntualidad() {
    // Inicializar variables
    string today, dueDate, query;

    // Declaracion de variables
    string curDateQuery = "SELECT CURDATE() AS today;";


    today = db.ejecutarConsulta(curDateQuery);
    dueDate = this->calcularDueDate();

    return verifyDate(dueDate, today);
};



/*
----------------------------------------------------------
            Funcion que calcula la fecha de pago
----------------------------------------------------------
*/
string AbonoPrestamo::calcularDueDate() {
    // Declaracion de variables
    int year, month, day;
    stringstream duedate;

    // Inicializar variables
    int plazo = stoi(this->loanData["loan_term"]);
    int plazos_completados = stoi(this->lastPayment["terms_completed"]);
    string creation_date = this->loanData["creation_date"];

    // Extraccion de los datos de la fecha
    year = stoi(creation_date.substr(0, 4));
    month = stoi(creation_date.substr(5, 2));
    day = stoi(creation_date.substr(8, 2));

    // Ver cuantos meses se avanza
    month = month + plazos_completados + 1;

    // Formatear la fecha al distribuir meses en anios
    while (month > 12) {
      month -= 12;
      year += 1;
    }

    // Crear fecha
    duedate << year << "-" 
            << (month < 10 ? "0" : "") << month << "-" 
            << (day < 10 ? "0" : "") << day;

    // Retornar fecha
    return duedate.str();
}



/*
----------------------------------------------------------
      Funcion que calcula el interes de amortizacion.
      Cuanto de la cuota total se asigna a intereses.
----------------------------------------------------------
*/
double AbonoPrestamo::interesAmortizacion(double capitalPagado,
                                          double principal, double interes)
{
    // Formula para calcular cuanto se abona de interes de la cuota mensual
    double saldo = principal - capitalPagado;
    return (saldo*((interes*0.01)/12.0));
}