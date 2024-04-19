#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

void setup(void);
void initADC(void);


uint8_t valorADC2;


int main(void)
{
    setup();
	ADCSRA |= (1<<ADSC);
	
    while (1){
		OCR2A = valorADC2;
    }
}

void setup(void){
	cli();
	
	DDRB |= (1<<DDB3);
	
	//TIMER 2
	TCCR2A = 0;
	TCCR2B = 0;
	
	TCCR2A |= (1<<COM2A1);	//NO INVERTIDO
	TCCR2A |= (1<<WGM21)|(1<<WGM20);	//MODO FAST
	
	TCCR2B &= ~(1<<WGM22);	//
	TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20);	//PRESCALER DE 1024

	initADC();
	
	sei();
}

void initADC(void){
	// Seleccion de Canal ADC (A)
	ADMUX = 6;
	
	// Utilizando AVCC = 5V internos
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	// Justificacion a la Izquierda
	ADMUX |= (1<<ADLAR);
	
	ADCSRA = 0;
	
	// Habilitando el ADC
	ADCSRA |= (1<<ADEN);
	
	//Habilitamos las interrupciones
	ADCSRA |= (1<<ADIE);
	
	// Habilitamos el Prescaler de 128
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	DIDR0 |= (1<<ADC0D);
}

ISR(ADC_vect){
	valorADC2 = ADCH;
	
	
	ADCSRA |= (1<<ADIF);
	ADCSRA |= (1<<ADSC);

}