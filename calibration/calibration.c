// Created on Thu February 6 2014
//quick and dirty program to see if mav API is more reliable than motor
//to improve dead recknoning outcome.
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 0
#define SPEED_FWD 700
#define SPEED_BWD -700
#define RIGHT 76
#define LEFT 57
#define RIGHT_ANGLE_CLICKS 1400
#define RIGHT_ANGLE_CLICKS_BACK -1400
#define FV_ANGLE_CLICKS 700
#define FV_ANGLE_CLICKS_BACK -700
//declaration
void moveForward(int distanceInInches); 
void moveBackward(int distanceInInces);
void rightAngleFwd(int direction);
void rightAngleBwd(int direction);
void fortyFiveAngleFwd(int direction);
void fortyFiveAngleBwd(int direction);

int main()
{
	printf("version 1.0 ");
	printf("moving forwrd 10 ");
	moveForward(10);
	printf("right angle right");
	rightAngleFwd(RIGHT);
	moveForward(10);
	printf("click a button to continue");
	while (a_button_clicked() == 0) {
		msleep(25);
	}
	
	printf("moving bckwrd 10 ");
	moveBackward(10);
	printf("right angle back right");
	rightAngleBwd(RIGHT);
	moveBackward(10);
	printf("click a button to continue");
	while (a_button_clicked() == 0) {
		msleep(25);
	}
	//printf("program finished, POMS should be in...\n");
	return 0;
}

//convenience function to make code reading easier
void moveBackward(int distanceInInches) {
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
	if (direction == RIGHT) {
		//printf("test turning right");
		mrp(LEFT_MOTOR,SPEED_BWD,RIGHT_ANGLE_CLICKS_BACK);
		bmd(LEFT_MOTOR);
	} else if (direction == LEFT) {
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
	if (direction == RIGHT) {
		//printf("test turning right");
		mrp(LEFT_MOTOR,SPEED_BWD,FV_ANGLE_CLICKS_BACK);
		bmd(LEFT_MOTOR);
	} else if (direction == LEFT) {
		//printf ("test turning left");
		mrp(RIGHT_MOTOR, SPEED_BWD, FV_ANGLE_CLICKS_BACK) ;
		bmd(RIGHT_MOTOR);
	} else {
		printf("ooopppsss I did not recognize your turn... so I ignored it");
	}
}
