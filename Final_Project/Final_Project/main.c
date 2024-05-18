//*********************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Alan Gomez
// Proyecto: Final_Project.c
// Descripción: Proyecto Final de Programación de Microcontroladores con lenguaje C.
// Hardware: ATmega328p
// Created: 4/29/2024 7:37:15 PM
//*********************************************************************

#include <avr/io.h>
#include <util/delay.h>
#include "servo.h"

int main(void) {
	servo_init();
	
	while (1) {
		uint16_t adc_value1 = adc_read(0);
		uint16_t adc_value2 = adc_read(1);
		uint16_t adc_value3 = adc_read(2);
		uint16_t adc_value4 = adc_read(3);

		servo_set_position(1, adc_value1);
		servo_set_position(2, adc_value2);
		servo_set_position(3, adc_value3);
		servo_set_position(4, adc_value4);
		
		_delay_ms(50);
	}
	
	return 0;
}
