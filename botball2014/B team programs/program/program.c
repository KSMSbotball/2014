void claw_up();
void forward (int seconds);
void claw_down ();
int main(){
	enable_servos();
	claw_up ();
	forward(3.8);
	
	
	
	motor(0,-500);
	motor(2,-420);
	msleep(765);
	
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
motor(0,500);
	motor(2,500);
	msleep(seconds * 1000);
	ao();
}
void left_turn(){
motor(0,500);
msleep(765);
}
