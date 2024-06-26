#include "Sistema.hpp"
#include "Transaccion.hpp" // Incluir la definición de Transaccion

Sistema::Sistema(const std::string& dbPath) : database(dbPath), dbManager(dbPath) {
    dbManager.conectar();
}

void Sistema::atencionCliente() {
    int opcion;
    std::cout << "Bienvenido al Sistema de Atención al Cliente. Seleccione una opción:\n";
    std::cout << "1. Crear objeto (Cliente, Cuenta, Préstamo, CDP)\n";
    std::cout << "2. Obtener información (Transacciones, Préstamos)\n";
    std::cout << "3. Realizar Transacción (Depósito, Retiro, Transferencia, Abono)\n";
    std::cin >> opcion;
    std::string data;
    std::string type;

    switch (opcion) {
        case 1:
            // Proceso para crear objetos
            // Pedir al usuario que ingrese los datos necesarios
            std::cin.ignore(); // Ignorar el '\n' que queda en el buffer
            std::cout << "Ingrese los datos necesarios para la creación:\n";

            std::getline(std::cin, data); // Se asume por el momento que el usuario sabe cómo ingresar datos correctamente

            std::cout << "Ingrese el tipo de objeto a crear (Cliente, Cuenta, Préstamo, CDP):\n";
            std::cin >> type;

            crear();
            break;
        case 2:
            // Proceso para obtener información
            obtenerRe();
            break;
        case 3:
            // Proceso para manejar transacciones
            handleTransactions();
            break;
        default:
            std::cout << "Opción no válida, por favor intente de nuevo.\n";
    }
}

void Sistema::crear() {
    int opcion;
    std::string data;
    std::cout << "Seleccione el tipo de objeto a crear:\n";
    std::cout << "1. Cliente\n";
    std::cout << "2. Cuenta\n";
    std::cout << "3. Préstamo\n";
    std::cout << "4. Certificado de Depósito (CDP)\n";
    std::cin >> opcion;

    std::cin.ignore(); // Ignorar el '\n' que queda en el buffer
    std::cout << "Ingrese los datos necesarios para la creación:\n";

    switch (opcion) {
        case 1:
            dbManager.ejecutarSQL("INSERT INTO clientes (datos) VALUES ('" + data + "')");
            break;
        case 2:
            dbManager.ejecutarSQL("INSERT INTO cuentas (datos) VALUES ('" + data + "')");
            break;
        case 3:
            dbManager.ejecutarSQL("INSERT INTO prestamos (datos) VALUES ('" + data + "')");
            break;
        case 4:
            dbManager.ejecutarSQL("INSERT INTO certificados_deposito (datos) VALUES ('" + data + "')");
            break;
        default:
            std::cout << "Opción no válida. Por favor intente de nuevo.\n";
    }
}


void Sistema::obtenerRe() {
    int id;
    int opcion;
    std::cout << "Ingrese el ID para obtener registros de transacciones o reporte de préstamos:\n";
    std::cin >> id;
    std::cout << "Seleccione el tipo de información a obtener:\n";
    std::cout << "1. Registros de transacciones\n";
    std::cout << "2. Reporte de préstamos\n";

    std::cin >> opcion;

    switch (opcion) {
        case 1:
            std::cout << obtenerRegTrans(id) << std::endl;
            break;
        case 2:
            std::cout << obtenerRepPrest(id) << std::endl;
            break;
        default:
            std::cout << "Opción no válida. Por favor intente de nuevo.\n";
    }
}

void Sistema::handleTransactions() {
    // Se instancia un objeto de la clase Transaccion
    // y se llama al método ejecutar
    Transaccion transaccion;
    transaccion.ejecutar();
}

std::string Sistema::solicitarInfo(const std::string& tipoInfo) {
    // Ejemplo de cómo manejar diferentes tipos de información
    if (tipoInfo == "general") {
        return dbManager.ejecutarConsulta("SELECT * FROM prestamos");
    } else if (tipoInfo == "detalles") {
        int idPrestamo;
        std::cout << "Ingrese el ID del préstamo para obtener detalles:\n";
        std::cin >> idPrestamo;
        return dbManager.ejecutarConsulta("SELECT * FROM prestamos WHERE id = " + std::to_string(idPrestamo));
    } else if (tipoInfo == "calculo") {
        int idPrestamo;
        std::cout << "Ingrese el ID del préstamo para calcular el total de cuotas y monto a pagar:\n";
        std::cin >> idPrestamo;
        return calcularCuotasYPago(idPrestamo);
    } else {
        return "Tipo de información no reconocido.";
    }
}

std::string Sistema::calcularCuotasYPago(int idPrestamo) {
    // Se supone que se necesita ejecutar un procedimiento almacenado que calcula las cuotas
    return dbManager.ejecutarConsulta("CALL calcularCuotas(" + std::to_string(idPrestamo) + ")");
}
std::string Sistema::obtenerRegTrans(int idCliente) {
    return dbManager.ejecutarConsulta("SELECT * FROM transacciones WHERE cliente_id = " + std::to_string(idCliente));
}

std::string Sistema::obtenerRepPrest(int idPrestamo) {
    return dbManager.ejecutarConsulta("SELECT * FROM prestamos WHERE prestamo_id = " + std::to_string(idPrestamo));
}
