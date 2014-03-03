// Created on Thu February 6 2014
//quick and dirty program to see if mav API is more reliable than motor
//to improve dead recknoning outcome.
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 0
#define SPEED_FWD 700
#define SPEED_BWD -700
#define ADJUST_SPEED 0.75
#define RIGHT 76
#define LEFT 57
#define RIGHT_ANGLE_CLICKS 1420
#define RIGHT_ANGLE_CLICKS_BACK -1410
#define FV_ANGLE_CLICKS 744
#define FV_ANGLE_CLICKS_BACK -744
#define UP_SERVO 1900
#define DOWN_SERVO 1015
#define UP_SERVO_CUBE 1900
#define DOWN_SERVO_CUBE 1398
#define LIGHT_SENSOR 1
#define CHECK_LIGHT_SENSOR 101
#define DONOT_CHECK_LIGHT_SENSOR 197

//declaration
void moveForward(double distanceInInches); 
void moveForwardTilBlackLine(double distanceInInches); 	
void moveBackward(double distanceInInces);
void moveForwardRoutine(double distanceInInches, int checkLightSensor); 

void rightAngleFwd(int direction);
void rightAngleBwd(int direction);
void fortyFiveAngleFwd(int direction);
void fortyFiveAngleBwd(int direction);
void clawUp();
void clawDown();
void clawDownCube();
void clawUpCube();
void reset_counters();
int main()
{
	printf("test 2.02, fixed fowd and bwd function bugs.\n");
	
	
	enable_servos();
	clawUp();
	moveBackward(1);
	moveForward(22);
	clawDown();
	
	//we have the Poms
	rightAngleBwd(RIGHT);
	//bump against the upper storage area
	moveBackward(15);
	msleep(100);
	moveForward(20);
	rightAngleBwd(RIGHT);
	//bump against upper PVC side
	moveBackward(15);
	//move towards dropping poms
	
	

	moveForward(3);
	clawUp();
	rightAngleFwd(LEFT);
	moveForwardTilBlackLine(9);
	/*fortyFiveAngleFwd(RIGHT);
	moveForward(13.5);
	fortyFiveAngleFwd(RIGHT);
	moveForward(1.5);
	clawUp();*/
	
	/*Milestone 2
	moveForward(6);
	//Milestone 2
	moveBackward(11);
	reset_counters();
	rightAngleBwd(RIGHT);
	moveBackward(10);
	moveForward(9);
	reset_counters();
	rightAngleFwd(RIGHT);
	moveForward(22);
	clawDownCube();
	reset_counters();
	fortyFiveAngleFwd(LEFT);
	moveForward(20);
	//printf("program finished, POMS should be in...\n");
	*/
	ao();
	disable_servos();
	
	return 0;
}

//uses a home made mrp (move to relative position) and convert from inches
//to motor units.
void moveForward(double distanceInInches) {	
	moveForwardRoutine(distanceInInches, DONOT_CHECK_LIGHT_SENSOR);
}

//uses a home made mrp (move to relative position) and convert from inches
//to motor units. KIPR stops when it no longer is on the white surface (either black tape
// or void)
//
void moveForwardTilBlackLine(double distanceInInches) {
	moveForwardRoutine(distanceInInches, CHECK_LIGHT_SENSOR);
}

//uses a home made mrp (move to relative position) and convert from inches
//to motor units.
//
void moveForwardRoutine(double distanceInInches, int checkLightSensor) {
	//printf("starting to move for %d\n",distanceInInches);
	//checkLightSensor  do not check light sensor: see #define values
	//                  do check light sensor and stop when it is over black or void
	
	reset_counters();

	//convert inches to clicks
	int clicks =(int) (156.25l * distanceInInches);
	int initial_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int initial_position_left = get_motor_position_counter(LEFT_MOTOR);
	
	int current_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int current_position_left = get_motor_position_counter(LEFT_MOTOR);
	int differential  = 0 ;
	//we will keep moving until both motors have covered their distance or
	//the light sensor is tripped
	while (current_position_left <= (initial_position_left + clicks) ||
		current_position_right <= (initial_position_right + clicks) || 
		(analog10(LIGHT_SENSOR) > 512 && checkLightSensor == CHECK_LIGHT_SENSOR) )	{
		
		//first let's see if one motor is going ahead of the other
		differential = current_position_left - initial_position_left - 
				(current_position_right - initial_position_right);
		if (differential > -25 && differential < 25 ) {
		//counter are around the same 
			mav(RIGHT_MOTOR, SPEED_FWD);
			mav(LEFT_MOTOR, SPEED_FWD);
		} else if (differential < 0 ) {
		//right has moved ahead, let's slow down right until left catches up
			mav(RIGHT_MOTOR,(int) (SPEED_FWD*ADJUST_SPEED));
			mav(LEFT_MOTOR, SPEED_FWD);
			printf("adjusting LEFT L: %d R: %d\n", (current_position_left - initial_position_left), (current_position_right - initial_position_right));
		} else {
		//left has moved ahead, let's slow down left until right catches up
			mav(RIGHT_MOTOR, SPEED_FWD);
			mav(LEFT_MOTOR, (int) (SPEED_FWD*ADJUST_SPEED));
			printf("adjusting RIGHT L: %d R: %d\n", (current_position_left - initial_position_left), (current_position_right - initial_position_right));
		}
		msleep(100);
		current_position_right = get_motor_position_counter(RIGHT_MOTOR);
		current_position_left = get_motor_position_counter(LEFT_MOTOR);
	}
	//turn off motors completely
	ao();
	msleep(100);
	//printf("done moving %d...", distanceInInches);
}

//uses a home made mrp (move to relative position) and convert from inches
//to motor units.
void moveBackward(double distanceInInches) {
	//printf("starting to move for %d\n",distanceInInches);
	reset_counters();
	//convert inches to clicks
	int clicks =(int) (156.25l * distanceInInches);
	int initial_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int initial_position_left = get_motor_position_counter(LEFT_MOTOR);
	
	int current_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int current_position_left = get_motor_position_counter(LEFT_MOTOR);
	int differential  = 0 ;
	while (current_position_left >= (initial_position_left - clicks) ||
		current_position_right >= (initial_position_right - clicks) ) {
		
		//first let's see if one motor is going ahead of the other
		differential = current_position_left - initial_position_left - 
				(current_position_right - initial_position_right);
		if (differential > -25 && differential < 25 ) {
			mav(RIGHT_MOTOR, SPEED_BWD);
			mav(LEFT_MOTOR, SPEED_BWD);
		} else if (differential > 0 ) {
			mav(RIGHT_MOTOR, (int) (SPEED_BWD*ADJUST_SPEED));
			mav(LEFT_MOTOR, SPEED_BWD);
			printf("bwd adjusting left L: %d R: %d\n", (current_position_left - initial_position_left), (current_position_right - initial_position_right));
		} else {
			mav(RIGHT_MOTOR, SPEED_BWD);
			mav(LEFT_MOTOR, (int) (SPEED_BWD*ADJUST_SPEED));
			printf("bwd adjusting right L: %d R: %d\n", (current_position_left - initial_position_left), (current_position_right - initial_position_right));
		}
		msleep(100);
		current_position_right = get_motor_position_counter(RIGHT_MOTOR);
		current_position_left = get_motor_position_counter(LEFT_MOTOR);
	}
	//turn off motors completely
	ao();
	msleep(100);

	//printf("done moving %d...", distanceInInches);
}


//right angle turn function
void rightAngleFwdA(int direction) {
	reset_counters();
	if (direction == RIGHT) {
		//printf("test turning right");
		mrp(LEFT_MOTOR,SPEED_FWD,RIGHT_ANGLE_CLICKS);
		bmd(LEFT_MOTOR);
	} else if (direction == LEFT) {
		//printf ("test turning left");
		mrp(RIGHT_MOTOR, SPEED_FWD, RIGHT_ANGLE_CLICKS) ;
		bmd(RIGHT_MOTOR);
	} else {
		printf("ooopppsss I did not recognize your turn... so I ignored it");
	}
	//turn off motors completely
	ao();
	msleep(100);

}


//right angle turn function
void rightAngleFwd(int direction) {
	reset_counters();
	if (direction == RIGHT) {
		//printf("test turning right");
		mrp(LEFT_MOTOR,SPEED_FWD,RIGHT_ANGLE_CLICKS);
		bmd(LEFT_MOTOR);
	} else if (direction == LEFT) {
		//printf ("test turning left");
		mrp(RIGHT_MOTOR, SPEED_FWD, RIGHT_ANGLE_CLICKS) ;
		bmd(RIGHT_MOTOR);
	} else {
		printf("ooopppsss I did not recognize your turn... so I ignored it");
	}
	//turn off motors completely
	ao();
	msleep(100);

}
void rightAngleBwd(int direction) {
	reset_counters();

	if (direction == LEFT) {
		//printf("test turning right");
		mrp(LEFT_MOTOR,SPEED_BWD,RIGHT_ANGLE_CLICKS_BACK);
		bmd(LEFT_MOTOR);
	} else if (direction == RIGHT) {
		//printf ("test turning left");
		mrp(RIGHT_MOTOR, SPEED_BWD, RIGHT_ANGLE_CLICKS_BACK) ;
		bmd(RIGHT_MOTOR);
	} else {
		printf("ooopppsss I did not recognize your turn... so I ignored it");
	}
	//turn off motors completely
	ao();
	msleep(100);

}
void fortyFiveAngleFwd(int direction) {
	if (direction == RIGHT) {
		//printf("test turning right");
		mrp(LEFT_MOTOR,SPEED_FWD,FV_ANGLE_CLICKS);
		bmd(LEFT_MOTOR);
	} else if (direction == LEFT) {
		//printf ("test turning left");
		mrp(RIGHT_MOTOR, SPEED_FWD, FV_ANGLE_CLICKS) ;
		bmd(RIGHT_MOTOR);
	} else {
		printf("ooopppsss I did not recognize your turn... so I ignored it");
	}
	//turn off motors completely
	ao();
	msleep(100);
	
}
void fortyFiveAngleBwd(int direction) {
	if (direction == LEFT) {
		//printf("test turning right");
		mrp(LEFT_MOTOR,SPEED_BWD,FV_ANGLE_CLICKS_BACK);
		bmd(LEFT_MOTOR);
	} else if (direction == RIGHT) {
		//printf ("test turning left");
		mrp(RIGHT_MOTOR, SPEED_BWD, FV_ANGLE_CLICKS_BACK) ;
		bmd(RIGHT_MOTOR);
	} else {
		printf("ooopppsss I did not recognize your turn... so I ignored it");
	}
	//turn off motors completely
	ao();
	msleep(100);

}

void clawUp(){
	set_servo_position(0,UP_SERVO);
}
	
void clawDown(){
	set_servo_position(0,DOWN_SERVO);
}
void clawUpCube(){
    set_servo_position(0,UP_SERVO_CUBE);
}
void clawDownCube(){
    set_servo_position(0,DOWN_SERVO_CUBE);
}
void reset_counters(){
	 clear_motor_position_counter(0);
	clear_motor_position_counter(2);
}
