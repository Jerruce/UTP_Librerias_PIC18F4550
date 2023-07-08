
/**
  * @file MT_serial_buffer.h	
  * @version 1.0
  * @date 13/10/2022
  * @author Miguel Torres
  * @brief  Archivo cabecera con estructuras y funciones para la construcción 
  * y el manejo de buffers circulares, empleados frecuentemente en la 
  * comunicación serial.
  */

#ifndef MT_SERIAL_BUFFER_H_
#define MT_SERIAL_BUFFER_H_


#ifdef	__cplusplus
extern "C" {
#endif
    

/* Inclusión de archivos */
#include <stdint.h>
#include <stdbool.h>

/* Definición de tipos */

/**
  * @brief Estructura para manejar un buffer circular.
  */
typedef struct{
	char *ptr; /**< Arreglo (buffer) donde se almacenan datos. */
	uint8_t size; /**< Tamaño del arreglo (buffer) donde se almacenan los 
	                   datos. */
	volatile int16_t head /**< Cabeza: indica la ubicación del siguiente 
	                           elemento que saldrá del buffer. */;
	volatile int16_t tail; /**< Cola: indica la ubicación donde se almacenará 
	                            el siguiente elemento que ingrese al buffer. */
	volatile int16_t used; /**< Número de ubicaciones ocupadas en el buffer. */
}
ring_buffer_t;


/* Declaración de funciones (prototipos) */

/**
  * @brief Función para construir un buffer circular.
  * @param buff Puntero al buffer circular correspondiente.
  * @param buff_ptr Arreglo (buffer) donde se almacenan datos.
  * @param buff_size Tamaño del arreglo (buffer) donde se almacenan los datos.
  * @details Para utilizar esta función, primero se debe crear una estructura de tipo
  * ring_buffer_t y un arreglo para almacenar los datos.\n
  * Luego, se debe pasar un puntero a dicha estructura y un puntero a dicho 
  * arreglo como argumentos.\n
  * Ejemplo:
  * @code
	ring_buffer_t buffer_prueba;
	char datos[150];
	
	Serial_Buffer_Initialize(&buffer_prueba, datos, 150);
  * @endcode
  */
void Serial_Buffer_Initialize(ring_buffer_t *buff, char *buff_ptr, uint8_t buff_size);

/**
  * @brief Función para limpiar un buffer circular.
  * @param buff Puntero al buffer circular correspondiente.
  * @details Ejemplo:
  * @code
	ring_buffer_t buffer_prueba;
	
    //Limpiar el buffer circular buffer_prueba.
	Serial_Buffer_Reset(&buffer_prueba);
  * @endcode
  */
void Serial_Buffer_Reset(ring_buffer_t *buff);

/**
  * @brief Función para almacenar un byte en un buffer circular.
  * @param Puntero al buffer circular correspondiente.
  * @param Dato que se desea almacenar.
  * @return Si el byte se logró almacenar o no en el buffer circular.
  * @details La función almacena un byte en el buffer circular, siempre
  * y cuando éste cuente con espacio disponible. Si hay espacio en el buffer 
  * y el byte se logra almacenar, la función retorna VERDADERO; de lo
  * contrario, si el buffer se encuentra lleno y el byte no se logra
  *	almacenar, la función retorna FALSO.\n
  * Ejemplo:
  * @code
	ring_buffer_t buffer_prueba;
	char dato;
	char mensaje[100];
	
    //Extraer un byte del buffer circular buffer_prueba.
	if(Serial_Buffer_Extract_Element(&buffer_prueba, &dato))
	{
		sprintf(mensaje, "Byte extraído exitosamente.");
	}
	else
	{
		sprintf(mensaje, "No hay bytes para extraer (buffer vacío).");
	}
	
  * @endcode
  */
bool Serial_Buffer_Put_Element(ring_buffer_t *buff, char byte);

/**
  * @brief Función para extraer un byte de un buffer circular.
  * @param buff Puntero al buffer circular correspondiente.
  * @param byte Puntero a la variable donde se guardará el dato extraído.
  * @return Si el byte se logró extraer o no desde el buffer circular.
  * @details La función extrae un byte desde el buffer circular, siempre
  * y cuando éste no se encuentre vacío. Si hay algún dato para leer en el 
  * buffer, la función retorna VERDADERO; de lo contrario, si el buffer se 
  * encuentra vacío, la función retorna FALSO.\n  
  * Ejemplo:
  * @code
	ring_buffer_t buffer_prueba;
	char dato;
	char mensaje[100];
	
    //Extraer un byte del buffer circular buffer_prueba.
	if(Serial_Buffer_Extract_Element(&buffer_prueba, &dato))
	{
		sprintf(mensaje, "Byte extraído exitosamente.");
	}
	else
	{
		sprintf(mensaje, "No hay bytes para extraer (buffer vacío).");
	}
	
  * @endcode
  */
bool Serial_Buffer_Extract_Element(ring_buffer_t *buff, char *byte);

/**
  * @brief Función para consultar si un buffer circular está vacío.
  * @param buff Puntero al buffer circular correspondiente.
  * @return Si el buffer circular se encuentra vacío o no.
  * @details Si el buffer circular se encuentra vacío, la función 
    retorna el valor VERDADERO; de lo contrario, la función retorna FALSO.\n 
  * Ejemplo:
  * @code
  
  ring_buffer_t buffer_prueba;
  
  if(Serial_Buffer_Full(&buffer_prueba))
  {
	  //Hacer algo si el buffer circular está vacío.
  }
  else
  {
	  //Hacer algo si el buffer circular no está vacío.
  }
  * @endcode
  */
bool Serial_Buffer_Empty(ring_buffer_t *buff);

/**
  * @brief Función para consultar si un buffer circular está lleno.
  * @param buff Puntero al buffer circular correspondiente.
  * @return Si el buffer circular se encuentra lleno o no.
  * @details Si el buffer circular se encuentra lleno, la función 
    retorna el valor VERDADERO; de lo contrario, la función retorna FALSO.\n 
  * Ejemplo:
  * @code
  
  ring_buffer_t buffer_prueba;
  
  if(Serial_Buffer_Full(&buffer_prueba))
  {
	  //Hacer algo si el buffer circular está lleno.
  }
  else
  {
	  //Hacer algo si el buffer circular no está lleno.
  }
  * @endcode
  */
bool Serial_Buffer_Full(ring_buffer_t *buff);

#ifdef	__cplusplus
}
#endif

#endif /* MT_SERIAL_BUFFER_H_ */

