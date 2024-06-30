#include "AbonoPrestamo.hpp"
#include "Funciones.hpp"
#include <iostream>
#include <string>
#include <vector>
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
    bool existe, isOnTime, enoughBalance;
    string input, final_query, divisaPago;
    stringstream queryInsert, queryUpdate;
    double pago, cuotasPagar, tipoDeCambio;


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

        vector<string> queries;

        // 2. Verificar el cobro por multa
        isOnTime = verificarPuntualidad();

        if (!isOnTime) {
            pago = pagoMensual + (pagoMensual*MULTA);
        } else {
            pago = pagoMensual;
        }


        // 3. Confirmar transaccion
        cout << "Cuantas cuotas desea abonar: ";
        cin >> cuotasPagar;
        pago = pagoMensual * (cuotasPagar-1); // multa solo a una cuota


        cout << "El monto total a pagar es de " << pago << " " << divisa;
        bool confirmed = this->confirmarMetodoDePago();


        if (id_account != "") {
            tipoDeCambio = this->getCurrencyChange(divisa);
            pago = pago * tipoDeCambio;
            enoughBalance = this->confirmarFondos(divisa, pago);

            if (enoughBalance) {
                newBalance = getNewBalanceAccount(pago);
                queryAccount << "UPDATE BankAccount SET balance=" << to_string_with_precision(newBalance, 2)
                             << " WHERE id_account" << this->account;
            }

        } else {
            cout << "Indique la divisa de pago (USD/CRC): " << endl;
            cin >> divisaPago;

            tipoDeCambio = this->obtenerTipoDeCambio(divisa, divisaPago);
            pago = pago * tipoDeCambio;
            cout << "El monto total a pagar es de " << pago << " " << divisaPago;
            enoughBalance = true; // se asume que se acepta el pago;
        }

        // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        if (confirmed && enoughBalance) {

            for (double i=0; i < cuotasPagar; cuotasPagar--) {
                // 4. Actualizar datos del presente abono
                cuotasPagadas += 1; 
                interestPaid = interesAmortizacion(totalCapitalPaid, principal, interes);
                capitalPaid = pagoMensual - interestPaid;

                totalInterestPaid += interestPaid;
                totalCapitalPaid += capitalPaid;


                // 5. Actualizar datos del prestamo
                deudaActual -= pagoMensual;
            }


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

            final_query = queryInsert.str();
            queries.push_back(final_query);

            final_query = queryUpdate.str();
            queries.push_back(final_query);

            final_query = queryAccount.str();
            queries.push_back(final_query);

            db.ejecutarTransactionSQL(queries);


        // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
        } else {
            // Afinar respuesta
            cout << "Cliente suspende el pago." << endl;
        }


    // _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
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

    // Inicializar cuenta bancaria del que se extrae el abono
    this->idAccount = "";
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



/*
----------------------------------------------------------
      Funcion que permite determinar el metodo de
             pago: efectivo o por cuenta.
----------------------------------------------------------
*/
bool AbonoPrestamo::confirmarMetodoDePago(){
    string metodo, continuar, idAccount;
    bool metodoValido, confirmado;

    if (this->id_client = 0) {
        cout << "El cliente solo puede pagar en efectivo.\n";

    } else {

        while (!metodoValido) {
            cout << "Desea pagar:\n"
             << "  1. En efectivo\n"
             << "  2. Cuenta interna \n"
             << "  3, Suspender pago"  ;
            cout << "Seleccione: ";
            cin >> metodo;
            option = verifyMenuOption(metodo, 4);
            cin.ignore();

            switch (option) {
                case 1:
                    cout << "El pago se realiza en efectivo." << endl;
                    metodoValido = true;
                    return true;
                    break;
                case 2:
                    cout << "El pago se realiza por cuenta interna." << endl;
                    this->idAccount = db.determinarCuentaID(this->id_client);
                    metodoValido = true;
                    return true;
                    break;
                case 3:
                    metodoValido = true;
                    return false;
                    break;
                default:
                    cout << "La entrada no es valida" 
                         << ", seleccione un numero del menu."
                         << endl;
                    break;
            }
        }
    }
}


double getNewBalanceAccount(const double& pago) {
    string query;
    double balance, newBalance;

    query = "SELECT balance FROM BankAccount WHERE id_account=" + this->idAccount;
    balance = stod(db.ejecutarConsulta{query});
    newBalance = balance - pago;

    return newBalance;
}

double getCurrencyChange(const string& divisaPrestamo) {
    string query, divisaCuenta;
    double tipoDeCambio;

    query = "SELECT currency FROM BankAccount WHERE id_account=" + this->idAccount;
    divisaCuenta = db.ejecutarConsulta{query};

    tipoDeCambio = obtenerTipoDeCambio(divisaPrestamo, divisaCuenta);

    return tipoDeCambio;
}



bool AbonoPrestamo::confirmarFondos(const double& pagoConv) {
    string query;
    double balance;

    query = "SELECT balance FROM BankAccount WHERE id_account=" + this->idAccount;
    balance = stod(db.ejecutarConsulta{query});
    
    if (balance < pago) {
        return false;
    } esle {
        return true;
    }

}