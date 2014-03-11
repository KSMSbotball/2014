// Created on Thu February 6 2014
//quick and dirty program to see if mav API is more reliable than motor
//to improve dead recknoning outcome.
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 0
#define SPEED_FWD 700
#define SPEED_BWD -700
#define ADJUST_SPEED 0.70
#define RIGHT 76
#define LEFT 57
#define RIGHT_ANGLE_CLICKS 1300
#define RIGHT_ANGLE_CLICKS_BACK -1300
#define FV_ANGLE_CLICKS 744
#define FV_ANGLE_CLICKS_BACK -744
#define UP_SERVO 1900
#define DOWN_SERVO 1015
#define UP_SERVO_CUBE 1900
#define DOWN_SERVO_CUBE 1398
#define LIGHT_SENSOR 0
#define CHECK_LIGHT_SENSOR 101
#define NO_CHECK_LIGHT_SENSOR 197

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
	printf("test 3.03, fixed fowd and bwd function bugs.\n");
	//wait_for_light(1);
	shut_down_in(115);
	enable_servos();
	clawUp();
	moveBackward(3);
	printf("==> moving forward 22 inches\n");

	moveForward(22);
	clawDown();
	printf("==> moving R bwds\n");
	
	//we have the Poms
	rightAngleBwd(LEFT);
	msleep(100);
	//bump against the upper storage area
	printf("==> moving backward 20 inches\n");
	moveBackward(20);
	msleep(100);
	printf("==> moving forward 20 inches\n");
	moveForward(20);
	rightAngleBwd(LEFT);
	//bump against upper PVC side
	moveBackward(25);
	//move towards dropping poms
	
	

	moveForward(3);
	rightAngleFwd(LEFT);
	clawUp();
	moveForwardTilBlackLine(15);
	/*fortyFiveAngleFwd(RIGHT);
	moveForward(13.5);
	fortyFiveAngleFwd(RIGHT);
	moveForward(1.5);
	clawUp();*/
	 5
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
	
	ao();
	disable_servos();
	
	return 0;
}

void moveForward(double distanceInInches) {	
	moveForwardRoutine(distanceInInches, NO_CHECK_LIGHT_SENSOR);
}
//moves forward without light sensor

void moveForwardTilBlackLine(double distanceInInches) {
	moveForwardRoutine(distanceInInches, CHECK_LIGHT_SENSOR);
}
//moves forward with light sensor
void moveForwardRoutine(double distanceInInches, int checkLightSensor) {
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
		current_position_right <= (initial_position_right + clicks)   )	{
		
		//let's get out if the sensor is on
		if (checkLightSensor == CHECK_LIGHT_SENSOR && analog(LIGHT_SENSOR) > 512) 			{
			printf("exiting because of light sensor");
			break;
		}
		//first let's see if one motor is going ahead of the other
		differential = current_position_left - initial_position_left - 
				(current_position_right - initial_position_right);
			printf("sensor value: %d lightsensor %d \n", analog(LIGHT_SENSOR),checkLightSensor);
		if (differential > -25 && differential < 25 ) {
		//counter are around the same 
			mav(RIGHT_MOTOR, SPEED_FWD);
			mav(LEFT_MOTOR, SPEED_FWD);
			//printf("going straight, L: %d, R: %d\n", (current_position_left - initial_position_left), (current_position_right - initial_position_right));
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
}


void moveBackward(double distanceInInches) {
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
		} else {
			mav(RIGHT_MOTOR, SPEED_BWD);
			mav(LEFT_MOTOR, (int) (SPEED_BWD*ADJUST_SPEED));
		}
		msleep(100);
		current_position_right = get_motor_position_counter(RIGHT_MOTOR);
		current_position_left = get_motor_position_counter(LEFT_MOTOR);
	}
	//turn off motors completely
	ao();
	msleep(100);

}


//right angle turn function
void rightAngleFwd(int direction ) {
	
	reset_counters();

	int current_position_left = get_motor_position_counter(LEFT_MOTOR);
	int current_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int initial_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int initial_position_left = get_motor_position_counter(LEFT_MOTOR);
	while ((current_position_right - initial_position_right + current_position_left - initial_position_left)<= RIGHT_ANGLE_CLICKS) {
		if (direction == RIGHT) {
			mav(LEFT_MOTOR,SPEED_FWD);
		} else if (direction == LEFT) {
		    mav(RIGHT_MOTOR, SPEED_FWD) ;
		}
		msleep(25);
		current_position_left = get_motor_position_counter(LEFT_MOTOR);
		current_position_right = get_motor_position_counter(RIGHT_MOTOR);
		printf("right angle fwd L Init , curr, R Init, curr : LI %d LC %d RI %d RC %d\n", initial_position_left,current_position_left , initial_position_right,current_position_right );
		
	} 
	//turn off motors completely
	ao();
	msleep(100);

}



//right angle turn function
void rightAngleFwdA(int direction) {
	reset_counters();
	if (direction == RIGHT) {
		mrp(LEFT_MOTOR,SPEED_FWD,RIGHT_ANGLE_CLICKS);
		bmd(LEFT_MOTOR);
	} else if (direction == LEFT) {
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
void rightAngleBwd(int direction ) {
	
	reset_counters();

	int current_position_left = get_motor_position_counter(LEFT_MOTOR);
	int current_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int initial_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int initial_position_left = get_motor_position_counter(LEFT_MOTOR);
	while ((current_position_right - initial_position_right + current_position_left - initial_position_left)>= RIGHT_ANGLE_CLICKS_BACK) {
		if (direction == RIGHT) {
			mav(RIGHT_MOTOR,SPEED_BWD);
		} else if (direction == LEFT) {
		    mav(LEFT_MOTOR, SPEED_BWD) ;
		}
		msleep(25);
		current_position_left = get_motor_position_counter(LEFT_MOTOR);
		current_position_right = get_motor_position_counter(RIGHT_MOTOR);
		printf("right angle bwd L Init , curr, R Init, curr : LI %d LC %d RI %d RC %d\n", initial_position_left,current_position_left , initial_position_right,current_position_right );
		
	} 
	//turn off motors completely
	ao();
	msleep(100);

}
void rightAngleBwdA(int direction) {
	reset_counters();
//right angle backwards
	printf("right angle back %d\n", RIGHT_ANGLE_CLICKS_BACK);
	if (direction == LEFT) {
		mrp(LEFT_MOTOR,SPEED_BWD,RIGHT_ANGLE_CLICKS_BACK);
		bmd(LEFT_MOTOR);
	} else if (direction == RIGHT) {
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
	//fortyfive degree forward turn
	if (direction == RIGHT) {
		mrp(LEFT_MOTOR,SPEED_FWD,FV_ANGLE_CLICKS);
		bmd(LEFT_MOTOR);
	} else if (direction == LEFT) {
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
	//forty five degree backwards turn
	if (direction == LEFT) {
		mrp(LEFT_MOTOR,SPEED_BWD,FV_ANGLE_CLICKS_BACK);
		bmd(LEFT_MOTOR);
	} else if (direction == RIGHT) {
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
	//puts the claw up
	set_servo_position(0,UP_SERVO);
}
	
void clawDown(){
	//puts the claw down
	set_servo_position(0,DOWN_SERVO);
}
void clawUpCube(){
//moves the claw to the position we need for the claw 
	set_servo_position(0,UP_SERVO_CUBE);
}
void clawDownCube(){
	//moves the claw to the position we need for the claw
    set_servo_position(0,DOWN_SERVO_CUBE);
}
void reset_counters(){
	//resets the motor counters
	clear_motor_position_counter(RIGHT_MOTOR);
	clear_motor_position_counter(LEFT_MOTOR);
	msleep(100);
}
