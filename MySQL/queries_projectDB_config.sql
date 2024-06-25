-- MySQL Script for `project-ie0217-db` development
-- mar 04 jun 2024 23:13:42 CST
-- Este script contiene:
-- 		1. Query de creacion de la DB.
-- 		2. Queries de modificacion de la DB.
-- 		3. Queries para la adicion de datos iniciales


-- -----------------------------------------------------------------------
--               Creacion de la base de datos y sus tablas              --
-- -----------------------------------------------------------------------
-- Agregar aca la exportacion del Model con todo lo implementado
-- MySQL Script generated by MySQL Workbench
-- mar 25 jun 2024 15:07:18 CST
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `project-ie0217-db` DEFAULT CHARACTER SET utf8 ;
USE `project-ie0217-db` ;

-- -----------------------------------------------------
-- Table `mydb`.`Currency`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `project-ie0217-db`.`Currency` (
  `id_currency` CHAR(3) NOT NULL,
  `currency_name` CHAR(7) NOT NULL,
  PRIMARY KEY (`id_currency`),
  UNIQUE INDEX `id_currency_UNIQUE` (`id_currency` ASC) VISIBLE,
  UNIQUE INDEX `currency_name_UNIQUE` (`currency_name` ASC) VISIBLE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`BankAccount`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `project-ie0217-db`.`BankAccount` (
  `id_account` INT UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT,
  `id_client` INT(9) UNSIGNED ZEROFILL NOT NULL,
  `currency` CHAR(3) NOT NULL,
  `balance` DECIMAL(9,2) UNSIGNED NOT NULL DEFAULT 0,
  `opening_date` DATE NOT NULL DEFAULT (CURRENT_DATE),
  PRIMARY KEY (`id_account`),
  UNIQUE INDEX `id_cuenta_UNIQUE` (`id_account` ASC) VISIBLE,
  UNIQUE INDEX `id_client_UNIQUE` (`id_client` ASC) VISIBLE,
  INDEX `currency_idx` (`currency` ASC) VISIBLE,
  CONSTRAINT `fk_id_client_ba`
    FOREIGN KEY (`id_client`)
    REFERENCES `project-ie0217-db`.`Client` (`id_client`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_currency_ba`
    FOREIGN KEY (`currency`)
    REFERENCES `project-ie0217-db`.`Currency` (`id_currency`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Client`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `project-ie0217-db`.`Client` (
  `id_client` INT(9) ZEROFILL UNSIGNED NOT NULL AUTO_INCREMENT,
  `client_name` VARCHAR(50) NOT NULL,
  `client_lastname` VARCHAR(50) NOT NULL,
  `id_colones_account` INT UNSIGNED ZEROFILL NULL DEFAULT NULL,
  `id_dolares_account` INT UNSIGNED ZEROFILL NULL DEFAULT NULL,
  PRIMARY KEY (`id_client`),
  UNIQUE INDEX `id_client_UNIQUE` (`id_client` ASC) VISIBLE,
  UNIQUE INDEX `id_dolares_account_UNIQUE` (`id_dolares_account` ASC) VISIBLE,
  UNIQUE INDEX `id_colones_account_UNIQUE` (`id_colones_account` ASC) VISIBLE,
  CONSTRAINT `fk_id_colones_account`
    FOREIGN KEY (`id_colones_account`)
    REFERENCES `project-ie0217-db`.`BankAccount` (`id_account`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_id_dolares_account`
    FOREIGN KEY (`id_dolares_account`)
    REFERENCES `project-ie0217-db`.`BankAccount` (`id_account`)
    ON DELETE CASCADE
    ON UPDATE CASCADE);


-- -----------------------------------------------------
-- Table `mydb`.`LoanType`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `project-ie0217-db`.`LoanType` (
  `id_loan_type` CHAR(2) NOT NULL,
  `loan_type` VARCHAR(20) NOT NULL,
  PRIMARY KEY (`id_loan_type`),
  UNIQUE INDEX `id_loan_type_UNIQUE` (`id_loan_type` ASC) VISIBLE,
  UNIQUE INDEX `type_name_UNIQUE` (`loan_type` ASC) VISIBLE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Loan`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `project-ie0217-db`.`Loan` (
  `id_loan` INT UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT,
  `id_client` INT(9) UNSIGNED ZEROFILL NOT NULL,
  `loan_term` TINYINT(3) UNSIGNED NOT NULL,
  `creation_date` DATE NOT NULL DEFAULT (CURRENT_DATE),
  `id_loan_type` CHAR(2) NOT NULL,
  `currency` CHAR(3) NOT NULL,
  `principal` FLOAT UNSIGNED NOT NULL,
  `interest_rate` TINYINT(2) UNSIGNED NOT NULL,
  `monthly_payment` DECIMAL(9,2) UNSIGNED NOT NULL,
  `total_repayment` DECIMAL(9,2) UNSIGNED NOT NULL,
  `actual_debt` DECIMAL(9,2) UNSIGNED NOT NULL,
  PRIMARY KEY (`id_loan`),
  INDEX `id_client_idx` (`id_client` ASC) VISIBLE,
  INDEX `loan_type_idx` (`id_loan_type` ASC) VISIBLE,
  INDEX `fk_currency_loan_idx` (`currency` ASC) VISIBLE,
  CONSTRAINT `fk_id_client_loan`
    FOREIGN KEY (`id_client`)
    REFERENCES `project-ie0217-db`.`Client` (`id_client`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_loan_type_loan`
    FOREIGN KEY (`id_loan_type`)
    REFERENCES `project-ie0217-db`.`LoanType` (`id_loan_type`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_currency_loan_table`
    FOREIGN KEY (`currency`)
    REFERENCES `project-ie0217-db`.`Currency` (`id_currency`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`TransactionType`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `project-ie0217-db`.`TransactionType` (
  `id_tran_type` CHAR(2) NOT NULL,
  `transaction_type` VARCHAR(25) NOT NULL,
  PRIMARY KEY (`id_tran_type`),
  UNIQUE INDEX `id_tran_type_UNIQUE` (`id_tran_type` ASC) VISIBLE,
  UNIQUE INDEX `transaction_type_UNIQUE` (`transaction_type` ASC) VISIBLE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Transaction`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `project-ie0217-db`.`Transaction` (
  `id_transaction` INT UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT,
  `date_and_time` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `transaction_type` CHAR(2) NOT NULL,
  `currency` CHAR(3) NOT NULL,
  `transaction_amount` DECIMAL(8,2) UNSIGNED NOT NULL,
  `origin_account` INT UNSIGNED ZEROFILL NOT NULL,
  `target_account` INT UNSIGNED ZEROFILL NOT NULL,
  `detail` TINYTEXT NULL DEFAULT NULL,
  `previous_qty` DECIMAL(9,2) UNSIGNED NOT NULL,
  `present_qty` DECIMAL(9,2) UNSIGNED NOT NULL,
  PRIMARY KEY (`id_transaction`),
  UNIQUE INDEX `id_transaccion_UNIQUE` (`id_transaction` ASC) VISIBLE,
  INDEX `tran_type_idx` (`transaction_type` ASC) VISIBLE,
  INDEX `origin_account_idx` (`origin_account` ASC) VISIBLE,
  INDEX `target_account_idx` (`target_account` ASC) VISIBLE,
  INDEX `fk_currency_tran_idx` (`currency` ASC) VISIBLE,
  CONSTRAINT `fk_transaction_type_tran`
    FOREIGN KEY (`transaction_type`)
    REFERENCES `project-ie0217-db`.`TransactionType` (`id_tran_type`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_origin_account_tran`
    FOREIGN KEY (`origin_account`)
    REFERENCES `project-ie0217-db`.`BankAccount` (`id_account`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_target_account_tran`
    FOREIGN KEY (`target_account`)
    REFERENCES `project-ie0217-db`.`BankAccount` (`id_account`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_currency_tran`
    FOREIGN KEY (`currency`)
    REFERENCES `project-ie0217-db`.`Currency` (`id_currency`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`DepositCertificate`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`DepositCertificate` (
  `id_deposit_certificate` INT UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT,
  `id_account` INT UNSIGNED ZEROFILL NOT NULL,
  `cdp_term` TINYINT(2) UNSIGNED NOT NULL,
  `startline` DATE NOT NULL DEFAULT (CURRENT_DATE),
  `deadline` DATE NOT NULL,
  `principal` DECIMAL(9,2) UNSIGNED NOT NULL,
  `interest_rate` TINYINT(2) UNSIGNED NOT NULL,
  `capitalization_freq` TINYINT(2) UNSIGNED NOT NULL,
  `interest_penalty` TINYINT(2) UNSIGNED NOT NULL,
  `final_amount` DECIMAL(9,2) UNSIGNED NOT NULL,
  PRIMARY KEY (`id_deposit_certificate`),
  UNIQUE INDEX `id_deposit_certificate_UNIQUE` (`id_deposit_certificate` ASC) VISIBLE,
  INDEX `id_account_idx` (`id_account` ASC) VISIBLE,
  CONSTRAINT `fk_id_account_dc`
    FOREIGN KEY (`id_account`)
    REFERENCES `project-ie0217-db`.`BankAccount` (`id_account`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Payment`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Payment` (
  `id_payment` INT UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT,
  `id_loan` INT UNSIGNED ZEROFILL NOT NULL,
  `terms_completed` TINYINT(3) UNSIGNED NOT NULL DEFAULT 0,
  `total_capital_amount` DECIMAL(9,2) UNSIGNED NOT NULL,
  `total_interest_amount` DECIMAL(9,2) UNSIGNED NOT NULL,
  `total_capital_paid` DECIMAL(9,2) UNSIGNED NOT NULL DEFAULT 0,
  `total_interest_paid` DECIMAL(9,2) UNSIGNED NOT NULL DEFAULT 0,
  `capital_paid` DECIMAL(9,2) UNSIGNED NOT NULL DEFAULT 0,
  `interest_paid` DECIMAL(9,2) UNSIGNED NOT NULL DEFAULT 0,
  `date_of_payment` DATE NOT NULL DEFAULT (CURRENT_DATE),
  PRIMARY KEY (`id_payment`),
  INDEX `id_loan_idx` (`id_loan` ASC) VISIBLE,
  INDEX `date_of_payment_indx` (`date_of_payment` ASC) VISIBLE,
  CONSTRAINT `fk_id_loan_paymnt`
    FOREIGN KEY (`id_loan`)
    REFERENCES `project-ie0217-db`.`Loan` (`id_loan`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;


-- -----------------------------------------------------------------------
--                       Modificaciones  Iniciales                      --
-- -----------------------------------------------------------------------
-- Cabe destacar que el script anterior para la creacion de la base de datos
-- no fue el que se ejecuto inicialmente, sino el oficial en caso de replica.
-- Lastimosamente, no se guardo registro de la creada incialmente.
-- Por tanto, a continuacion se agregan los cambios progresivos que se fueron
-- haciendo a la DB con el fin de mantener un registro de las pruebas y erro-
-- res afrontadas.

-- NOTA IMPORTANTE: si parace que hay informacion faltante, es debido a que
-- 					para la adicion del segundo usuario, se modificaban los
-- 					queries, es decir no se realizo un query aparte. Por ende,
-- 					no se tiene registro de esos cambios.

-- Visualizacion de algunas tablas
SELECT * FROM `project-ie0217-db`.Client;
SELECT * FROM `project-ie0217-db`.Currency;
SELECT * FROM `project-ie0217-db`.BankAccount;
SELECT * FROM `project-ie0217-db`.LoanType;
SELECT * FROM `project-ie0217-db`.LoanReport;
SELECT * FROM `project-ie0217-db`.Payment;
SELECT * FROM `project-ie0217-db`.Loan;

-- Se agregan los primeros datos
INSERT INTO `project-ie0217-db`.Client(id_client, client_name, client_lastname)
VALUE("Ariel", "Romero");
INSERT INTO `project-ie0217-db`.Currency(id_currency, currency_name)
VALUE("USD", "Dolares");
INSERT INTO `project-ie0217-db`.BankAccount(id_client, currency)
VALUE("1", "CRC");
INSERT INTO `project-ie0217-db`.LoanType(id_loan_type, loan_type)
VALUE	("PE", "Personal"),
		("PR", "Prendario"),
        ("HP", "Hipotecario");

-- Se realiza una actualizacion
UPDATE `project-ie0217-db`.BankAccount
SET currency = "CRC"
WHERE id_account = 2;


-- -----------------------------------------------------------------------
--             Segundas Modificaciones  (Formato de Tablas)             --
-- -----------------------------------------------------------------------
-- Las segundas modificaciones consistieron en cambiar algunos valores por
-- default de las columnas, al igual que el formato de las cantidades aso-
-- ciadas a dinero por DECIMAL para evitar perdida de precision, ya que los
-- FLOAT o DOUBLE presentaban perdidas de precision lo cual puede llegar a
-- ser contraproducente en la vida real porque estamos trabajando con "dinero".
-- Asimismo, se agregan foreign keys que hicieron falta al igual que unos
-- indices.


-- Para modificar los valores por default que se me olvido al configurar inicialmente
-- Los (CURRENT_DATE) para que se genere la fecha automaticamente.
ALTER TABLE `project-ie0217-db`.`BankAccount`
MODIFY COLUMN `opening_date` DATE NOT NULL DEFAULT (CURRENT_DATE);
ALTER TABLE `project-ie0217-db`.`DepositCertificate`
MODIFY COLUMN `startline` DATE NOT NULL DEFAULT (CURRENT_DATE);
ALTER TABLE `project-ie0217-db`.`Loan`
MODIFY COLUMN `startline` DATE NOT NULL DEFAULT (CURRENT_DATE);
ALTER TABLE `project-ie0217-db`.`LoanReport`
MODIFY COLUMN `creation_date` DATE NOT NULL DEFAULT (CURRENT_DATE);
ALTER TABLE `project-ie0217-db`.`Payment`
ADD COLUMN made_on DATE NOT NULL DEFAULT (CURRENT_DATE);
ALTER TABLE `project-ie0217-db`.`Transaction`
MODIFY COLUMN `date_and_time` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP;

-- Los DECIMAL para el manejo de precision de los datos
ALTER TABLE `project-ie0217-db`.`Loan`
MODIFY COLUMN `monthly_payment` DECIMAL(9,2) UNSIGNED NOT NULL,
MODIFY COLUMN `total_repayment` DECIMAL(9,2) UNSIGNED NOT NULL,
MODIFY COLUMN `actual_debt` DECIMAL(9,2) UNSIGNED NOT NULL DEFAULT 0;

-- Agregar una nueva columna con fk e index
SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

ALTER TABLE `project-ie0217-db`.`Loan`
MODIFY COLUMN `creation_date` DATE NOT NULL DEFAULT (CURRENT_DATE),
ADD COLUMN `currency` CHAR(3) NOT NULL AFTER `id_loan_type`,
ADD INDEX `fk_currency_loan_idx` (`currency` ASC) VISIBLE,
ADD CONSTRAINT `fk_currency_loan`
    FOREIGN KEY (`currency`)
    REFERENCES `project-ie0217-db`.`Currency` (`id_currency`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION;
    
SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- Probar exportacion de datos
INSERT INTO `project-ie0217-db`.Loan(id_client, loan_term, id_loan_type, currency, principal, interest_rate, monthly_payment, total_repayment)
VALUE	(1, 24, "PE", "CRC", 1500000, 6, 76676.70, 1841841.25);

-- MySQL Script generated by Kristhel Quesada
-- jue 06 jun 2024 20:39 CST
-- Changing float values capital related to DECIMAL(9,2) or DECIMAL(12,2)

ALTER TABLE `project-ie0217-db`.`BankAccount`
MODIFY COLUMN balance DECIMAL(12,2) UNSIGNED NOT NULL DEFAULT 0;

ALTER TABLE `project-ie0217-db`.`DepositCertificate`
MODIFY COLUMN principal DECIMAL(9,2) UNSIGNED NOT NULL,
MODIFY COLUMN final_amount DECIMAL(9,2) UNSIGNED NOT NULL;

ALTER TABLE `project-ie0217-db`.`Transaction`
MODIFY COLUMN transaction_amount DECIMAL(8,2) UNSIGNED NOT NULL,
MODIFY COLUMN previous_qty DECIMAL(9,2) UNSIGNED NOT NULL,
MODIFY COLUMN present_qty DECIMAL(9,2) UNSIGNED NOT NULL;

ALTER TABLE `project-ie0217-db`.`Payment`
MODIFY COLUMN `total_capital_amount` DECIMAL(9,2) UNSIGNED NOT NULL,
MODIFY COLUMN `total_capital_paid` DECIMAL(9,2) UNSIGNED NOT NULL DEFAULT 0,
MODIFY COLUMN `capital_paid` DECIMAL(9,2) UNSIGNED NOT NULL DEFAULT 0,
MODIFY COLUMN `total_interest_amount` DECIMAL(9,2) UNSIGNED NOT NULL,
MODIFY COLUMN `total_interest_paid` DECIMAL(9,2) UNSIGNED NOT NULL DEFAULT 0,
MODIFY COLUMN `interest_paid` DECIMAL(9,2) UNSIGNED NOT NULL DEFAULT 0;


-- -----------------------------------------------------------------------
--           Terceras Modificaciones  (Prueba de Exportacion)           --
-- -----------------------------------------------------------------------
-- Anteriormente se creo un prestamo provisional, ahora se crea un payment
-- con el fin de probar la union de informaciones para generar el Reporte
-- de Prestamos que se solicita, Para ello inicialmente se penso hacer una
-- sola tabla que incluyera la info de Loan y Payment, se creia que para
-- ahorrar almacenamiento se podian hacer foreign keys para cada valor repe-
-- tido, pero un foreign key solo se puede asociar a una Primary Key, por
-- tanto hacer una tabla asi duplicaria demasiada informacion.

-- SOLUCION: Trabajar con tablas temporales, de tal manera que esta fuera
-- creada a la hora de implementar la consulta y se borrara al finalizar.
-- Asimismo, esta tabla se crearia mediante el uso de JOINS donde se uni-
-- ria la tabla Client, Loan y Payment.


-- Se crea una cuota de prueba para el prestamo de prueba.
INSERT INTO `project-ie0217-db`.Payment(id_loan, terms_completed, total_capital_amount, total_capital_paid, capital_paid, total_interest_amount, total_interest_paid, interest_paid)
VALUE(1, 23, 1500000, 58980.92, 58980.92, 103041.97, 7500, 7500);

-- Merge client, loan and payment (Este sera el reporte de prestamos)
-- Paso 0: Seleccionar la base de datos
USE `project-ie0217-db`;

-- Paso 1: Crear la tabla temporal
CREATE TEMPORARY TABLE loanreport
SELECT
	-- de la tabla de clientes
	Client.id_client,
	CONCAT(client_name, ' ', client_lastname) AS full_name,
    -- de la tabla de prestamos
    Loan.id_loan, loan_term, creation_date, id_loan_type, currency, principal,
    interest_rate, monthly_payment, total_repayment, actual_debt,
    -- de la tabla de cuotas (payments)
    id_payment, terms_completed, total_capital_amount, total_interest_amount,
    total_capital_paid, total_interest_paid, capital_paid, interest_paid, made_on
FROM Client
INNER JOIN Loan ON Client.id_client = Loan.id_client
INNER JOIN Payment ON Loan.id_loan = Loan.id_loan;
SELECT * FROM `project-ie0217-db`.loanreport;

-- Paso 2: Eliminar la tabla temporal
DROP TEMPORARY TABLE `project-ie0217-db`.loanreport;

-- Funciona!


-- ------------------------------------------------------------------------
--               Cuarta Modificacion (Adicion de mas Datos)              --
-- ------------------------------------------------------------------------
-- Inicialmente se borra el prestamo y pago de pruebas para dejar la DB lista
-- para modificaciones y pruebas limpias en el codigo de C++.
-- Se realizan varias modificaciones de autoincrements ya que se presentaron
-- algunos errores de insercion.

-- Ver estado de las tablas
SELECT * FROM `project-ie0217-db`.Client;
SELECT * FROM `project-ie0217-db`.BankAccount;
SELECT * FROM `project-ie0217-db`.DepositCertificate;
SELECT * FROM `project-ie0217-db`.Loan;
SELECT * FROM `project-ie0217-db`.Payment;
SELECT * FROM `project-ie0217-db`.Transaction;
SELECT * FROM `project-ie0217-db`.TransactionType;

-- Borramos primero los payments, luego el prestamo y revisamos autoincrement
-- Borrar payment
DELETE FROM `project-ie0217-db`.Payment
WHERE id_payment = 1;
-- Borrar prestamos
DELETE FROM `project-ie0217-db`.Loan
WHERE id_loan = 1;

-- Ver autoincrement
SELECT AUTO_INCREMENT
FROM information_schema.TABLES
WHERE TABLE_SCHEMA = 'project-ie0217-db'
AND TABLE_NAME = 'Loan'; -- si se elimina un elemento, el AI no se reduce

-- Modificar autoincrements
ALTER TABLE `project-ie0217-db`.Loan AUTO_INCREMENT = 1;
ALTER TABLE `project-ie0217-db`.Payment AUTO_INCREMENT = 1;
ALTER TABLE `project-ie0217-db`.Client AUTO_INCREMENT = 3;

-- Agregamos Clientes primero, pero sin las cuentas
INSERT INTO `project-ie0217-db`.Client(client_name, client_lastname)
VALUES ("Luis", "Murillo"),
       ("Celeste", "Abarca"),
       ("Alejandro", "Perez"),
       ("Matias", "McTagart"),
       ("Nicole", "Araya"),
       ("Matthew", "Dingott"),
       ("Luis Fernando", "Castro"),
       ("Nayeli", "Solano"),
       ("Eithan", "Alvarado"),
       ("Juan Carlos", "Soto"),
       ("Belen", "Solano"),
       ("Dereck", "Diaz"),
       ("Anthony", "Quesada");
       
UPDATE `project-ie0217-db`.Client
SET id_client = id_client - 13
WHERE id_client > 2;
SELECT * FROM `project-ie0217-db`.Client;
ALTER TABLE `project-ie0217-db`.Client AUTO_INCREMENT = 16;

-- Agregamos Cuentas
-- Teniamos un problema donde el indice estaba configurado para ser unico
-- entonces vamos a cambiarlo: primero lo borramos y luego lo volvemos a crear
SHOW CREATE TABLE `project-ie0217-db`.BankAccount;
SET FOREIGN_KEY_CHECKS = 0;
ALTER TABLE `project-ie0217-db`.BankAccount ADD INDEX `idClient_inBA_indx` (`id_client`);
ALTER TABLE `project-ie0217-db`.BankAccount DROP INDEX `id_client_UNIQUE`;
SET FOREIGN_KEY_CHECKS = 1;

INSERT INTO `project-ie0217-db`.BankAccount(id_client, currency, balance)
VALUES (5, 'CRC', 478000.53),
       (6, 'CRC', 918340.91),
       (3, 'CRC', 758122.91),
       (8, 'USD', 4121.90),
       (7, 'USD', 15022.01),
       (3, 'USD', 6780.51),
       (8, 'CRC', 1437711.04),
       (10, 'CRC', 555773.81),
       (9, 'CRC', 85679.97),
       (13, 'CRC', 236031.37),
       (12, 'USD', 790.45),
       (15, 'USD', 2200.00),
       (11, 'CRC', 9310000.00),
       (9, 'USD', 61.50);

-- Actualizar las cuentas
-- Los indices estaban para ser unicos entonces vamos a arreglar eso:
SET FOREIGN_KEY_CHECKS = 0;
ALTER TABLE `project-ie0217-db`.Client ADD INDEX `id_dolares_account_indx` (`id_dolares_account`);
ALTER TABLE `project-ie0217-db`.Client DROP INDEX `id_dolares_account_UNIQUE`;
ALTER TABLE `project-ie0217-db`.Client ADD INDEX `id_colones_account_indx` (`id_colones_account`);
ALTER TABLE `project-ie0217-db`.Client DROP INDEX `id_colones_account_UNIQUE`;
SET FOREIGN_KEY_CHECKS = 1;

-- Habia errores en el autoincrement
UPDATE `project-ie0217-db`.BankAccount
SET id_account = id_account - 14
WHERE id_account > 2;
SELECT * FROM `project-ie0217-db`.BankAccount;
ALTER TABLE `project-ie0217-db`.BankAccount AUTO_INCREMENT = 17;

-- Cliente 1
UPDATE `project-ie0217-db`.Client
SET id_colones_account = 2
WHERE id_client = 1;

-- Cliente 2
UPDATE `project-ie0217-db`.Client
SET id_dolares_account = 1
WHERE id_client = 2;

-- Cliente 3
UPDATE `project-ie0217-db`.Client
SET id_colones_account = 5, id_dolares_account = 8
WHERE id_client = 3;

-- Cliente 4
-- No hay datos para actualizar

-- Cliente 5
UPDATE `project-ie0217-db`.Client
SET id_colones_account = 3
WHERE id_client = 5;

-- Cliente 6
UPDATE `project-ie0217-db`.Client
SET id_colones_account = 4
WHERE id_client = 6;

-- Cliente 7
UPDATE `project-ie0217-db`.Client
SET id_dolares_account = 7
WHERE id_client = 7;

-- Cliente 8
UPDATE `project-ie0217-db`.Client
SET id_colones_account = 9, id_dolares_account = 6
WHERE id_client = 8;

-- Cliente 9
UPDATE `project-ie0217-db`.Client
SET id_colones_account = 11, id_dolares_account = 16
WHERE id_client = 9;

-- Cliente 10
UPDATE `project-ie0217-db`.Client
SET id_colones_account = 10
WHERE id_client = 10;

-- Cliente 11
UPDATE `project-ie0217-db`.Client
SET id_colones_account = 15
WHERE id_client = 11;

-- Cliente 12
UPDATE `project-ie0217-db`.Client
SET id_dolares_account = 13
WHERE id_client = 12;

-- Cliente 13
UPDATE `project-ie0217-db`.Client
SET id_colones_account = 12
WHERE id_client = 13;

-- Cliente 14
-- No hay datos para actualizar

-- Cliente 15
UPDATE `project-ie0217-db`.Client
SET id_dolares_account = 14
WHERE id_client = 15;


-- ------------------------------------------------------------------------
--            Modificacion de las Tablas, revision de indices            --
-- ------------------------------------------------------------------------
-- 1. Revision de BankAccount
-- Se crean indices para: id_account, id_client, currency
-- Esta bien!

-- 2. Revision de Client
-- Se crean indices para: id_client, client_name, client_lastname, id_colones_account, id_dolares_account
-- Se agregan entonces: client_name, client_lastname
ALTER TABLE `project-ie0217-db`.Client
ADD INDEX `nameClient_indx` (`client_name`),
ADD INDEX `lastnameClient_indx` (`client_lastname`);

-- 3. Revision de Currency
-- Esta bien!

-- 4. Revision de DepositCertificate
-- Se crean indices para: id_deposit_certificate, id_account, capitalization_freq (para la periocidad de retribucion de los intereses)
-- Se piensa sea: diario (ver si se puede hacer un update), mensual o una vez se cumpla el cdp_term
-- Ademas se busca crear un indice para startline y deadline, para hacer los updates diarios o mensuales con base en startline y el
-- deadline para corroborar si ya se cumplio. Ademas el cdp_term para construir el deadline
-- Se agregan entonces: capitalization_freq, startline, deadline
ALTER TABLE `project-ie0217-db`.DepositCertificate
ADD INDEX `cdp_term_indx` (`cdp_term`),
ADD INDEX `startline_indx` (`startline`),
ADD INDEX `deadline_indx` (`deadline`),
ADD INDEX `capitalization_freq_indx` (`capitalization_freq`);

-- 5. Revision de Loan
-- Se crean indices para: id_loan, id_client, creation_date, id_loan_type, currency, actual_debt e interest_rate (por si se hace la tasa variable)
-- Se agregan entonces: actual_debt (para ir actualizando conforme se hacen los pagos), creation_date e interest_rate
ALTER TABLE `project-ie0217-db`.Loan
ADD INDEX `actual_debt_indx` (`actual_debt`),
ADD INDEX `interest_rate_indx` (`interest_rate`);
ALTER TABLE `project-ie0217-db`.Loan
ADD INDEX `creation_date_indx` (`creation_date`);

-- Se modifica para que actual_debt sea no nulo y no tenga valor por default.
ALTER TABLE `project-ie0217-db`.Loan
MODIFY COLUMN actual_debt DECIMAL(9,2) UNSIGNED NOT NULL;

-- Se agrega una columna que contiene la fecha de la proxima cuota
-- ALTER TABLE `project-ie0217-db`.`Transaction`
-- ADD COLUMN `next_quote` DATE NOT NULL DEFAULT (CURRENT_DATE) AFTER `actual_debt`,
-- ADD INDEX `fk_nxtQuote_indx` (`next_quote` ASC) VISIBLE;

-- 6. Revision de LoanType
-- Esta bien!

-- 7. Revision de Payment
-- Se crean indices para: id_payment, id_loan, made_on
-- Se agrega entonces: made_on
ALTER TABLE `project-ie0217-db`.Payment
ADD INDEX `made_on_indx` (`made_on`);

-- 8. Revision de Transaction
-- Se crean indices para: id_transaction, date_and_time, transaction_type, origin_account, target_account
-- Se agrega entonces: date_and_time
ALTER TABLE `project-ie0217-db`.Transaction
ADD INDEX `date_and_time_indx` (`date_and_time`);

-- Agregar currency que corresponde al target account
ALTER TABLE `project-ie0217-db`.`Transaction`
ADD COLUMN `currency` CHAR(3) NOT NULL AFTER `transaction_type`,
ADD INDEX `fk_currency_tran_idx` (`currency` ASC) VISIBLE,
ADD CONSTRAINT `fk_currency_tran`
    FOREIGN KEY (`currency`)
    REFERENCES `project-ie0217-db`.`Currency` (`id_currency`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION;

-- 9. Revision de TransactionType
-- Esta bien!

-- ----------------------------------------------------------------------
--            Adicion de contenido a Tabla Transaction Type            --
-- ----------------------------------------------------------------------
INSERT INTO `project-ie0217-db`.TransactionType(id_tran_type, transaction_type)
VALUES ("RT", "Retiro"),
	   ("DP", "Deposito"),
       ("TR", "Transferencia"),
       ("AP", "Abono a prestamo");
SELECT * FROM `project-ie0217-db`.TransactionType;

-- ----------------------------------------------------------------------
--                          Ideas  pendientes                          --
-- ----------------------------------------------------------------------
-- 1. Crear una tabla para capitalization_freq en la cual se van a incluir
--    lo que seria:
-- 	  -> D: diario (no es util pero es para ver si la actualizacion se realiza)
-- 	  -> M: mensual
-- 	  -> F: final del plazo asignado

-- 2. Tablas generadas para las actualizaciones.
-- 3. Uso de transactions.
-- 4. Definir plazos predeterminados/fijos para los cdp's. Asi se crea tabla
-- 	  adicional para no repetir tantos datos.


-- ----------------------------------------------------------------------
--                          Pruebas de Queries                         --
-- ----------------------------------------------------------------------
SELECT * FROM `project-ie0217-db`.BankAccount
WHERE YEAR(opening_date)=YEAR(CURDATE());

-- Changes not implemented
-- USE `project-ie0217-db`;
-- SELECT * FROM Loan;
-- SELECT DATE_ADD(Loan.creation_date, INTERVAL 1 MONTH);


-- ----------------------------------------------------------------------
--           Actualizacion de las tablas con ON CASCADE ALL            --
-- ----------------------------------------------------------------------
-- 1. Revision de BankAccount
ALTER TABLE `project-ie0217-db`.BankAccount
ADD CONSTRAINT `fk_id_client_ba`
    FOREIGN KEY (`id_client`)
    REFERENCES `project-ie0217-db`.`Client` (`id_client`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
ADD CONSTRAINT `fk_currency_ba`
    FOREIGN KEY (`currency`)
    REFERENCES `project-ie0217-db`.`Currency` (`id_currency`)
    ON DELETE CASCADE
    ON UPDATE CASCADE;

ALTER TABLE `project-ie0217-db`.BankAccount DROP FOREIGN KEY currency;
ALTER TABLE `project-ie0217-db`.BankAccount DROP FOREIGN KEY id_client;


-- 2. Revision de Client
ALTER TABLE `project-ie0217-db`.Client
ADD CONSTRAINT `fk_id_colones_account`
    FOREIGN KEY (`id_colones_account`)
    REFERENCES `project-ie0217-db`.`BankAccount` (`id_account`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
ADD CONSTRAINT `fk_id_dolares_account`
    FOREIGN KEY (`id_dolares_account`)
    REFERENCES `project-ie0217-db`.`BankAccount` (`id_account`)
    ON DELETE CASCADE
    ON UPDATE CASCADE;

ALTER TABLE `project-ie0217-db`.Client DROP FOREIGN KEY id_colones_account;
ALTER TABLE `project-ie0217-db`.Client DROP FOREIGN KEY id_dolares_account;


-- 4. Revision de DepositCertificate
ALTER TABLE `project-ie0217-db`.DepositCertificate
ADD CONSTRAINT `fk_id_account_dc`
    FOREIGN KEY (`id_account`)
    REFERENCES `project-ie0217-db`.`BankAccount` (`id_account`)
    ON DELETE CASCADE
    ON UPDATE CASCADE;

ALTER TABLE `project-ie0217-db`.DepositCertificate DROP FOREIGN KEY id_account_dc;


-- 5. Revision de Loan
ALTER TABLE `project-ie0217-db`.Loan
ADD CONSTRAINT `fk_id_client_loan`
    FOREIGN KEY (`id_client`)
    REFERENCES `project-ie0217-db`.`Client` (`id_client`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
ADD CONSTRAINT `fk_loan_type_loan`
    FOREIGN KEY (`id_loan_type`)
    REFERENCES `project-ie0217-db`.`LoanType` (`id_loan_type`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
ADD CONSTRAINT `fk_currency_loan_table`
    FOREIGN KEY (`currency`)
    REFERENCES `project-ie0217-db`.`Currency` (`id_currency`)
    ON DELETE CASCADE
    ON UPDATE CASCADE;

ALTER TABLE `project-ie0217-db`.Loan DROP FOREIGN KEY fk_currency_loan;
ALTER TABLE `project-ie0217-db`.Loan DROP FOREIGN KEY id_client_loan;
ALTER TABLE `project-ie0217-db`.Loan DROP FOREIGN KEY loan_type_loan;


-- 7. Revision de Payment
ALTER TABLE `project-ie0217-db`.Payment
ADD CONSTRAINT `fk_id_loan_paymnt`
    FOREIGN KEY (`id_loan`)
    REFERENCES `project-ie0217-db`.`Loan` (`id_loan`)
    ON DELETE CASCADE
    ON UPDATE CASCADE;

ALTER TABLE `project-ie0217-db`.Payment DROP FOREIGN KEY id_loan_paymnt;



-- 8. Revision de Transaction
ALTER TABLE `project-ie0217-db`.Transaction
ADD CONSTRAINT `fk_transaction_type_tran`
    FOREIGN KEY (`transaction_type`)
    REFERENCES `project-ie0217-db`.`TransactionType` (`id_tran_type`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
ADD CONSTRAINT `fk_origin_account_tran`
    FOREIGN KEY (`origin_account`)
    REFERENCES `project-ie0217-db`.`BankAccount` (`id_account`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
ADD CONSTRAINT `fk_target_account_tran`
    FOREIGN KEY (`target_account`)
    REFERENCES `project-ie0217-db`.`BankAccount` (`id_account`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
ADD CONSTRAINT `fk_currency_trans`
    FOREIGN KEY (`currency`)
    REFERENCES `project-ie0217-db`.`Currency` (`id_currency`)
    ON DELETE CASCADE
    ON UPDATE CASCADE;

ALTER TABLE `project-ie0217-db`.Transaction DROP FOREIGN KEY transaction_type_t;
ALTER TABLE `project-ie0217-db`.Transaction DROP FOREIGN KEY target_account_t;
ALTER TABLE `project-ie0217-db`.Transaction DROP FOREIGN KEY origin_account_t;
ALTER TABLE `project-ie0217-db`.Transaction DROP FOREIGN KEY fk_currency_tran;


