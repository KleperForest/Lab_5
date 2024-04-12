//*********************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Alan Gomez
// Proyecto: LAB_5.c
// Descripción: Quinto Laboratorio de Programación de Microcontroladores con lenguaje C.
// Hardware: ATmega328p
// Created: 4/12/2024 12:27:37 AM
//*********************************************************************

#include <avr/io.h>
#include <util/delay.h>
#include "servo.h"

int main(void) {
	initServo();

	ADMUX |= (1<<REFS0) | (1<<MUX0); // Referencia 5V y usar ADC1
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); // Enable ADC and set prescaler to 64

	while (1) {
		ADCSRA |= (1<<ADSC); //Conversion ADC
		while (ADCSRA & (1<<ADSC)); // Esperar que la lecura termine
		uint16_t servo_angle = ADC; // 
		setServoAngle(servo_angle);// Mapeo y muestra
	}
}
