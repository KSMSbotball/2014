void claw_up();
void forward (int seconds);
void claw_down ();
void left_turn();
#define LEFT_MOTOR 0
int main(){
	enable_servos();
	claw_up();
	forward(3.8);
	left_turn();
	disable_servos();
	return 0;
}
void claw_up () {
	set_servo_position(0,1002);
}
void claw_down () {
	set_servo_position(0,315);
}
void forward (int seconds){
motor(LEFT_MOTOR,500);
	motor(2,500);
	msleep(seconds * 1000);
	ao();
}
void left_turn(){
motor(LEFT_MOTOR,500);
msleep(765);
}
