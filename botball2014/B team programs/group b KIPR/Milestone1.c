// Created on Thu February 6 2014
//quick and dirty program to see if mav API is more reliable than motor
//to improve dead recknoning outcome.
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 0
#define SPEED_FWD 700
#define SPEED_BWD -700
#define RIGHT 76
#define LEFT 57
#define RIGHT_ANGLE_CLICKS 1450
#define RIGHT_ANGLE_CLICKS_BACK -1450
#define FV_ANGLE_CLICKS 700
#define FV_ANGLE_CLICKS_BACK -700
#define UP_SERVO 1246
#define DOWN_SERVO 1015
//declaration
void moveForward(int distanceInInches); 
void moveBackward(int distanceInInces);
void rightAngleFwd(int direction);
void rightAngleBwd(int direction);
void fortyFiveAngleFwd(int direction);
void fortyFiveAngleBwd(int direction);

int main()
{
	printf("test calibration 1.93\n");
	
	enable_servos();

	moveForward(22);
	fortyFiveAngleFwd(RIGHT);
	moveForward(13.5);
	fortyFiveAngleFwd(RIGHT);
	moveForward(2);
	
	
	//Milestone 2
	moveBackward(11);
	rightAngleBwd(RIGHT);
	moveBackward(9);
	moveForward(9);
	rightAngleFwd(RIGHT);
	moveForward(22);
	fortyFiveAngleFwd(LEFT);
	moveForward(20);
	//printf("program finished, POMS should be in...\n");
	
	disable_servo();
	
	return 0;
}

//convenience function to make code reading easier
void moveBackward(int distanceInInches) {
	//printf("starting to move backwards for %d\n",distanceInInches);
	//convert inches to clicks
	moveForward(distanceInInches * -1);

}

//uses mrp (move to relative position) and convert from inches
//to motor units. This is pretty accurate (a lot more than motor at speed)
void moveForward(int distanceInInches) {
	//printf("starting to move for %d\n",distanceInInches);
	//convert inches to clicks
	long clicks = 156.25l * distanceInInches;
	mrp(RIGHT_MOTOR, SPEED_FWD, clicks);
	mrp(LEFT_MOTOR, SPEED_FWD, clicks);
	bmd(RIGHT_MOTOR);
	bmd(LEFT_MOTOR);
	
	//printf("done moving %d...", distanceInInches);
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
