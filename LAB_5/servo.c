#include "servo.h"
#include <avr/io.h>
#include <util/delay.h>

void initServo(void) {
	DDRB |= (1<<PB1); // PB1 salida

	TCCR1A |= (1<<COM1A1) | (1<<WGM11); // Fast PWM, non-inverting mode
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // Fast PWM, prescaler = 8
	ICR1=39999;   //20ms PWM period
}

float setServoAngle(uint16_t angle) {
	uint16_t servo_pos = angle * 4.8866;// Mapeo
	servo_pos = (servo_pos >= 999) ? servo_pos : 999;// Evitar que descienda más de 999 ya que es 0 grados
	OCR1A = servo_pos;
	_delay_ms(100); // Delay para mostrar en servo
}
