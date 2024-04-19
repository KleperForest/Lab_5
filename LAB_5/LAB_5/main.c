//*********************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Alan Gomez
// Proyecto: LAB_5.c
// Descripción: Quinto Laboratorio de Programación de Microcontroladores con lenguaje C.
// Hardware: ATmega328p
// Created: 4/12/2024 12:27:37 AM
//*********************************************************************
  #define F_CPU 16000000
  #include <avr/io.h>
  #include <util/delay.h>

  int main(void)
  {
	  DDRB |= (1<<PB1); // PB1 salida

	  ADMUX |= (1<<REFS0) | (1<<MUX0); // Referencia 5V y usar ADC1
	  ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); // Enable ADC and set prescaler to 64

	  TCCR1A |= (1<<COM1A1) | (1<<WGM11); // Fast PWM, non-inverting mode
	  TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Fast PWM, prescaler = 8
	  ICR1=39999;   //20ms PWM period

	  while (1){
		  ADCSRA |= (1<<ADSC); //Conversion ADC
		  while (ADCSRA & (1<<ADSC)); // Esperar que la lecura termine
		  uint16_t servo_pos = ADC * 4.8866;// Mapeo
		  servo_pos = (servo_pos>=999)? servo_pos : 999;// Evitar que decienda más de 999 ya que es 0 grados
		  OCR1A = servo_pos;
		  _delay_ms(100); // Delay para mostrar en servo
	  }
  }

///////////////////////////////////////////////////////////////////////////////////////////////
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

void setup(void);
void initADC(void);


uint8_t ADC_TIMER;


int main(void)
{
	setup();
	ADCSRA |= (1<<ADSC);//Comenzar Conversion.
	
	while (1){
		OCR2A = ADC_TIMER;//Cargar ADC a OCR2A, Salida. 
	}
}

void setup(void){
	cli();// Interrupciones
	
	DDRB |= (1<<DDB3);
	
	//TIMERO 2
	TCCR2A = 0;
	TCCR2B = 0;
	TCCR2A |= (1<<COM2A1);	//NO INVERTIDO
	TCCR2A |= (1<<WGM21)|(1<<WGM20);	//Fast mode
	TCCR2B &= ~(1<<WGM22);	//
	TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20);//Prescaler 1024

	initADC();//Llamar ADC
	
	sei();// Inicializar Interrupciones
}

void initADC(void){
	// ADC a utilizar
	ADMUX = 6;
	
	// Utilizando AVCC = 5V internos
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	// Justificacion a la Izquierda
	ADMUX |= (1<<ADLAR);
	
	ADCSRA = 0;// Clear ADCSRA
	
	// Habilitando el ADC
	ADCSRA |= (1<<ADEN);
	
	//Habilitamos las interrupciones
	ADCSRA |= (1<<ADIE);
	
	// Habilitamos el Prescaler de 127
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	DIDR0 |= (1<<ADC0D);
}

ISR(ADC_vect){
	ADC_TIMER = ADCH;// Cargar ADCH 8bits a ADC
	
	
	ADCSRA |= (1<<ADIF);//Interrupcion flag ADC
	ADCSRA |= (1<<ADSC);//Start Conversion-

}