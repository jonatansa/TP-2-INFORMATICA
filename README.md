# TP-2-INFORMATICA
## *Prof: CORBALAN Damian*
## *ENUNCIADOS*
## *PARTE 1 - Entrega 26/10/2020*

###### ***Ejercicio 35***
> HACER UN PROGRAMA QUE TOME LOS DATOS DE CONTACTO DE UNA PERSONA (Nombre, Apellido, Edad,Telefono, Mail), Y LOS CARGUE EN FORMA DIRECTA, EN UNA PILA 
DE MEMORIA DINAMICA. IMPRIMIR EN PANTALLA Y CARGAR EN UN ARCHIVO LLAMADO "Contactos.dat", DE ORGANIZACION SECUENCIAL, LOS REGISTROS INGRESADOS POR EL USUARIO 
SI LA PERSONA TIENE UNA EDAD MAYOR A 21 AÑOS.

###### ***Ejercicio 36*** 
> Hacer un programa que lea el archivo "contactos.dat" creado en el ejercicio 35 y crear una lista, en memoria dinamica, ordernarla alfabeticamene. Una vez 
creada la lista guardarla en un archivo de organizacion directa llamodo "contactos_ordenados.dat" imprimiendola en pantalla.

###### ***Ejercicio 37*** 
>Exite un archivo llamado "datos.dat",de tipo binario, cuya organizacion es secuencial.Los datos estan organizados segun la siguiente estructura:

	struct d{
			long clave;
			char d[30];
			struct d *z;
			char b;
			unsigned char tipo;
    };
  Se pide, realizcar una funcion que pase como parametro la clave(id), entre otros parametros y apile dos valores, la clave
	y su posicion fisica respecto al archivo(registros 1,2,etc), si es que el campo tipo tiene el bit 4 con valor 1. En caso
	de no encontrarlo mostrar en pantalla "Registro no encontrado".La funcion debe devolver el puntero de pila. Realizar el main
	con varias llamadas a dicha funcion y proceder a motrar las descripciones del archivo, mediante la pila como accesos
	directo, NO USAR VARIABLES GLOBALES.

###### ***Ejercicio 38*** 
>Hacer una cola con los valores muestreados de un cuarto de ciclo de una señal sinuidal, en 8 bits, para luego recorrerla y recomponer la señal completa.
Las muestras deberan ir de 127 a -127 utilizando el BMS en 1 para los valores negativos y en 0 para los valores positivos. Imprimir en pantalla los valores.

###### ***Ejercicio 39*** 
>Hacer un programa que tome los datos de medicion de potencia, cargados por el usuario,
de un sistema de medicion a distancia.

Los datos que cargara el usuario tienen la siguiente estructura:

    char desc[60];
    unsigned char potencia;
    unsigned int estado;
    
Donde estado es la multiplicacion del valor ASCII de la primer letra de la descripcion por la potencia.
Los datos cargados se deberan guardar en una lista ordenada, de mayor a menor, del valor de potencia.
Una vez finalizada la carga guardar los datos en un archivo de organizacion directa llamado "potencia.dat"
imprimiendo en pantalla los datos.

###### ***Ejercicio 40*** 
> Utilizando el archivo potencia.data creado en el Ejercicio 39, realizar una funcion que pase como parametro,entre otros datos, la clave del registro (id).
La funcion ubicara el registro correspondiente al id pasado como parametro, y utilizando punteros imprimira la primera palabra del campo "desc" en forma inversa,
ademas cambiara el estado del bit 3 para luego actualizar el archivo. Ademas, se agregara a una pila la potencia cuando los bits 0 y 2, del campo estado, estÃ©n
encendidos, en caso contrario se agregara el registro al archivo salida.data de organizacion secuencial.


## *ENUNCIADOS*
## *PARTE 2 - Entrega 02/11/2020*


###### ***Ejercicio 41*** 
>El depósito de la empresa __*CosmeFulanito*__ necesita cargar su stock de repuestos en forma ordenada. Para dicha tarea se solicitó categorizar a los respuestos 
bajo la siguiente estructura de datos:

    typedef struct{
        long partNumber;
        long serialNumber;
        char descripcion[40];       
        chat ubicacion[100];        
    }repuestos_t;
>Los repuestos no están ordenados, se solicita cargarlos en una lista, la cual ordene por descripción a los repuestos para luego guardarlos en un archivo de
*stock* con organización secuencial.
> - Imprimir en pantalla la lista con cada inserción. 
> - El archivo se generará cuando el usuario decide no cargar mas productos.

###### ***Ejercicio 42*** 
> El proveedor de repuestos de __*CosmeFulanito*__ informó que una partida de repuestos salió con falla y debe ser devuelta. Para identificar la partida, 
el proveedor indicó que la falla fue en el partNumber: 1234 que tiene números de serie con el bit 3 y 5 en 1.

    Para estas tareas se solicita:
    - Hacer una cola con todos los registros fallados
    - Realizar la baja física a todos los repuestos fallados 
    - Crear un archivo donde se vuelque el contenido de la cola en orden inverso.

###### ***Ejercicio 43*** 
>El servicio técnico de __*CosmeFulanito*__ recibe órdenes de trabajo diarias. Las mismas son cargadas en un archivo secuencial por el personal de recepción
bajo la siguiente estructura de datos:

    typedef struct{
        long numeroDeOrden;
        char cliente[40];       
        char descripciondeFalla[200];        
        char modelo[65];
        char fecha[10];
        char hora[10];
    }repuestos_t;

    Se pide:
    - Hacer una pila con las órdenes de trabajo de forma tal que la más vieja sea la última en cargarse.

###### ***Ejercicio 44*** 
> El servicio técnico utiliza la pila generada en el ejercicio 43 en su labor diaria. Cada técnico toma una tarea de la pila y genera un orden de extracción 
de repuestos al depósito. Para optimizar los viajes al depósito se arma una lista con los repuestos que cada orden necesita utilizando la siguiente estructura:

    typedef struct{
        repuestos_t repuesto;        
        int cantidad;
    }extraccionRepuestos_t;
    
    Se pide:
    - Cargar la lista de repuestos solicitados por los técnicos. Tener en cuenta que varios técnicos pueden necesitar la misma parte,
    y en esos casos se debe incrementar la cantidad pedida en la lista.

###### ***Ejercicio 45*** 
> La lista creada en el ejercicio 44 es procesada por el depósito. 
    
    Para dicha tarea se pide hacer un programa que:
    - Descuente las cantidades solicitadas del archivo de stock, creado en el __Ejercicio 41__.
    - Hacer una cola con los repuestos en los que no se encontró stock suficiente para poder notificar a los clientes la demora de la reparación.
