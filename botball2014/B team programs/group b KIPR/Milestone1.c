// Created on Thu February 6 2014
//quick and dirty program to see if mav API is more reliable than motor
//to improve dead recknoning outcome.
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 0
#define SPEED_FWD 700
#define SPEED_BWD -700
#define ADJUST_SPEED 0.65
#define RIGHT 76
#define LEFT 57
#define RIGHT_ANGLE_CLICKS 1430
#define RIGHT_ANGLE_CLICKS_BACK -1430
#define FV_ANGLE_CLICKS 744
#define FV_ANGLE_CLICKS_BACK -744
#define UP_SERVO 1500
#define DOWN_SERVO 1015
#define UP_SERVO_CUBE 1900
#define DOWN_SERVO_CUBE 1300
//declaration
void moveForward(double distanceInInches); 
void moveBackward(double distanceInInces);
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
	printf("test calibration 2.03, fixed fowd and bwd function bugs.\n");
	
	
	enable_servos();
    reset_counters();
	clawUp();
	moveBackward(1);
	moveForward(22);
	clawDown();
	
	printf("i is turning\n");
	reset_counters();
	rightAngleFwd(LEFT);
	moveBackward(4);
	reset_counters();
	rightAngleFwd(LEFT);
	printf("i is finished turning\n");
	moveBackward(25);
	moveForward(3);
	reset_counters();
	rightAngleFwd(LEFT);
	reset_counters();
	moveForward(5);
	clawUp();
	moveForward(6);
	
	
	//Milestone 2
	/* moveBackward(11);
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
	*/
	disable_servos();
	
	return 0;
}

//uses a home made mrp (move to relative position) and convert from inches
//to motor units.
void moveForward(double distanceInInches) {
	//printf("starting to move for %d\n",distanceInInches);
	//convert inches to clicks
	reset_counters();
	int clicks =(int) (156.25l * distanceInInches);
	int initial_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int initial_position_left = get_motor_position_counter(LEFT_MOTOR);
	
	int current_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int current_position_left = get_motor_position_counter(LEFT_MOTOR);
	int differential  = 0 ;
	while (current_position_left <= (initial_position_left + clicks) ||
		current_position_right <= (initial_position_right + clicks) ) {
		
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
	mav(RIGHT_MOTOR,0);
	mav(LEFT_MOTOR,0);
	//printf("done moving %d...", distanceInInches);
}


//uses a home made mrp (move to relative position) and convert from inches
//to motor units.
void moveBackward(double distanceInInches) {
	//printf("starting to move for %d\n",distanceInInches);
	//convert inches to clicks
	reset_counters();
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
	mav(RIGHT_MOTOR,0);
	mav(LEFT_MOTOR,0);

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
}


//right angle turn function
void rightAngleFwd(int direction) {
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
}
void rightAngleBwd(int direction) {
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
