// Created on Thu February 6 2014
//quick and dirty program to see if mav API is more reliable than motor
//to improve dead recknoning outcome.
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 0
#define SPEED_FWD 700
#define SPEED_BWD -700
#define RIGHT 76
#define LEFT 57
#define RIGHT_ANGLE_CLICKS 1478
#define RIGHT_ANGLE_CLICKS_BACK -1478
#define FV_ANGLE_CLICKS 739
#define FV_ANGLE_CLICKS_BACK -739
#define UP_SERVO 1246
#define DOWN_SERVO 1015
#define UP_SERVO_CUBE 1500
#define DOWN_SERVO_CUBE 1398
//declaration
void moveForward(int distanceInInches); 
void moveBackward(int distanceInInces);
void rightAngleFwd(int direction);
void rightAngleBwd(int direction);
void fortyFiveAngleFwd(int direction);
void fortyFiveAngleBwd(int direction);
void clawUp();
void clawDown();
void clear_motor_position_counter(int motor_nbr);
void clear_motor_position_counter(int motor_nbr);

int main()
{
	printf("test calibration 1.94\n");
	
    clear_motor_position_counter(0);
	clear_motor_position_counter(2);
	
	enable_servos();
	
	clawUp();
	moveBackward(3);

	moveForward(22);
	clawDown();
	rightAngleFwd(LEFT);
	moveBackward(3);
	rightAngleFwd(LEFT);
	moveBackward(25);
	rightAngleFwd(LEFT);
	moveForward(10);
<<<<<<< HEAD
=======
	moveForward(5);
	rightAngleFwd(LEFT);
	clawUp();
	moveForward(14);
>>>>>>> 43e2c3980130272fa697d7e682e624a5c224e48b
	/*fortyFiveAngleFwd(RIGHT);
	moveForward(13.5);
	fortyFiveAngleFwd(RIGHT);
	moveForward(1.5);
	clawUp();*/
	
	/*Milestone 2
	moveBackward(11);
	rightAngleBwd(RIGHT);
	moveBackward(9);
	moveForward(9);
	rightAngleFwd(RIGHT);
	moveForward(22);
	clawDown();
	fortyFiveAngleFwd(LEFT);
	moveForward(20);
	//printf("program finished, POMS should be in...\n");
	*/
	disable_servos();
	
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
    
	void clear_motor_position_counter(int motor_nbr);
	
