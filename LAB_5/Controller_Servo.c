//Controller_Servo.c

float Val_servo_pos(float servo_pos){
	servo_pos = (servo_pos>=999)? servo_pos : 999;// Evitar que decienda más de 999 ya que es 0 grados
	return servo_pos;
}