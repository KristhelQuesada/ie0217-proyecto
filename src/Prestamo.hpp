#ifndef PRESTAMO
#define PRESTAMO

#include "DBManager.hpp"


class Prestamo {
private:
    int id_client;
    DBManager& db;

public:
    Prestamo(int id_client, DBManager& db);

    // Metodos funcionalidad
    void createLoan();
    void viewAll();
    void searchLoans();
};

#endif // PRESTAMO_HPP