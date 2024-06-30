# Makefile para el proyecto del sistema bancario

# Definición de variables
CXX = g++
CXXFLAGS = -I/usr/include/cppconn -L/usr/lib -lmysqlcppconn
SRCDIR = src
TARGET = sistema_bancario.exe
SOURCES = $(SRCDIR)/AbonoPrestamo.cpp $(SRCDIR)/CDP.cpp $(SRCDIR)/Cliente.cpp $(SRCDIR)/Cuenta.cpp $(SRCDIR)/DBManager.cpp $(SRCDIR)/Deposito.cpp $(SRCDIR)/Funciones.cpp $(SRCDIR)/Prestamo.cpp $(SRCDIR)/Menus.cpp $(SRCDIR)/Retiro.cpp $(SRCDIR)/Sistema.cpp $(SRCDIR)/Transaccion.cpp $(SRCDIR)/Transferencia.cpp

# Regla por defecto
all: compile run

# Regla para compilar el proyecto
compile:
	$(CXX) -o $(TARGET) $(SOURCES) $(CXXFLAGS)

# Regla para ejecutar el proyecto
run:
	./$(TARGET)

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET)
