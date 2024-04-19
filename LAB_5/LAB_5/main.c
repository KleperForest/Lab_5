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
		// Timer 1
		DDRB |= (1<<PB1); // PB1 salida

		ADMUX |= (1<<REFS0) | (1<<MUX0); // Referencia 5V y usar ADC1
		ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); // Enable ADC and set prescaler to 64

		TCCR1A |= (1<<COM1A1) | (1<<WGM11); // Fast PWM, non-inverting mode
		TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Fast PWM, prescaler = 8
		ICR1=29999;   //20ms PWM period
	  
		//Timer 2

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
			ADCSRA |= (1<<ADSC); //Conversion ADC
			while (ADCSRA & (1<<ADSC)); // Esperar que la lecura termine
			uint16_t servo_pos = ADC * 4.8866;// Mapeo
			servo_pos = (servo_pos>=999)? servo_pos : 999;// Evitar que decienda más de 999 ya que es 0 grados
			OCR1A = servo_pos;
			OCR2B = 10;//Ciclos de trabajo.
			_delay_ms(100); // Delay para mostrar en servo
	  }
  }
