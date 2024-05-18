#include "servo.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void servo_init(void) {
	// Configurar pines como salida
	DDRB |= (1 << SERVO1_PIN) | (1 << SERVO2_PIN);
	DDRD |= (1 << SERVO3_PIN) | (1 << SERVO4_PIN);
	
	// Configurar Timer 1 para Fast PWM, modo 14
	TCCR1A |= (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8
	ICR1 = 39999; // Periodo de 20 ms (50 Hz)
	
	// Configurar Timer 2 para Fast PWM
	TCCR2A |= (1 << WGM20) | (1 << WGM21) | (1 << COM2A1) | (1 << COM2B1);
	TCCR2B |= (1 << WGM22) | (1 << CS21); // Prescaler 8
	OCR2A = 0;
	OCR2B = 0;

	// Configurar ADC
	ADMUX |= (1 << REFS0); // Referencia AVcc
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Habilitar ADC y prescaler de 128
}

void servo_set_position(uint8_t servo, uint16_t position) {
	uint16_t pulse_width = (position * 2) + 1000; // Convertir a microsegundos (aprox. entre 1000 y 2000 us)
	switch (servo) {
		case 1:
		OCR1A = pulse_width;
		break;
		case 2:
		OCR1B = pulse_width;
		break;
		case 3:
		OCR2A = pulse_width / 16; // Ajustar para el Timer 2
		break;
		case 4:
		OCR2B = pulse_width / 16; // Ajustar para el Timer 2
		break;
		default:
		break;
	}
}

uint16_t adc_read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Seleccionar canal
	ADCSRA |= (1 << ADSC); // Iniciar conversión
	while (ADCSRA & (1 << ADSC)); // Esperar a que la conversión termine
	return ADC;
}
