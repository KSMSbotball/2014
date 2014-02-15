// Created on Thu February 6 2014
//quick and dirty program to see if mav API is more reliable than motor
//to improve dead recknoning outcome.
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 0
#define SPEED_FWD 500
#define SPEED_BWD -500
#define RIGHT 76
#define LEFT 57
#define RIGHT_ANGLE_CLICKS 1450
//declaration
void moveForward(int distanceInInches); 
void moveBackward(int distanceInInces);
void rightAngle(int direction);

int main()
{
<<<<<<< HEAD
	printf("test calibration 1.4\n");
	
/*	moveForward(5);
=======
	printf("test calibration 1.3\n");

	moveForward(5);
>>>>>>> 54f1150b8f40d8e40bd73689c68b9bbf15136053
	set_a_button_text("Click me to continue\n");
	while (a_button() == 0) {
		msleep(25);
	}
	moveForward(10);
	while (a_button() == 0) {
		msleep(25);
	}
	moveForward(2);
	*/
	printf("testing right angle turn");
	moveForward(10);
	rightAngle(RIGHT);
	moveForward(10);
	printf("program finished\n");
	return 0;
}

//convenience function to make code reading easier
void moveBackward(int distanceInInches) {
	moveForward(distanceInInches * -1);
}

//uses mrp (move to relative position) and convert from inches
//to motor units. This is pretty accurate (a lot more than motor at speed)
void moveForward(int distanceInInches) {
	printf("starting to move for %d\n",distanceInInches);
	//convert inches to clicks
	long clicks = 156.25l * distanceInInches;
	mrp(RIGHT_MOTOR, SPEED_FWD, clicks);
	mrp(LEFT_MOTOR, SPEED_FWD, clicks);
	bmd(RIGHT_MOTOR);
	bmd(LEFT_MOTOR);
<<<<<<< HEAD
	
	printf("done moving %d...", distanceInInches);
=======

	printf("done moving %ld...", distanceInInches);
>>>>>>> 54f1150b8f40d8e40bd73689c68b9bbf15136053
}

//right angle turn function
void rightAngle(int direction) {
	if (direction == RIGHT) {
		printf("test turning right");
		mrp(LEFT_MOTOR,SPEED_FWD,RIGHT_ANGLE_CLICKS);
		bmd(LEFT_MOTOR);
	} else if (direction == LEFT) {
		printf ("test turning left");
		mrp(RIGHT_MOTOR, SPEED_FWD, RIGHT_ANGLE_CLICKS) ;
		bmd(RIGHT_MOTOR);
	} else {
		printf("ooopppsss I did not recognize your turn... so I ignored it");
	}
}
	
