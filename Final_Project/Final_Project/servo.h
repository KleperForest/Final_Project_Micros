#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h>

// Definir constantes para los canales de los ADC y los pines de los servos
#define SERVO1_PIN PB1
#define SERVO2_PIN PB2
#define SERVO3_PIN PD3
#define SERVO4_PIN PD6

// Inicializar servos y ADC
void servo_init(void);

// Establecer posición del servo
void servo_set_position(uint8_t servo, uint16_t position);

// Leer valor del ADC
uint16_t adc_read(uint8_t channel);

#endif // SERVO_H
