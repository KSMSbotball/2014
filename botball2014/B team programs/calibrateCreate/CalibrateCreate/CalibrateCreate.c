// Created on Thu March 13 2014
//CGroup b Create program:  this program is what should be run at the competition
//
//Cube position (x coordinate), change when calibrating channel if needed
//see program camera calibration routine
#define RIGHT_ANG_LEFT 2000
#define RIGHT_ANG_RIGHT 2000

#define FORWARD_FROM_BASE 4.6
#define UP_TO_CUBE 9.5

#define CUBE_1 2
#define CUBE_2 6

#define POS_7 6
#define POS_6 20
#define POS_5 55
#define POS_4 90
#define POS_3 122
#define POS_2 147
#define POS_1 170

#define STANDRD_LENGTH 6.5
#define FORWARD_TO_CUBE 7.5
#define CUBE_WIDTH 2

#define CLAW_CLOSE 500
#define CLAW_OPEN 980



#define CLAW_SERVO 1
#define CLAW_OPENING_INCREMENT 5
#define CLAW_CLOSING_INCREMENT -5
#define FORWARD_CONSTANT 100
#define BACKWARD_CONSTANT 95

#define HALF_CIRCLE 3800
#define SPEED_FWD 250
#define SPEED_BWD -250
#define CHANNELS 1
#define DEBUG 100
#define NO_DEBUG 51

#define RIGHT 2
#define LEFT 3
//function stubs
void clawOpen();
void clawClose(int debug);
void clawCloseA(int debug);
void forward(int inches);
void backward(int inches);
void rightAngle(int direction);

void goToBase();
void pushSideToSide();
void determineCubePositions(int* positions, int debug);
void goGrabCubeAtPosition(int position);
int getShelfPlacement(int xLocation);



int main()
{
	printf("beginning pgm\n");	
	create_connect();
	enable_servos();
	camera_open(LOW_RES);
//	wait_for_light(1);
	shut_down_in(115);
	printf("2.3 after initialization\n");
	int startTime = seconds();
	
	printf("opening claw...\n");
	clawOpen();
	
	forward(10); 
	//backward(9);
	backward(1);
	msleep(300);
	//place create for camera recognition of cube positions
	forward(FORWARD_FROM_BASE + 2*CUBE_1);
	rightAngle(RIGHT);
	msleep(300);
	forward(UP_TO_CUBE);
	msleep(300);
	clawClose(NO_DEBUG);
	backward(UP_TO_CUBE + 0.5);
	msleep(300);
	rightAngle(RIGHT);
	msleep(300);
	forward(FORWARD_FROM_BASE + 2* CUBE_1);
	msleep(300);
	clawOpen();
	backward(2);
	rightAngle(RIGHT);
	msleep(300);
	rightAngle(RIGHT);
	msleep(300);
	backward(3);
	pushSideToSide();
	
	//cube 2
	forward(FORWARD_FROM_BASE + 2*CUBE_2);
	msleep(300);
	rightAngle(RIGHT);
	msleep(300);
	forward(UP_TO_CUBE);
	msleep(300);
	clawClose(NO_DEBUG);
	msleep(300);
	backward(UP_TO_CUBE + 0.5);
	msleep(300);
	rightAngle(RIGHT);
	msleep(300);
	forward(FORWARD_FROM_BASE + 2 * CUBE_2);
	msleep(300);
	clawOpen();
	backward(2);
	msleep(300);
	rightAngle(RIGHT);
	rightAngle(RIGHT);
	backward(3);
	pushSideToSide();
	
	camera_close();
	create_disconnect();
	return 0;
	
	
}






//return the shelf placement based on predefined values
int getShelfPlacement(int xLocation) {
	if (xLocation > (int) ((POS_1 + POS_2) /2) ) {
		return 1; 
	} 
	if (xLocation > (int) ((POS_2 + POS_3) /2) ) {
		return 2; 
	} 
	if (xLocation > (int) ((POS_3 + POS_4) /2) ) {
		return 3; 
	} 
	if (xLocation > (int) ((POS_4 + POS_5) /2) ) {
		return 4; 
	} 
	if (xLocation > (int) ((POS_5 + POS_6) /2) ) {
		return 5; 
	} 
	if (xLocation > (int) ((POS_6 + POS_7) /2) ) {
		return 6; 
	} 
	return 7;
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
	
	if (direction == RIGHT) { 
		//then well turn 90 deg to the RIGHT
		create_spin_CW(100);
		msleep(RIGHT_ANG_RIGHT);
	} else if (direction == LEFT) {
		//then well turn 90 deg to the LEFT
		create_spin_CCW(100);
		msleep(RIGHT_ANG_LEFT);
	} else {
		printf("sorry I don't understand what you want me to do... ignoring right angle turn command\n");
	}
	create_stop();
}



//wiggle from side to side to get recalibrated againt PVC
void pushSideToSide (){
	create_drive_direct(SPEED_BWD,0);
	msleep(300);
	create_stop();
	create_drive_direct(0, SPEED_BWD);
	msleep(300);
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
	

