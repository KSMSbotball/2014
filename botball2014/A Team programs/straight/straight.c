// Created on Thu February 13 2014
#define RIGHT_MOTOR 0
#define LEFT_MOTOR 2
#define SPEED_FWD 500
#define SPEED_BWD -500

void moveForward(int distanceInInches);

int main()
{
	/*
	motor(0, 67);
	motor(2, 70);
	msleep(5000);
	*/

	printf("test calibration 1.4\n");

	moveForward(20);
	set_a_button_text("Click me to continue\n");
	while (a_button() == 0) {
		msleep(25);
	}
	moveForward(20);
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
long clicksLeft = 160 * distanceInInches;
long clicksRight = clicksLeft * 0.9;// * 0.8;
mrp(RIGHT_MOTOR, SPEED_FWD, clicksRight);
mrp(LEFT_MOTOR, SPEED_FWD, clicksLeft);
bmd(RIGHT_MOTOR);
bmd(LEFT_MOTOR);

printf("done moving %ld...", distanceInInches);
}
