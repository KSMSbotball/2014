// Created on Thu February 6 2014
//quick and dirty program to see if mav API is more reliable than motor
//to improve dead recknoning outcome.
#define RIGHT_MOTOR 0
#define LEFT_MOTOR 2
#define SPEED_FWD 500
#define SPEED_BWD -500

void moveForward(int distanceInInches); 

int main()
{
	printf("test calibration 1.3\n");

	moveForward(5);
	set_a_button_text("Click me to continue\n");
	while (a_button() == 0) {
		msleep(25);
	}
	moveForward(10);
	while (a_button() == 0) {
		msleep(25);
	}
	moveForward(2);
	printf("program finished\n");
	return 0;
}


void moveForward(int distanceInInches) {
	printf("starting to move for %d\n",distanceInInches);
	//convert inches to clicks
	long clicks = 156.25l * distanceInInches;
	mrp(RIGHT_MOTOR, SPEED_FWD, clicks);
	mrp(LEFT_MOTOR, SPEED_FWD, clicks);
	bmd(RIGHT_MOTOR);
	bmd(LEFT_MOTOR);

	printf("done moving %ld...", distanceInInches);
}
