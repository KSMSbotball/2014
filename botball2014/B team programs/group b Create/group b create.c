// Created on Thu March 13 2014
//CGroup b Create program:  this program is what should be run at the competition
//
//Cube position (x coordinate), change when calibrating channel if needed
//see program camera calibration routine
#define POS_7 6
#define POS_6 20
#define POS_5 55
#define POS_4 90
#define POS_3 122
#define POS_2 147
#define POS_1 170

#define STANDRD_LENGTH 20
#define CUBE_WIDTH 3.5

#define CLAW_CLOSE 500
#define CLAW_OPEN 920



#define CLAW_SERVO 1
#define CLAW_OPENING_INCREMENT 5
#define CLAW_CLOSING_INCREMENT -5
#define FORWARD_CONSTANT 275
#define BACKWARD_CONSTANT 250
#define RIGHT_ANG_LEFT 1960
#define RIGHT_ANG_RIGHT 1840
#define HALF_CIRCLE 3800
#define SPEED_FWD 100
#define SPEED_BWD -100
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
void turnCreate(int time);
void approachYellowCube(int debug);
void dropCube(int fromLocation);
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
	printf("2.1 after initialization\n");
	int startTime = seconds();
	msleep(1500);	
	msleep(5000);
	printf("opening claw...\n");
	clawOpen();
	//place create for camera recognition of cube positions
	forward(9);
	rightAngle(LEFT);
	forward(20);
	int positions[2] = {-1, -1};
	determineCubePositions(positions, DEBUG);
	printf("back from looking camera usage. elapsed time: %f s\n", (seconds() - startTime));
	//start routine to go grab the cubes
	if (positions[0] != -1) {
		//position create at the standard starting position
		goToBase();
		goGrabCubeAtPosition(positions[0]);
		dropCube(positions[0]);
		printf("should have dropped cube 1, elapsed time: %f s.\n", (seconds() - startTime));
		//create just dropped a cube and is back at the starting location ready for number 2
		goGrabCubeAtPosition(positions[1]);
		dropCube(positions[1]);
		printf("should have dropped cube 2, the end. elapsed time: %f s\n", (seconds() - startTime));
	} else { 
		printf("the camera did not get any hits... sorry bad run.\n");
		goToBase();
	}
	
	camera_close();
	create_disconnect();
	return 0;
	
	
}

//routine to move create towards yellow cube
void determineCubePositions(int* positions,  int debug) {
	msleep(2000);
	int retries = 0;
	int channel = 0;
	int result = camera_update();
	while (retries < 10 && get_object_count(channel) == 0) {
		msleep(1000);
		retries = retries + 1;
		if (debug == DEBUG) {
			printf ("camera not seeing cubes retry %d \n",retries);
		}
		result = camera_update();
	}
	if (retries >= 10) {
		printf ("the camera couldn't see anything, bad run.\n");
		return;
	}
	//one more update
	msleep(2000); 
	camera_update();
	if (debug == DEBUG) {		
		printf ("====> for channel %d, object count %d \n", channel, get_object_count(channel));
	}
	//now let's compute the results of the camera 			
	int i = 0; 
	int shelfPlacesTtlArea[8] = {0,0,0,0,0,0,0,0};
	while (i < get_object_count(channel)) {
		int position = getShelfPlacement(get_object_center(channel, i).x);
		if (debug == DEBUG) {
			printf("obj %d, ctr loc, area, shelf plcmt: %d, %d, %d\n", i, get_object_center(channel, i).x, get_object_area(channel, i), position);
		}
		
		shelfPlacesTtlArea[position] += get_object_area(channel, i);
		i++;
	}
	i = 1;
	int areas[2] = {0,0};
	//let's select the 2 with the most areas
	//look at all 7 shelfPlacement and the total area accumulated by each based on the routine above
	//areas array of 2 will contain the top 2 and we start the area at 0 of course we also need to remember what
	//shelf placement that was and this is kept in positions.
	while (i < 8) {
		if (shelfPlacesTtlArea[i] > areas[0]) {
			//the current shelf placement examined has more surface than the greatest we have seen so we will
			// slide the previous largest to the 2nd largest and store this one as the new largest area
			areas[1] = areas[0];
			positions[1] = positions[0];
			areas[0] = shelfPlacesTtlArea[i];
			positions[0] = i;
			if (debug == DEBUG) {
				printf ("shelfPlace : %d, total cube area : %d is the largest on record.\n", i, shelfPlacesTtlArea[i]);
			}

		} else if (shelfPlacesTtlArea[i] > areas[1]) {
			//the current shelf placement examined has more surface than the 2nd largest greatest we have seen so far, so we will
			//store it at the 2nd largest and drop the other one since there are only 2 cubes		
			areas[1] = shelfPlacesTtlArea[i];
			positions[1] = i;
			if (debug == DEBUG) {
				printf ("shelfPlace : %d, total cube area : %d is the 2nd largest on record.\n", i, shelfPlacesTtlArea[i]);
			}
		}
		i++;
	}
	//since the camera can't see position 7 we will have to assume that if the camera only saw 1 cube the other one is at palcement 7
	if (areas[1] < 100) {
		positions[1] = 7;
	}

}

//goes and picks up the cube based on the shelf location this is dead reckoning but create is very accurate
void goGrabCubeAtPosition(int location) { 
	//the claw should be opened but just in case
	clawOpen();
	forward(STANDRD_LENGTH + location * CUBE_WIDTH);
	rightAngle(RIGHT);
	//go up to pick it up
	forward(12);
	//we should now secure teh cube
	clawClose(NO_DEBUG);
		
}

//goes from picking up the cube to dropping it off in the upper storage area
void dropCube(int fromLocation) { 
	backward(8);
	rightAngle(LEFT);
	backward((STANDRD_LENGTH +  fromLocation * CUBE_WIDTH + 1) );
	pushSideToSide();
	forward(3);
	
	turnCreate(HALF_CIRCLE);
	clawOpen();
	turnCreate(HALF_CIRCLE);
	backward(3);
	pushSideToSide();
		
}
//goes to position where bot is ready to go pick up square
void goToBase() { 
	backward(8);
	rightAngle(LEFT);
	backward(23);
	pushSideToSide();
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
	create_drive_straight(SPEED_FWD);
	if (direction == RIGHT) { 
		//then well turn 90 deg to the RIGHT
		create_spin_CW(SPEED_FWD);
		msleep(RIGHT_ANG_RIGHT);
	} else if (direction == LEFT) {
		//then well turn 90 deg to the LEFT
		create_spin_CCW(SPEED_FWD);
		msleep(RIGHT_ANG_LEFT);
	} else {
		printf("sorry I don't understand what you want me to do... ignoring right angle turn command\n");
	}
	create_stop();
}

//generic right angle turn in place
void turnCreate (int time){
	create_spin_CW(SPEED_FWD);
	msleep(time);
	create_stop();
}

//wiggle from side to side to get recalibrated againt PVC
void pushSideToSide (){
	create_drive_direct(SPEED_BWD,0);
	msleep(1000);
	create_stop();
	create_drive_direct(0, SPEED_BWD);
	msleep(1000);
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

