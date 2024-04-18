//*********************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Alan Gomez
// Proyecto: LAB_5.c
// Descripción: Quinto Laboratorio de Programación de Microcontroladores con lenguaje C.
// Hardware: ATmega328p
// Created: 4/12/2024 12:27:37 AM
//*********************************************************************
#define F_CPU 12000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	//Configuracion el pin 
	DDRD |=(1<<PD5);
	
	//Modo Fast PWM
	TCCR0B &= ~(1<<WGM02);
	TCCR0A |= (1<<WGM01);
	TCCR0A |= (1<<WGM00);
	
	// Prescaler 1024
	TCCR0B |= (1<<CS02);
	TCCR0B &= ~(1<<CS01);
	TCCR0B |= (1<<CS00);
	
	// Pin oc0b
	TCCR0A |=(1<<COM0B1);
	TCCR0A &= ~(1<<COM0B0);
	
	OCR0B = 10;//Ciclos de trabajo.

	while (1){

	}
}


