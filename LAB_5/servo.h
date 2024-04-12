#ifndef SERVO_H_
#define SERVO_H_

#include <avr/io.h>

void initServo(void);
void setServoAngle(uint16_t angle);

#endif /* SERVO_H_ */
