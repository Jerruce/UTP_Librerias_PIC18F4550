
/**
  * @file MT_serial_buffer.c	
  * @version 1.0
  * @date 13/10/2022
  * @author Miguel Torres
  * @brief  Archivo fuente con la implementación de funciones para la 
  * construcción y el manejo de buffers circulares, empleados frecuentemente
  * en la comunicación serial.
  */

/* Inclusión de archivos */
#include "MT_serial_buffer.h"

/* Definición de funciones */

void Serial_Buffer_Initialize(ring_buffer_t *buff, char *buff_ptr, uint8_t buff_size){
	buff->ptr = buff_ptr;
	buff->size = buff_size;
	buff->used = 0;
	buff->head = 0;
	buff->tail = 0;
}


bool Serial_Buffer_Put_Element(ring_buffer_t *buff, char byte){

	bool op_success = false;

	if(buff->used >= buff->size)
	{
		op_success = false;

	}
	else
	{
		*(buff->ptr + buff->tail) = byte;
		buff->tail++;
		if(buff->tail >= buff->size)
		{
			buff->tail = 0;
		}
		buff->used++;

		op_success = true;
	}

	return  op_success;
}


bool Serial_Buffer_Extract_Element(ring_buffer_t *buff, char *byte){

	bool op_success = false;

	if(buff->used == 0)
	{
		op_success = false;
	}
	else
	{
		*byte = *(buff->ptr + buff->head);
		buff->head++;
		if(buff->head >= buff->size)
		{
			buff->head = 0;
		}
		buff->used--;
		op_success = true;
	}

	return op_success;
}


bool Serial_Buffer_Empty(ring_buffer_t *buff){
	return (buff->used == 0);
}


bool Serial_Buffer_Full(ring_buffer_t *buff){
	return (buff->used == buff->size);
}


void Serial_Buffer_Reset(ring_buffer_t *buff){
	buff->used = 0;
	buff->head = 0;
	buff->tail = 0;
}
