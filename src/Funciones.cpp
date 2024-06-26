#include "Funciones.hpp"
#include "Transaccion.hpp"
#include "AbonoPrestamo.hpp"
#include "Prestamo.hpp"
#include <cmath> // Para usar la función pow(base, exponential)
#include <iomanip> // precision de los datos
using namespace std;

// https://www.geeksforgeeks.org/processing-strings-using-stdistringstream/
// Funcion que verifica la opcion ingresada en el menu
int verifyMenuOption(string input, int out_range) {
    int size_input = size(input); // determina el tamanio del string
    int verified_input;

    // Las opciones que queremos verificar solo tienen un caracter,
    // por tanto se pregunta si esto sucede
    if (size_input == 1) {

        // Luego se crea el objeto de la clase istringstream
        istringstream objetoEntrada(input);

        // Verifica si el caracter es un numero
        /* Para ello intenta extraer un entero de la cadena con
            objetoEntrada >> verified_input
           que devuelve true si la extraccion fue exitosa
        */
        if (objetoEntrada >> verified_input) {
            return verified_input;
        } else {
            return out_range;
        }

    } else {
        return out_range;
    }
}


// Funcion que compara dos fechas para saber si se hizo el cobro antes o despues
// de la fecha esperada (due_date) con fechas en el formato YYYY-MM-DD
bool verifyDate(string due_date, string payment_date) {
    // Variables que contienen el anio, mes y dia de cada fecha
    int year_DD, year_PD, month_DD, month_PD, day_DD, day_PD;
    bool isOnTime;

    // Extraccion de datos
    year_DD = stoi(due_date.substr(0, 4));
    month_DD = stoi(due_date.substr(6, 2));
    day_DD = stoi(due_date.substr(9, 2));

    year_PD = stoi(payment_date.substr(0, 4));
    month_PD = stoi(payment_date.substr(6, 2));
    day_PD = stoi(payment_date.substr(9, 2));

    // Determinacion de si la fecha de pago es menor al due date
    if (year_DD > year_PD || 
        year_DD == year_PD && month_DD > month_PD || 
        year_DD == year_PD && month_DD == month_PD && day_DD >= day_PD) {
            isOnTime = true;
        } else {
            isOnTime = false;
        }

    // Resultado
    return isOnTime;
}


// Funcion que permite regresar los numeros con dos decimales de precision
string to_string_with_precision(double value, int precision) {
    ostringstream out;
    out << fixed << setprecision(precision) << value;
    return out.str();
}


// Funcion que calcula el monto por cuota y saldo total a pagar de
// un credito a tasa fija.
map<string, string> calculateLoan(){
    // Variables
    int option;
    double p, i, n, r;                  // inputs
    double monthly_payment, repayment;  // outputs
    string input, loan_type, currency;  // str inputs
    map<string, string> data;           // return data
    bool isValid = false;

    // Determinar el tipo de prestamo
    cout << "\n-----------------------------------------------------" << endl;
    cout << "|                  TIPO DE PRESTAMO                 |" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "|  1. Personal  |  2. Prendario  |  3. Hipotecario  |" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Indique el tipo de prestamo: ";
    cin >> input;
    option = verifyMenuOption(input, LOAN_TYPE_MAX);
    cin.ignore();

    while (!isValid) {
        switch (option) {
            case PERSONAL:
                loan_type = "PE";
                isValid = true;
                break;
            case PRENDARIO:
                loan_type = "PR";
                isValid = true;
                break;
            case HIPOTECARIO:
                loan_type = "HP";
                isValid = true;
                break;
            default:
                cout << "La opcion para el tipo de prestamo ingresado no es valida." << endl;
                break;
        }
    }

    // Solicitud de monto, plazo e interes
    cout << "\n\n>> INGRESE:" << endl;
    cout << "Tipo de cambio (USD/CRC): ";
    cin >> currency;
    cin.ignore();
    cout << "Monto solicitado (" << currency << "): ";
    cin >> p;
    cout << "Plazo (meses): ";
    cin >> n;
    cout << "Tasa de interes (%): ";
    cin >> i;

    // Calculo de tasa de interes periodica
    r = i/(100*12);

    // Calculo de cuota mensual y el monto final a pagar (repayment)
    monthly_payment = (p*r)/(1-pow(1+r, -n));
    repayment = monthly_payment*n;

    // Impresion de resultados
    cout << "\n>> LOS RESULTADOS DEL PRESTAMO SOLICITADO SON:" <<  endl;
    cout << "- Cuota mensual: "
         << to_string_with_precision(monthly_payment, 2)
         << " (" << currency << ")."
         << "\n- Monto final a pagar: "
         << to_string_with_precision(repayment, 2) << " (" << currency << ")." << endl;

    // Creacion del mapa
    data["loan_term"] = to_string_with_precision(n, 0);
    data["id_loan_type"] = loan_type;
    data["currency"] = currency;
    data["principal"] = to_string_with_precision(p, 2);
    data["interest_rate"] = to_string_with_precision(i, 0);
    data["monthly_payment"] = to_string_with_precision(monthly_payment, 2);
    data["total_repayment"] = to_string_with_precision(repayment, 2);


    // Retornar la cuota
    return data;
}