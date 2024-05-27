# IE-0217 Proyecto Final
Repositorio de desarrollo del proyecto final del curso de Estructuras Abstractas de Datos y Algoritmos para Ingeniería, UCR

### Desarrolladores:
1. Oscar Porras Silesky, C16042
2. Anthony Brenes Rodriguez, C11238
3. Kristhel Quesada Lopez, C06153

### Indice
1. [Descripción General](#descripcion-general)
2. [Investigación Previa](#investigacion-previa)

    - [Operaciones Bancarias](#operaciones-bancarias-y-sus-funciones)
    - [Prestamos e Intereses](prestamos-y-tipos-de-interes)
    - [Tipos de Cambio](#tipos-de-cambio)

3. [Descripción de Diseño](#descripcion-de-diseño)
    - [Diseño de la Base de Datos](#diseño-de-la-base-de-datos)
    - [Diseño del Programa](#diseño-del-programa)



<!-- Inicio del Contenido -->
## Descripcion General
El siguiente proyecto pretende implementar un dise;o que cumpla con los siguientes objetivos:

1. Crear una sistema de gestion bancaria enfocada al uso por parte de los __agentes de dicha institucion__ a traves de ventanilla.
2. El sistema debe ser capaz de soportar dos modos de operacion: _atencion al cliente_ y _obtener informacion sobre prestamos (pesonales, prendario e hipotecarios)_.
3. En el area de atencion al cliente, el sistema debe:
    - Poder agregar un nuevo cliente, agregar cuenta (colones o dolares) al cliente (maximo 1 por moneda), creacion de prestamo o creacion de Certificados de Deposito (CDP).
    - Ademas debe poder permitir transacciones como depositos, retiros, transferencias y abonos a prestamos entre cuentas personales o de terceros, siempre y cuando sea entre cuentas pertenecientes a la misma entidad bancaria.
    - Finalmente el sistema debe ser capaz de entregar reportes como lo son: Registro de transacciones y Reporte de Prestamos (tabla de amortizacion).
4. El sistema debe ser capaz de gestionar la informacion requerida mediante bases de datos SQL.
5. La implementacion y desarrollo del problema a resolver debe ser realizado mediante el uso de C++ utilizando el paradigma de programacion de Programacion Orientada a Objetos, al igual que el uso de estructuras, defines, o enumeraciones.
6. Asimismo, se solicita que la documentacion del mismo sea implementada correctamente y utilizada en conjunto con el generador de Doxygen.

<br>



## Investigacion Previa

<!-- Investigacion referente a conceptos del proceso bancario -->
### Operaciones bancarias y sus funciones
Entre las operaciones bancarias que se realizaran en ventanilla y algunos beneficios bancarios a los cuales los clientes pueden estar subscritos con sus cuentas, se describen los siguientes:

1. __Deposito:__
2. __Retiro:__
3. __Transferencias entre mismos clientes:__
4. __Abonos a prestamos propios o de terceros:__
5. __Certificado de deposito a plazo:__

<br>

### Prestamos y tipos de interes
Un prestamo, bajo el contexto del proyecto, se define como el proceso mediante el cual una entidad bancaria presta y entrega de un monto completo de dinero que el cliente solicite, todo a cambio de un compromiso por parte del cliente de delvolver el dinero solicitado a cambio de pagos de mensuales de menor cantidad (cuotas) a un plazo acordado entre el cliente y el banco, hasta que complete la cantidad solicitada mas intereses.

Ahora, estos intereses pueden ser fijos o pueden ser variables de tal manera que, en Costa Rica, dicha variacion esta sujeta a la Tasa Basica Pasiva adicional a un margen adicional que define la entidad bancaria. Adicionalmente, las entidades bancarias pueden emitir diferentes tipos de prestamos, entre ellos, se destacan los siguientes:

#### A. __Prestamo Personal__
Un prestamo personal pueden ser solicitados para una amplia variedad de fines personales, como consolidar deudas, cubrir gastos médicos, financiar viajes, etc. Este se carcateriza por:

- Para solicitarlos usualmente no se requiere de una garantia adicional pero requiere que el solicitante sea asalariado con minimo 1 año desde que inicio o 
- Su plazo puede extenderse dependiendo del sector en el cual trabaje, por ejemplo: hasta 5 años para un empleado privado y hasta 8 años para un empleado publico.
- Sus montos no suelen ser elevados pero podrian serlo aceptando garantias.

#### B. __Prestamo Prendario__
Esta clase de creditos tienden a ser solicitados para la compra de bienes específicos, como vehículos o maquinaria. Entre sus caracteristicas se encuentran:

- Requieren una garantía (colateral), que usualmente es el bien que se está adquiriendo, de tal forma que el prestammista (entidad bancaria) puede tomar posesión del colateral si el cliente no cumple con los pagos.
- Su plazo puede extenderse hasta 8 años, aunque el plazo tiende a estar delimitado por la vida util del bien que se esta adquiriendo. Por ejemplo, un vehiculo se dice que aproximadamente pierde su valor a los 5 años dependiendo del modelo y sus especificaciones, por lo que el banco debe asegurarse que en caso que se requiera tomar posesion del bien, el vehiculo no este a punto de entrar en periodo de desvalorizacion. En resumen, se define plazos de maximo la vida util del bien.
- Sus montos (cantidad que solicita el cliente) suelen ser de magnitud intermedia, razon por la cual se requiere usualmente de un fiador o garantia.
- Se requiere de buen record crediticio, una garantia y ser asalariado por consecuencia.


#### C. __Prestamo Hipotecario__
Este tipo de prestamos se solicitan usualmente al requerir de la compra o desarrollo de bienes inmuebles como lotes, casas o propiedades comerciales. Entre sus principales caracteristicas destacan:

- Requieren una garantía que viene siendo el bien inmueble como tal, donde el prestamista toma posecion del mismo. Para ello se requiere de una evaluacion del bien mediante un perito que determine si dicho bien es capaz de cubrir el prestamo solicitado en caso de que no pueda ser cubierto.
- Su plazo puede extenderse hasta 40 años dependiendo, ya que al igual que los prendarios, este depende de la vida util del bien inmueble que se esta adquiriendo. Usualmente, la vida util de una casa por ejemplo, ronda los 40-50 años, po lo que su plazo maximo suele ser menor a eso.
- Sus montos (cantidad que solicita el cliente) suelen ser altos, razon por la cual se requiere usualmente de un estrictamente de una garantia y estudio detallado del valor del bien.
- Se requiere de buen record crediticio, una garantia hipotecaria, una tasación del inmueble y ser asalariado por consecuencia.


#### Resumen de Solicitudes de Prestamos segun el tipo
| Característica      | Préstamo Personal              | Préstamo Prendario               | Préstamo Hipotecario               |
|---------------------|--------------------------------|----------------------------------|------------------------------------|
| **Propósito**       | Variado                        | Compra de bienes específicos     | Compra de inmuebles                |
| **Garantía**        | No                             | Bien adquirido                   | Inmueble adquirido                 |
| **Monto**           | Bajo                         | Intermedio                       | Alto                              |                              |
| **Plazo**           | Corto (meses hasta 5-8 años)     | Medio (hasta 8 años) pero depende de la vida util del bien adquirido               | Largo (hasta 40-50 años) igual depende de la vida util del bien         |
| **Requisitos**      | Calificación crediticia y serasalariado        | Calificación crediticia, colateral y serasalariado | Calificación crediticia, tasación del inmueble y ser asalariado |

<br>

### Tipos de Cambio
Un cliente de una entidad bancaria puede tener distintas cuentas con tipos de moneda distinta. Por tanto, un mismo cliente puede tener una cuenta en colones y otra en dolares por ejemplo. El tipo de cambio suele estar especificado por la entidad bancaria, donde para el caso de Costa Rica, el Banco Central de Costa Rica se encarga de fijar un valor base que utilizan el resto de Bancos como referencia. El tipo de cambio basicamente se define como el precio de una unidad monetaria de un país, expresado en términos de una moneda distinta y suelen determinarse dos tipos de cambio distintos: uno para venta y otro para compra.

Para el desarrollo del presente proyecto, se utilizaran conversiones de dolares a colones y viceversa, en casos cuando se desee realizar un abono en dolares a una cuenta en colones o cualquier otra transaccion que requiera dos tipos de moneda distintas. La conversion de cada una estara dada por las siguientes formulas:

<div style="text-align:center;">

$\text{Monto en USD} \ (venta) = \frac{\text{Monto en CRC}}{\text{Tipo de Cambio}}$


$\text{Monto en CRC} \ (compra) = \text{Monto en USD} \times \text{Tipo de Cambio}$

</div>



<br>



## Descripcion de Diseño

### Diseño de la Base de Datos
<br>

### Diseño del Programa