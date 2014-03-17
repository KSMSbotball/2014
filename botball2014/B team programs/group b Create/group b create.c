// Created on Thu March 13 2014
#define CLAW_CLOSE 550
#define CLAW_OPEN 1100



#define CLAW_SERVO 1
#define CLAW_OPENING_INCREMENT 5
#define CLAW_CLOSING_INCREMENT -5
#define FORWARD_CONSTANT 275
#define A 0


//function stubs
void clawOpen();
void clawClose();
void forward(int inches);
void backward(int inches);



int main()
{
create_connect();
	enable_servos();
	msleep(5000);
	printf("opening claw...\n");
	clawOpen();
	printf("opening claw...done \n");
	msleep(2000);
	printf("opening claw...\n");
	clawClose();
	printf("opening claw...done\n");
	msleep(2000);
	clawOpen();
	msleep(2000);
	clawClose();
	msleep(2000);
/*	printf("prgm starts 2..\n");
	forward(10);
	printf("i have moved 10 inc andd I am resting 3 s\n");
	msleep(3000);
	forward (15);
	printf("i have moved 15 inc andd I am resting 3 s\n");
*/	msleep(3000);
	backward (1000);
	printf("the end...\n");
	create_disconnect();
	return 0;
	//hey guys here is a "nicer way" more programer like to write teh same thing below
	//while(!get_create_lbump() && !get_create_rbump());
	//we could also create a function that does go forward until bumping against something
	//KIPR program has a similar function forwardUntilBlackLine(int inches) which goes forward
	//for either the number of inches or when it encounter the black or goes over 
	//void 	(no infrared reflection)
	//while (get_create_lbump() == 0 && get_create_rbump() == 0) {
		//sleep i.e do nothing
		//msleep(50);
		//printf("in the while loop\n");
	//}
	// I now stop since I have bumped against something. 
	create_stop();
	
	create_disconnect();
	
	return 0;
	
}


//opening the claw gently from current position
void clawOpen() {
	int currentPosition = get_servo_position(CLAW_SERVO);
	if (currentPosition > CLAW_OPEN) {
		set_servo_position(CLAW_SERVO,CLAW_OPEN);
	}
	while  (currentPosition < CLAW_OPEN) {
		set_servo_position(CLAW_SERVO, (currentPosition + CLAW_OPENING_INCREMENT));
		msleep(10);
		currentPosition = get_servo_position(CLAW_SERVO);
	}
}

//closing the claw gently from current position
void clawClose() {
	int currentPosition = get_servo_position(CLAW_SERVO);
	if (currentPosition < CLAW_CLOSE) {
		set_servo_position(CLAW_SERVO,CLAW_CLOSE);
	}
	while  (currentPosition > CLAW_CLOSE) {
		set_servo_position(CLAW_SERVO, (currentPosition + CLAW_CLOSING_INCREMENT));
		msleep(10);
		currentPosition = get_servo_position(CLAW_SERVO);
	}
}

void forward (int inches){
	create_drive_straight(100);
	
	int time_conversion = inches * FORWARD_CONSTANT;
	msleep(time_conversion);
	create_stop();
}
	
void backward (int inches){
	create_drive_straight(-100);
	
	int time_conversion = inches * 1;
	msleep(time_conversion);
	create_stop();
}
	
