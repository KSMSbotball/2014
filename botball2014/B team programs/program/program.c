void claw_up();
void forward (double seconds);
void claw_down ();
void left_turn(double seconds);
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2
int main(){
	enable_servos();
	claw_up();
	forward(4);
	left_turn(1.3);
	forward(1.1);
	disable_servos();
	return 0;
}
void claw_up () {
	set_servo_position(0,1002);
}
void claw_down () {
	set_servo_position(0,315);
}
void forward (double seconds){
motor(LEFT_MOTOR,500);
	motor(RIGHT_MOTOR,500);
	msleep(seconds * 1000);
	ao();
}
void left_turn(double seconds){
motor(LEFT_MOTOR,500);
msleep(seconds * 1000);
	ao();
}
