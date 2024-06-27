#ifndef PRESTAMO_HPP
#define PRESTAMO_HPP

#include "DBManager.hpp"


class Prestamo {
private:
    int id_client;
    DBManager& db;
    // Atributo que contiene la informacion de un prestams en especifico
    std::map<std::string, std::string> relatedInfo;
    std::map<std::string, std::string> loadedValues;

public:
    Prestamo(int id_client, DBManager& db);

    // Metodos funcionalidad
    void createLoan();
    void viewAll();
    void searchLoans();

    // Pruebas de funciones del DBManager
    void extractAllData();
    void extractOneData();
};

#endif // PRESTAMO_HPP