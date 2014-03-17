// Created on Thu March 13 2014
#define CLAW_CLOSE 550
#define CLAW_OPEN 1100



#define CLAW_SERVO 1
#define CLAW_OPENING_INCREMENT 5
#define CLAW_CLOSING_INCREMENT -5
#define FORWARD_CONSTANT 275
#define BACKWARD_CONSTANT 250
#define SPEED_FWD 100
#define SPEED_BWD -100
#define CHANNELS 1
#define DEBUG 100
#define NO_DEBUG 51
#define A 0

#define RIGHT 2
#define LEFT 3
//function stubs
void clawOpen();
void clawClose(int debug);
void clawCloseA(int debug);
void forward(int inches);
void backward(int inches);
void rightAngle(int direction);
void approachYellowCube(int debug);



int main()
{
	printf("beginning pgm\n");
	create_connect();
	enable_servos();
	camera_open(LOW_RES);
	printf("2.1 after initialization\n");

	msleep(1500);	
/*	msleep(5000);
	printf("opening claw...\n");
	clawOpen();
	printf("opening claw...done \n");
	msleep(2000);
	printf("closing claw...\n");
	clawClose(DEBUG);
	printf("closing claw...done\n");
	msleep(2000);
	clawOpen();
	msleep(2000);
	clawClose(NO_DEBUG);
*/	
	printf("prgm starts 2..\n");
	clawOpen(NO_DEBUG);
	approachYellowCube(DEBUG);
	clawClose(NO_DEBUG);
/*	forward(10);
	printf("i have moved 10 inc andd I am resting 3 s\n");
	rightAngle(LEFT);
	forward (10);
	rightAngle(RIGHT);
	forward (10);
	
	rightAngle(LEFT);
	backward (10);
	rightAngle(RIGHT);
	backward (19);
	
	printf("i have moved 15 inc andd I am resting 3 s\n");
	msleep(3000);
//	backward (24);
	printf("the end...\n");
*/	create_disconnect();
	return 0;
	
	
}

//routine to move create towards yellow cube
void approachYellowCube(int debug) {
	camera_update();
	while (a_button_clicked() == 0 ) {
		int i = 0 ; 
		while (i < CHANNELS) {
			if (debug == DEBUG) {
				printf("printing for %d\n", i);
				printf("test %d\n", get_object_count(1));
				
				printf ("====> for channel %d, object count %d \n", i, get_object_count(i));
				
			}
			int j = 0; 
			int significantObject = -1;
			int area = -1;
			//get largest object
			while ( j <= get_object_count(i) ) {
				if (get_object_area(i,j) > area && get_object_area(i,j) > 130) {
					area = get_object_area(i,j);
					significantObject = j;
				}
				
				j = j + 1;
			}
			if (significantObject != -1)  {
				//we found something
				printf("the object center is at x %d, y %d \n", get_object_center(i, significantObject).x, get_object_center(i, significantObject).y);
			}

			i = i+ 1; 
		}
		if (debug == DEBUG) {
			printf("push b button to update, a to exit"); 
		}
		while (b_button_clicked() == 0 && a_button_clicked() == 0) {
			msleep(100);
		}
		camera_update();
		
	}
	if (debug == DEBUG) {
		printf ("all done camera routine...\n");
	}
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
void clawClose(int debug) {
	int currentPosition = get_servo_position(CLAW_SERVO);
	if (currentPosition < CLAW_CLOSE) {
		set_servo_position(CLAW_SERVO,CLAW_CLOSE);
	}
	while  (currentPosition > CLAW_CLOSE  ) {
		set_servo_position(CLAW_SERVO, (currentPosition + CLAW_CLOSING_INCREMENT));
		msleep(10);
		currentPosition = get_servo_position(CLAW_SERVO);
		if (debug == DEBUG) {
			printf("claw values,  curr : %d, tgt : %d.\n", currentPosition, CLAW_CLOSE);
		}
	}
}

//generic right angle turn in place
void rightAngle (int direction){
	create_drive_straight(SPEED_FWD);
	if (direction == RIGHT) { 
		//then well turn 90 deg to the RIGHT
		create_spin_CW(SPEED_FWD);
		msleep(1900);
	} else if (direction == LEFT) {
		//then well turn 90 deg to the LEFT
		create_spin_CCW(SPEED_FWD);
		msleep(1900);
	} else {
		printf("sorry I don't understand what you want me to do... ignoring right angle turn command\n");
	}
	create_stop();
}



//generic move forward function calibrated in inches
void forward (int inches){
	create_drive_straight(SPEED_FWD);
	
	int time_conversion = inches * FORWARD_CONSTANT;
	msleep(time_conversion);
	create_stop();
}
	
//generic move backward function calibrated in inches
void backward (int inches){
	create_drive_straight(SPEED_BWD);
	
	int time_conversion = inches * BACKWARD_CONSTANT;
	msleep(time_conversion);
	create_stop();
}
	
//closing the claw gently from current position
void clawCloseA(int debug) {
	int currentPosition = get_servo_position(CLAW_SERVO);
	if (currentPosition < CLAW_CLOSE) {
		set_servo_position(CLAW_SERVO,CLAW_CLOSE);
	}
	int stuckInSamePosition = 0;
	int previousPosition = 0;
	while  (currentPosition > CLAW_CLOSE && stuckInSamePosition < 10 ) {
		set_servo_position(CLAW_SERVO, (currentPosition + CLAW_CLOSING_INCREMENT));
		msleep(10);
		currentPosition = get_servo_position(CLAW_SERVO);
		int movement = currentPosition - previousPosition;
		//we need to allow for a tiny bit of movement a tick or 2 
		//so there is a tolerance of 5 to -5
		if (movement < 5 && movement > -5)  {
			stuckInSamePosition++;
		} else {
			previousPosition = currentPosition;
		}
		if (debug == DEBUG) {
			printf("claw values,  curr : %d, tgt : %d.\n", currentPosition, CLAW_CLOSE);
		}

	}
}
