# IE-0217 Proyecto Final
Repositorio de desarrollo del proyecto final del curso de Estructuras Abstractas de Datos y Algoritmos para Ingeniería, UCR

### Desarrolladores:
1. Oscar Porras Silesky, C16042
2. Anthony Brenes Rodriguez, C11238
3. Kristhel Quesada Lopez, C06153

### Indice
1. [Descripción General](#descripcion-general)
2. [Investigación Previa](#investigacion-previa)

    -   [Operaciones Bancarias](#operaciones-bancarias-y-sus-funciones)
    - [Prestamos e Intereses](prestamos-y-tipos-de-interes)

3. [Descripción de Diseño](#descripcion-de-diseño)



<!-- Inicio del Contenido -->
## Descripcion General
<br>



## Investigacion Previa

<!-- Investigacion referente a conceptos del proceso bancario -->
### Operaciones bancarias y sus funciones
1. __Transaccion:__  Al definir las operaciones bancarias, es importante saber el significado de una transacción. Una transacción es cualquier entrada o salida de dinero de una cuenta de un cliente de una entidad bancaria. Entre las operaciones bancarias que se realizan en ventanilla y algunos beneficios bancarios a los cuales los clientes pueden estar subscritos con sus cuentas, se describen los siguientes:

2. __Deposito:__ Un depósito es un proceso bancario donde un cliente puede realizar un ingreso manual de dinero a una cuenta de un cliente de un banco. Este método de transacción se puede efectuar de forma electrónica a través de un sistema. Para este tipo de transacción no es necesario que el cliente posea una cuenta bancaria a su nombre debido a que solo ocupa dinero en efectivo para llevar a cabo dicha acción.

<p style="text-indent: 2em;">Para realizar este tipo de transacción, el cliente debe brindar al sistema los siguientes datos para que se realice correctamente:

- Número de cuenta a la que se desea hacer el depósito.
- Número de cédula y nombre de la persona de quién realiza el depósito.
- Nombre de la persona que recibirá el dinero. 
- El tipo de moneda.
- Monto que el cliente desea depositar.
- Concepto y motivo que corresponde al detalle de la transacción.

<p style="text-indent: 2em;"> En el programa, la funcionalidad de depósito es esencial ya que permite la transacción de dinero a una cuenta de un cliente. Para llevar a cabo esto el sistema procesa y registra el ingreso de fondos a la cuenta que se desea depositar el dinero, verificando que el monto sea válido y sumándolo al monto actual de la cuenta del cliente. El depósito se registra en la base de datos del sistema, incluyendo detalles como el ID de la cuenta, el monto depositado y la fecha de la transacción.

3. __Retiro:__ Un retiro es una operación bancaria donde un cliente puede realizar una extracción de dinero de su propia cuenta bancaria. Esta transacción se puede realizar mediante un sistema bancario y para llevarla a cabo es necesario que el cliente posea una cuenta registrada, de lo contrario no se podría efectuar.

<p style="text-indent: 2em;">Para realizar un retiro de dinero, el cliente debe brindar al sistema los siguientes datos para que se realice correctamente:

- Número de cuenta a la que se desea hacer la extracción de dinero.
- Número de cédula y nombre de la persona de quién realiza la transacción y dueña de la cuenta.
- Monto que el cliente desee extraer.

<p style="text-indent: 2em;"> En el programa, la funcionalidad de retiro permite la resta de dinero a una cuenta del cliente. Para llevar a cabo esto el sistema valida que hayan fondos en la cuenta y procesa y registra el retiro de fondos de la cuenta que se desea extraer el dinero, verificando que el monto sea válido y restándoselo al monto actual de la cuenta del cliente. El retiro se registra en la base de datos del sistema, incluyendo detalles como el ID de la cuenta, el monto retirado y la fecha de la transacción.

4. __Transferencias entre mismos clientes:__ Una transferencia entre mismos clientes es un método bancario rápido que posibilita a un emisor el paso de dinero desde su cuenta bancaria a otra cuenta de otro cliente. Este proceso se puede realizar de forma digital a través de un sistema bancario. La ventaja de este tipo de transacción es que permite transferir dinero ya sea de una cuenta en colones o dólares a otra cuenta de la misma o diferente moneda. En cuyo caso que se realice una tranferencia entre cuentas de diferente moneda se debe de aplicar el tipo de cambio de moneda correspondiente. 

<p style="text-indent: 2em;">Para realizar una transferencia bancaria, el cliente ocupa proporcionar al sistema los siguientes datos para que el proceso se realice efectivamente: 

- Número de cuenta a la que se desea hacer la transferencia.
- Número de cédula y nombre de la persona de quién realiza la transferencia.
- Nombre de la persona que recibirá el dinero. 
- Monto que el cliente desee transferir.
- Concepto y motivo que corresponde al detalle de la transacción.
- El tipo de moneda.

<p style="text-indent: 2em;">En el programa, la funcionalidad de transferencias bancarias son importantes ya que permite la transacción de dinero a una cuenta de un cliente a otra. Para llevar a cabo este método el sistema verifica que la cuenta de origen posea fondos suficientes y luego se le deben proporcionar los datos de la transacción para poder validar la operación, despúes de este paso el sistema rebaja el dinero de la cuenta de origen y la suma al monto actual de la cuenta destino.

5. __Abonos a prestamos propios o de terceros:__ En el contexto de abonar a un préstamo, los abonos son pagos extraordinarios que un cliente realiza para reducir la vida del préstamo o la cuota mensual. Para realizar esta transacción, no es necesario que el cliente tenga una cuenta bancaria o un préstamo como tal con la entidad bancaria. 

<p style="text-indent: 2em;">Para realizar un abono a un préstamo, el cliente ocupa proporcionar al sistema los siguientes datos para que el proceso se realice efectivamente: 

- Número de cédula y nombre de la persona de quién realiza la transacción.
- Nombre y número de cédula de la persona asociada al préstamo. 
- Monto que el cliente desea abonar.

<p style="text-indent: 2em;">En el programa, la funcionalidad de abonar préstamos, el sistema valida la información del préstamo y del cliente, luego procesa los detalles de la transacción financiera y actualiza en tiempo real el saldo del préstamo y otros registros relevantes. Despúes de que la transacción haya sido efectuada el sistema generará de manera automática las confirmaciones y recibos para el cliente con los detalles del abono.

6. __Certificado de deposito a plazo:__ Un certificado de depósito (CDP) es un producto financiero ofrecido por los bancos donde una persona deposita una cantidad específica de dinero en una cuenta de ahorro por un período de tiempo acordado, que puede variar desde unos pocos meses hasta varios años. Durante este período, el banco paga intereses sobre el dinero depositado. Los CDP suelen ofrecer tasas de interés más altas que las cuentas de ahorro estándar, pero a cambio, el dinero no se puede retirar hasta que el plazo del CDP haya vencido sin incurrir en penalizaciones.

<p style="text-indent: 2em;">En el programa, los clientes pueden abrir un CDP seleccionando el monto y el plazo deseado. El sistema calcula automáticamente los intereses y gestiona las restricciones de retiro durante el período. Al vencimiento, el cliente puede retirar el dinero con los intereses o renovar el CD. Es una forma segura y rentable de ahorrar a largo plazo.

<br>



## Descripcion de Diseño
### Diseño de la Base de Datos
![Esquema de base de datos](esquema.png)

<br>

