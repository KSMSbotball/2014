// Created on Thu March 13 2014
//CGroup b Create program:  this program is what should be run at the competition
//
//Cube position (x coordinate), change when calibrating channel if needed
//see program camera calibration routine
#define RIGHT_ANG_LEFT 2000
#define RIGHT_ANG_RIGHT 2000

//from right PVC by Upper storage area to before right angle right
#define FORWARD_FROM_BASE 4.6
// distance after the right angle right to picking up the cube
#define UP_TO_CUBE 10.5

#define POS_7 6
#define POS_6 20
#define POS_5 55
#define POS_4 90
#define POS_3 122
#define POS_2 147
#define POS_1 170


#define CUBE_WIDTH 2

#define CLAW_CLOSE 500
#define CLAW_OPEN 950



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

void dropCubes(int cube1, int cube2);

void pushSideToSide();
void determineCubePositions(int* positions, int debug);

int getShelfPlacement(int xLocation);



int main()
{
	
	create_connect();
	enable_servos();
	camera_open(LOW_RES);
//	wait_for_light(1);
	shut_down_in(115);
	printf("3.0 HD version 03/21/14 after initialization\n");
	int startTime = seconds();
	msleep(1500);	
	//msleep(27000);
	
	clawOpen();
	//place create for camera recognition of cube positions
	forward(9);
	rightAngle(LEFT);
	forward(15);
	rightAngle(RIGHT);
	printf("Camera work\n");
	int positions[2] = {-1, -1};
	determineCubePositions(positions, DEBUG);
	printf("back from looking camera usage. positions: %d, %d, elapsed time: %f s\n", positions[0], positions[1], (seconds() - startTime));
	//start routine to go grab the cubes
	if (positions[0] == -1) {
		//the program did not find any objects based on the channel
		// so time for random guesses rather than doing nothing
		positions[0] = 2;
		positions[1] = 5;
	} else if (positions [1] == -1) {
		positions[1] = 5;
	}
	rightAngle(LEFT);
	
	rightAngle(LEFT);
	backward(16.5);
	pushSideToSide();
	//forward(5);
	
	
	
	//position create at the standard starting position
	
	dropCubes(positions[0], positions[1]);
		

	printf("All done. elapsed time: %f s\n", (seconds() - startTime));
	//moving out of the way now
	forward(10); 
	rightAngle(RIGHT);
	backward(17);
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
	msleep(1000); 
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
	//we want the lowest number to be first, so switch values if they are in reverse order
	if (positions[0] > positions[1]) {
		int interim = positions[0];
		positions[0] = positions[1];
		positions[1] = interim;
	}

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


//pcik up and drop cubes

void dropCubes(int cube1, int cube2) {
	
	clawOpen();

	backward(1);
	msleep(300);
	//place create for camera recognition of cube positions
	forward(FORWARD_FROM_BASE + 2*cube1 );
	rightAngle(RIGHT);
	msleep(300);
	forward(UP_TO_CUBE);
	msleep(300);
	clawClose(NO_DEBUG);
	backward(UP_TO_CUBE + 0.5);
	msleep(300);
	rightAngle(RIGHT);
	msleep(300);
	forward(FORWARD_FROM_BASE + 2* cube1);
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
	forward(FORWARD_FROM_BASE + 2*cube2);
	msleep(300);
	rightAngle(RIGHT);
	msleep(300);
	forward(UP_TO_CUBE - 1);
	msleep(300);
	clawClose(NO_DEBUG);
	msleep(300);
	backward(UP_TO_CUBE - 0.5);
	msleep(300);
	rightAngle(RIGHT);
	msleep(300);
	forward(FORWARD_FROM_BASE + 2 * cube2);
	msleep(300);
	clawOpen();
	backward(2);
	msleep(300);
	rightAngle(RIGHT);
	rightAngle(RIGHT);
	backward(3);
	pushSideToSide();
}


//wiggle from side to side to get recalibrated againt PVC
void pushSideToSide (){
	create_drive_direct(SPEED_BWD,0);
	msleep(500);
	create_stop();
	create_drive_direct(0, SPEED_BWD);
	msleep(500);
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

