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
  #include "Controller_Servo.h"
//servo_pos valor del potenciometro
  int main(void)
  {		
	  DDRB |= (1<<PB1); // PB1 como salida
	  
	  TCCR1A |= (1<<COM1A1) | (1<<WGM11); // Fast PWM, non-inverting mode
	  TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Fast PWM, prescaler = 8
	  ICR1=39999;   //20ms PWM periodo
	   
	  ADMUX |= (1<<REFS0) | (1<<MUX0); // Set  5V y escoger ADC1 as input
	  ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); //  prescaler a 64

	  while (1){
		  ADCSRA |= (1<<ADSC); // Comenzar ADC 
		  while (ADCSRA & (1<<ADSC)); // Esperar que la lecura termine del ADC
		  float servo_val = ADC * 4.8866;// Mapeo
		 
		  OCR1A = Val_servo_pos(servo_val);
		  _delay_ms(100); // Delay for servo to reach positivo
		  
	  }
  }


