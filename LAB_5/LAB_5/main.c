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
	TCCR2B &= ~(1<<WGM22);
	TCCR2A |= (1<<WGM20);
	TCCR2A |= (1<<WGM21);

	// Prescaler 1024
	TCCR2B |= (1<<CS22);
	TCCR2B &= ~(1<<CS21);
	TCCR2B |= (1<<CS20);
	
	// Pin oc0b
	TCCR2A |=(1<<COM2B1);
	TCCR2A &= ~(1<<COM2B0);


	while (1){
		OCR2B = 10;//Ciclos de trabajo.
	}
}


