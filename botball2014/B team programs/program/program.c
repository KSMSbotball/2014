#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2
#define SPEED_FWD 700
#define SPEED_BWD 500
#define SPEED_LFT 500
void claw_up();
void claw_down ();
void forward (double inches);
void left_turn(double seconds);
void backward (double inches);
int main(){
	//enable_servos();
	//claw_up();
	forward(31);
	left_turn(3);
	forward(11);
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
void left_turn(double inches){
	long clicks = 156.25l * inches;
	mrp(LEFT_MOTOR, SPEED_LFT, clicks);
	bmd(LEFT_MOTOR);
}
void backward (double inches) {
long clicks = 156.25l * inches;
	mrp(RIGHT_MOTOR, SPEED_FWD, clicks);
	mrp(LEFT_MOTOR, SPEED_FWD, clicks);
	bmd(RIGHT_MOTOR);
	bmd(LEFT_MOTOR);
}
