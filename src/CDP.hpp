#ifndef CDP_HPP
#define CDP_HPP

#include "DBManager.hpp"


class CDP {
private:
    int id_client;
    DBManager& db;
    // Atributo que contiene la informacion de un cdp en especifico
    std::map<std::string, std::string> relatedInfo;

public:
    CDP(int id_client, DBManager& db);

    // Metodos funcionalidad
    void createCDP();
    void viewAll();
    void searchCDP();
};

#endif // CDP_HPP