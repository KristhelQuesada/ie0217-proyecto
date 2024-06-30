#include "Funciones.hpp"
#include <cmath> // Para usar la función pow(base, exponential)
#include <iomanip> // precision de los datos
using namespace std;

// DEFINES DE PRESTAMO
#define MAX_PERSONAL_LOAN 8000000.0;
#define MAX_PRENDARIO_LOAN 20000000.0;
#define MAX_HIPOTECARIO_LOAN 50000000.0;

#define MAX_PERSONAL_LOAN_USD 15000.0;
#define MAX_PRENDARIO_LOAN_USD 40000.0;
#define MAX_HIPOTECARIO_LOAN_USD 100000.0;

// ENUMS
/**
 * @brief Enumeración de tipos de prestamo a consultar.
 * 
 * Esta enumeración lista las opciones validas que pueden ser
 * seleccionadas dentro del menu de calculateLoan()
 */
enum loanTypes {
    PERSONAL = 1,
    PRENDARIO,
    HIPOTECARIO,
    RETURN_LOAN,
    LOAN_TYPE_MAX // para saber cuantas opciones tenemos
};

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


// Función que calcula el monto por cuota y saldo total a pagar de
// un crédito a tasa fija.
map<string, string> calculateLoan() {
    // Variables
    double p, i, n, r;                  // inputs
    double monthly_payment, repayment;  // outputs
    string loan_type, currency;         // str inputs
    map<string, string> data;           // return data

    // Determinar el tipo de préstamo
    // Declarar e inicializar variables
    string input;
    bool isValid = false;
    int option;

    // Impresión del menú
    cout << "\n---------------------------------------------------------------------" << endl;
    cout << "|                         TIPO DE PRÉSTAMO                          |" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "|  1. Personal  |  2. Prendario   |  3. Hipotecario   |  4. Salir   |" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    while (!isValid) {
        cout << "Indique el tipo de préstamo: ";
        cin >> input;
        option = verifyMenuOption(input, LOAN_TYPE_MAX);
        cin.ignore();

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
            case RETURN_LOAN:
                cout << "Saliendo del cálculo de préstamo..." << endl;
                return data; // Retorno temprano si se selecciona salir
            default:
                cout << "La opción para el tipo de préstamo ingresado no es válida." << endl;
                break;
        }
    }



    // Determinar el tipo de cambio, monto, plazo e interés
    cout << "\n\n > Ingrese:" << endl;
    currency = verifyCurrency();

    p = verifyDesiredAmount(loan_type, currency);

    i = verifyInterest(loan_type);
    n = verifyTerm();

    // Cálculo de tasa de interés periódica
    r = i / (100 * 12);

    // Cálculo de cuota mensual y el monto final a pagar (repayment)
    monthly_payment = (p * r) / (1 - pow(1 + r, -n));
    repayment = p + monthly_payment * n;

    // Impresión de resultados
    cout << "\n > Los resultados del préstamo solicitado son" << endl;
    cout << "- Cuota mensual: "
         << to_string_with_precision(monthly_payment, 2)
         << " (" << currency << ")."
         << "\n- Monto final a pagar: "
         << to_string_with_precision(repayment, 2) << " (" << currency << ")." << endl;

    // Creación del mapa
    data["id_loan_type"] = loan_type;
    data["currency"] = currency;
    data["principal"] = to_string_with_precision(p, 2);
    data["loan_term"] = to_string_with_precision(n, 0);
    data["interest_rate"] = to_string_with_precision(i, 0);
    data["monthly_payment"] = to_string_with_precision(monthly_payment, 2);
    data["total_repayment"] = to_string_with_precision(repayment, 2);

    // Retornar la cuota
    return data;
}

map<string, string> calculateCDP() {
    // Variables
    double principal, interest_rate, months, total_repayment;  // inputs y outputs
    string currency, creation_date, maturity_date;             // str inputs
    map<string, string> data;                                  // return data

    // Solicitud de datos del CDP
    cout << "\n---------------------------------------------------------------------" << endl;
    cout << "|                  DATOS DEL CERTIFICADO DE DEPÓSITO               |" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "Tipo de cambio (USD/CRC): ";
    cin >> currency;
    cin.ignore();
    cout << "Monto del depósito (" << currency << "): ";
    cin >> principal;
    cout << "Plazo (meses): ";
    cin >> months;
    cout << "Tasa de interés (%): ";
    cin >> interest_rate;
    cout << "Fecha de creación (YYYY-MM-DD): ";
    cin >> creation_date;
    cout << "Fecha de vencimiento (YYYY-MM-DD): ";
    cin >> maturity_date;

    // Calculo del monto total a pagar (total_repayment)
    total_repayment = principal * pow((1 + interest_rate / 100), months / 12);

    // Impresion de resultados
    cout << "\n>> LOS RESULTADOS DEL CDP SON:" << endl;
    cout << "- Monto total a recibir: "
         << to_string_with_precision(total_repayment, 2) << " (" << currency << ")." << endl;

    // Creacion del mapa
    data["creation_date"] = creation_date;
    data["maturity_date"] = maturity_date;
    data["interest_rate"] = to_string_with_precision(interest_rate, 2);
    data["principal"] = to_string_with_precision(principal, 2);
    data["total_repayment"] = to_string_with_precision(total_repayment, 2);
    data["currency"] = currency;

    // Retornar los datos calculados
    return data;
}



double verifyInterest(const string& loanType) {
    // Declaracion e inicializacion de variables
    int interestRate;
    bool validInterest = false;

    // Obtener el rango de tasas de interés basado en el tipo de préstamo
    auto interestRateRange = getInterestRateRange(loanType);
    int defaultInterestRate = interestRateRange.second; // se escoje por default el mas grande

    // Asegurarse que se obtiene el interes correcto
    while (validInterest == false) {
        // Solicitar al usuario que seleccione una tasa de interés
        cout << "Tasa de interés entre " << interestRateRange.first << "-" 
             << interestRateRange.second << "% (Dejar en blanco para tasa predeterminada de " 
             << defaultInterestRate << "%): ";
        string input;
        getline(cin, input);

        if (input.empty()) {
            interestRate = defaultInterestRate;
            validInterest = true;
        } else {
            interestRate = stod(input);

            if (interestRate < interestRateRange.first || interestRate > interestRateRange.second) {
                cout << "La tasa de interés seleccionada está "
                     << "fuera del rango permitido, intente nuevamente." << endl;
            } else {
                validInterest = true;
            }
        }
    }

    return interestRate;
}




pair<double, double> getInterestRateRange(const string& loanType) {
    if (loanType == "HP") { // Préstamos Hipotecarios
        return {5.00, 20.00};
    } else if (loanType == "PR") { // Préstamos Prendarios
        return {10.00, 15.00};
    } else if (loanType == "PE") { // Préstamos Personales
        return {16.00, 22.00};
    } else {
        throw std::invalid_argument("Tipo de préstamo no válido");
    }
}




double verifyDesiredAmount(const string& loanType, const string& currency) {
    // Declaracion e inicializacion de variables
    string input;
    double desiredAmount;
    bool validAmount = false;

    // Obtener el rango de tasas de interés basado en el tipo de préstamo
    auto maxLimit = getAmountLimit(loanType, currency);

    // Asegurarse que se solicita un prestamo menor al maximo permitido
    while (validAmount == false) {
        try {
            // Solicitar al usuario que seleccione el monto
            cout << "Indique el monto solicitado por el cliente: ";
            string input;
            getline(cin, input);

            desiredAmount = stod(input);


            if (desiredAmount <= maxLimit) {
                validAmount = true;
            } else {
                cout << "El monto solicitado está fuera del rango "
                     << "permitido, intente nuevamente." << endl;
            }
        } catch (const std::invalid_argument& e) {
            cout << "El monto ingresado no debe contener caracteres. Intente de nuevo." << endl;
        }
    }

    return desiredAmount;
}




double getAmountLimit(const string& loanType, const string& currency) {
    if (currency == "CRC") {
        if (loanType == "HP") { // Préstamos Hipotecarios
            return MAX_HIPOTECARIO_LOAN;
        } else if (loanType == "PR") { // Préstamos Prendarios
            return MAX_PRENDARIO_LOAN;
        } else if (loanType == "PE") { // Préstamos Personales
            return MAX_PERSONAL_LOAN;
        } else {
            throw std::invalid_argument("Tipo de préstamo no válido");
        }

    } else if (currency == "USD") {
        if (loanType == "HP") { // Préstamos Hipotecarios
            return MAX_HIPOTECARIO_LOAN_USD;
        } else if (loanType == "PR") { // Préstamos Prendarios
            return MAX_PRENDARIO_LOAN_USD;
        } else if (loanType == "PE") { // Préstamos Personales
            return MAX_PERSONAL_LOAN_USD;
        } else {
            throw std::invalid_argument("Tipo de préstamo no válido");
        }
    } else {
        throw std::invalid_argument("Tipo de cambio no válida");
    }
}




string verifyCurrency() {
    string moneda; // Variable a retornar
    bool validCurrency = false;

    while (validCurrency == false) {
        cout << "Ingrese la moneda (CRC o USD): ";
        getline(std::cin, moneda);

        if (moneda != "CRC" && moneda != "USD") {
            std::cout << "Moneda inválida. Inténtelo de nuevo.\n";
        } else {
            validCurrency = true;
        }
    }

    return moneda;
}



// Función para pedir un entero al usuario y convertirlo a double con dos decimales
double verifyTerm() {
    int valorEntero;
    double valorDouble;
    bool valid_term = false;

    while (!valid_term) {
        cout << "Ingrese el plazo en meses: ";
        cin >> valorEntero;

        if (cin.fail()) {
            cin.clear(); // Limpiar el estado de error
            cin.ignore(); // Limpiar el buffer
            cout << "El plazo no puede contener decimales, intente de nuevo" << std::endl;
        } else {
            cin.ignore(); // Limpiar el buffer
            break;
        }
    }

    // Convertir el entero a double y configurar para mostrar dos decimales
    valorDouble = static_cast<double>(valorEntero);
    return valorDouble;
}