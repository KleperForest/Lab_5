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

  #define SERVO_MIN_POS 999 // 0 degrees
  #define SERVO_MAX_POS 4999 // 180 degrees

  int main(void)
  {
	  DDRB |= (1<<PB1); // Set PB1 as output

	  ADMUX |= (1<<REFS0) | (1<<MUX0); // Set reference voltage to AVCC and select ADC1 as input
	  ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); // Enable ADC and set prescaler to 64

	  TCCR1A |= (1<<COM1A1) | (1<<WGM11); // Fast PWM, non-inverting mode
	  TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Fast PWM, prescaler = 8
	  ICR1=39999;   //20ms PWM period

	  while (1){
		  ADCSRA |= (1<<ADSC); // Start ADC conversion
		  while (ADCSRA & (1<<ADSC)); // Wait for conversion to complete
		  uint16_t servo_pos = ADC * 4.8866;// Mapeo
		  servo_pos = (servo_pos>=999)? servo_pos : 999;// Evitar que decienda más de 999 ya que es 0 grados
		  OCR1A = servo_pos;
		  _delay_ms(100); // Delay for servo to reach position
	  }
  }


