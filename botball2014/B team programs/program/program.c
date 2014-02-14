#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2
#define SPEED_FWD 700
#define SPEED_BWD 500
void claw_up();
void claw_down ();
void forward (double inches);
void left_turn(double seconds);
void backward (double inches);
int main(){
	//enable_servos();
	//claw_up();
	forward(30);
	left_turn(1.3);
	forward(10);
	//backward(1.8);
	disable_servos();
	return 0;
}
void claw_up () {
	set_servo_position(0,1002);
}
void claw_down () {
	set_servo_position(0,315);
}
void forward (double inches){
	long clicks = 156.25l * inches;
	mrp(RIGHT_MOTOR, SPEED_FWD, clicks);
	mrp(LEFT_MOTOR, SPEED_FWD, clicks);
	bmd(RIGHT_MOTOR);
	bmd(LEFT_MOTOR);

}
void left_turn(double seconds){
motor(LEFT_MOTOR,500);
msleep(seconds * 1000);
	ao();
}
void backward (double inches) {
long clicks = 156.25l * inches;
	mrp(RIGHT_MOTOR, SPEED_FWD, clicks);
	mrp(LEFT_MOTOR, SPEED_FWD, clicks);
	bmd(RIGHT_MOTOR);
	bmd(LEFT_MOTOR);
}
