// Created on Thu February 6 2014
//quick and dirty program to see if mav API is more reliable than motor
//to improve dead recknoning outcome.
#define IR_SENSOR 0
#define IR_SENSOR_THRESHOLD 180

#define ADJUST_SPEED 0.70
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 0
#define SPEED_FWD_SLOW 400
#define SPEED_FWD 800
#define SPEED_FWD_HIGH_SPEED 1000
#define SPEED_BWD -700
#define RIGHT 76
#define LEFT 57
#define RIGHT_ANGLE_CLICKS 1400
#define RIGHT_ANGLE_CLICKS_BACK -1400
#define FV_ANGLE_CLICKS 739
#define FV_ANGLE_CLICKS_BACK -739
#define UP_SERVO 1250
#define DOWN_SERVO 1015
#define UP_SERVO_CUBE 1500
#define DOWN_SERVO_CUBE 1398

#define CHECK_IR_SENSOR 101
#define NO_CHECK_IR_SENSOR 197
#define DEBUG 10
#define NO_DEBUG 12

//declaration
void moveForward(double distanceInInches, int debug);
void moveForwardRoutine(double distanceInInches, int checkIRSensor, int speed, int debug);
void reset_motors();

void moveBackward(double distanceInInces);
void rightAngleFwd(int direction);
void rightAngleBwd(int direction);
void fortyFiveAngleFwd(int direction);
void fortyFiveAngleBwd(int direction);
void clawUp();
void clawDown();


int main()
{
	moveForward(63,DEBUG);
	
	return 0;
}

/*
trying a new way for move foward and backward
//convenience function to make code reading easier
void moveBackward(int distanceInInches) {
	//printf("starting to move backwards for %d\n",distanceInInches);
	//convert inches to clicks
	moveForward(distanceInInches * -1);

}

//uses mrp (move to relative position) and convert from inches
//to motor units. This is pretty accurate (a lot more than motor at speed)
void moveForward(double distanceInInches) {
	//printf("starting to move for %d\n",distanceInInches);
	//convert inches to clicks
	long clicks = 156.25l * distanceInInches;
	mrp(RIGHT_MOTOR, SPEED_FWD, clicks);
	mrp(LEFT_MOTOR, SPEED_FWD, clicks);
	bmd(RIGHT_MOTOR);
	bmd(LEFT_MOTOR);
	
	//printf("done moving %d...", distanceInInches);
}
*/
void moveForward(double distanceInInches, int debug) {	
	moveForwardRoutine(distanceInInches, NO_CHECK_IR_SENSOR, SPEED_FWD_HIGH_SPEED, debug);
}




//moves forward with light sensor
void moveForwardRoutine(double distanceInInches, int checkIRSensor, int speed, int debug) {
	//checkLightSensor	do not check light sensor: see #define values
	//                do check light sensor and stop when it is over black or void
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
		current_position_right <= (initial_position_right + clicks)   )	{
		//let's get out if the sensor is on
		if (checkIRSensor == CHECK_IR_SENSOR && analog(IR_SENSOR) > IR_SENSOR_THRESHOLD) 			{
			if (debug == DEBUG) {
				printf("exiting because of light sensor");
			}
			break;
		}
		//first let's see if one motor is going ahead of the other
		differential = current_position_left - initial_position_left - 
				(current_position_right - initial_position_right);
			if (debug == DEBUG) {
				printf("sensor value: %d lightsensor %d \n", analog(IR_SENSOR),checkIRSensor);
			}
		if (differential > -25 && differential < 25 ) {
		//counter are around the same 
			mav(RIGHT_MOTOR, speed);
			mav(LEFT_MOTOR, speed);
		} else if (differential < 0 ) {
		//right has moved ahead, let's slow down right until left catches up
			mav(RIGHT_MOTOR,(int) (speed*ADJUST_SPEED));
			mav(LEFT_MOTOR, speed);
			if (debug == DEBUG) {
				printf("adjusting LEFT L: %d R: %d\n", (current_position_left - 				initial_position_left), (current_position_right - initial_position_right));
			}
		} else {
		//left has moved ahead, let's slow down left until right catches up
			mav(RIGHT_MOTOR, speed);
			mav(LEFT_MOTOR, (int) (speed*ADJUST_SPEED));
			if (debug == DEBUG) {
				printf("adjusting RIGHT L: %d R: %d\n", (current_position_left - initial_position_left), (current_position_right - initial_position_right));
			}
		}
		msleep(25);
		current_position_right = get_motor_position_counter(RIGHT_MOTOR);
		current_position_left = get_motor_position_counter(LEFT_MOTOR);
	}
	//turn off motors completely
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR,0);
	ao();
	reset_motors();
}

void reset_motors(){
	//resets the motor counters
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR,0);
	msleep(200);
}
//uses a home made mrp (move to relative position) and convert from inches
//to motor units.
void moveBackward(double distanceInInches) {
	//printf("starting to move for %d\n",distanceInInches);
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
			mav(RIGHT_MOTOR, SPEED_BWD/2);
			mav(LEFT_MOTOR, SPEED_BWD);
		} else {
			mav(RIGHT_MOTOR, SPEED_BWD);
			mav(LEFT_MOTOR, SPEED_BWD/2);
		}
		msleep(100);
		current_position_right = get_motor_position_counter(RIGHT_MOTOR);
		current_position_left = get_motor_position_counter(LEFT_MOTOR);
	}
	
	//printf("done moving %d...", distanceInInches);
}


//right angle turn function
void rightAngleFwdA(int direction) {
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
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
