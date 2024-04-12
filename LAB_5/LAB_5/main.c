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

   int main(void)
   {
	   DDRB |= (1<<PB1); // Set PB1 as output

	   TCCR1A |= (1<<COM1A1) | (1<<WGM11); // Fast PWM, non-inverting mode
	   TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Fast PWM, prescaler = 8
	   ICR1=39999;   //20ms PWM period
	   //OCR1A = 1999; // Set initial position to 90 degrees

	   while (1){
		   
		   OCR1A = 999; // Set position to 0 degrees
		   _delay_ms(10000);
		   OCR1A = 1999; // Set position to 45 degrees
		   _delay_ms(10000);
		   OCR1A = 2999; // Set position to 90 degrees
		   _delay_ms(10000);
		   OCR1A = 3999; // Set position to 135 degrees
		   _delay_ms(10000);
		   OCR1A = 4999; // Set position 180to 180 degrees
		   _delay_ms(10000);
		   
	   }
   }
