#define IR_SENSOR 0
#define IR_SENSOR_THRESHOLD 150
//less than 1 will make the robot go more towards the right
//more than 1 will make the robot go more left (should be between 0.95 and 1.05)
#define MOTOR_CORRECTION_FACTOR_LEFT 0.95;

//#define DOWN_SERVO 1000
#define DOWN_SERVO 1025
#define UP_SERVO 1900
#define UP_SERVO_CUBE 1900
#define ALMOST_DOWN_SERVO_CUBE 1480
//#define RIGHT_ANGLE_CLICKS_MRP_LEFT 1490
#define RIGHT_ANGLE_CLICKS_MRP_LEFT 1450
//#define RIGHT_ANGLE_CLICKS_MRP_RIGHT 1450
#define RIGHT_ANGLE_CLICKS_MRP_RIGHT 1490
//#define RIGHT_ANGLE_CLICKS_BACK_MRP -1450
#define RIGHT_ANGLE_CLICKS_BACK_MRP -1450


#define MRP 0
#define MAV 1
#define MRP_OR_MAV 0
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 0
#define SPEED_FWD_SLOW 400
#define SPEED_FWD 800
#define SPEED_FWD_HIGH_SPEED 1000

#define SPEED_BWD -800
#define SPEED_BWD_HIGH -1000
#define ADJUST_SPEED 0.70
#define RIGHT 76
#define LEFT 57
#define RIGHT_ANGLE_CLICKS_LEFT 1330
#define RIGHT_ANGLE_CLICKS_RIGHT 1500
#define RIGHT_ANGLE_CLICKS_BACK -1250
#define FV_ANGLE_CLICKS 727
#define TT_ANGLE_CLICKS 340
#define FV_ANGLE_CLICKS_BACK -744
#define DOWN_SERVO_CUBE 1420

#define CHECK_IR_SENSOR 101
#define NO_CHECK_IR_SENSOR 197
#define DEBUG 10
#define NO_DEBUG 12
//declaration
void moveForward(double distanceInInches, int debug); 
void moveForwardSlow(double distanceInInches, int debug); 
void moveForwardHighSpeed(double distanceInInches, int debug); 
void moveForwardTilBlackLine(double distanceInInches, int debug);
void moveForwardRoutine(double distanceInInches,int checkLightSensor, int speed, int debug); 

void moveBackward(double distanceInInces, int debug);
void moveBackwardRoutine(double distanceInInces, int speed, int debug);
void moveBackwardHighSpeed(double distanceInInces, int debug);	
void rightAngleFwd(int direction, int debug);
void rightAngleBwd(int direction, int debug);
void rightAngleFwdMrp(int direction, int debug);
void rightAngleBwdMrp(int direction, int debug);
void rightAngleFwdMav(int direction, int debug);
void rightAngleBwdMav(int direction, int debug);
void fortyFiveAngleFwd(int direction, int debug);
void twentyTwoAngleFwd(int direction, int debug);
void clawUp();
void clawDown();
void clawDownCube();
void clawAlmostDownCube();
void clawUpCube();
void reset_motors();
int main()
{
	/* FIRST CALIBRATION: based on poms position adjust starting position
	*/
	
	printf("test 3.11, calibration value: \nclaw down : %d, \nright ang forward right: %d, \nright ang forward left  : %d, \nback right angle %d ...\n", DOWN_SERVO, RIGHT_ANGLE_CLICKS_MRP_RIGHT, RIGHT_ANGLE_CLICKS_MRP_LEFT, RIGHT_ANGLE_CLICKS_BACK_MRP);
	double start_time = seconds();
	enable_servos();
	clear_motor_position_counter(RIGHT_MOTOR);
	clear_motor_position_counter(LEFT_MOTOR);
	//wait_for_light(1);
	//shut_down_in(118);	
	clawUp();
	//**************************************
	//* PART 1 : get first set of poms to lower storage area
	//*
	//**************************************
	moveBackward(1, NO_DEBUG);
	moveForwardHighSpeed(23, DEBUG);
	clawDown();
	//moveForward(8,NO_DEBUG);
	//we have the Poms
	rightAngleBwd(RIGHT, NO_DEBUG);
	//bump against the upper storage area
	moveBackwardHighSpeed(15, NO_DEBUG);
	moveForwardHighSpeed(17, NO_DEBUG);
	
	rightAngleBwd(RIGHT, NO_DEBUG);
	//bump against upper PVC side
	moveBackwardHighSpeed(18, NO_DEBUG);
	//move towards dropping poms
	moveForward(1.5, NO_DEBUG);
	msleep(300);
	rightAngleFwd(LEFT, NO_DEBUG);
	msleep(300);
	clawUp();
	//uses IR sensor to stop the forward movement
	moveForwardTilBlackLine(15, NO_DEBUG);
	printf("====> elapsed time end of part 1: %f\n", (seconds() - start_time));

	//**************************************
	//* END OF PART 1 : get first set of poms to lower storage area
	//*
	//**************************************

	//**************************************
	//* PART 2 : get the blue cube to the corner
	//*
	//**************************************
	moveBackwardHighSpeed(25, NO_DEBUG);
	//recalibrate against top PVC next to botguy
	rightAngleBwd(LEFT, NO_DEBUG);
	moveBackwardHighSpeed(11, NO_DEBUG);
		
	// SECOND CALIBRATION: based on blackline/blue position
	
	
	moveForward(7.5, NO_DEBUG);
	
	rightAngleFwd(RIGHT, NO_DEBUG);
	//get the cube now

	//====>>>>> may have to be adjust the day of competition based on position of 2nd
	//====>>>>> set of poms
	moveForwardHighSpeed(17, NO_DEBUG);
	//====>>>>>

	clawAlmostDownCube();
	twentyTwoAngleFwd(LEFT, NO_DEBUG);
	clawUp();
	//====>>>>> calibration to get to the corner 22.5 fwd, 22.5 more forward, aiming at bottom left hand corner
	moveForwardHighSpeed(2.5, NO_DEBUG);
	twentyTwoAngleFwd(LEFT, NO_DEBUG);
	//clawAlmostDownCube();
	moveForwardHighSpeed(30, NO_DEBUG);
	
	//====>>>>> 
	//moveForwardHighSpeed(2, NO_DEBUG);
	
	//====>>>>>
	moveBackwardHighSpeed(9, NO_DEBUG);
	fortyFiveAngleFwd(LEFT, NO_DEBUG);

	printf("====> elapsed time end of part 2: %f\n", (seconds() - start_time));
	//**************************************
	//* END OF PART 2 : get the blue cube in the corner
	//*
	//**************************************

	//**************************************
	//* PART 3 : prepare to get second set of poms
	//*
	//**************************************
	//recalibrate against side PVC
	rightAngleBwd(RIGHT, NO_DEBUG);
	moveBackwardHighSpeed(15, NO_DEBUG);		
	moveForward(5, NO_DEBUG);
	//calibrating with top PVC
	rightAngleBwd(LEFT,NO_DEBUG);
	moveBackwardHighSpeed(23,NO_DEBUG);
	// THIRD CALIBRATION: based on second set of Poms
	//below is the number of inches from the side PVC
	//
	moveForwardHighSpeed(10, NO_DEBUG);
	rightAngleBwd(RIGHT, NO_DEBUG);
	//recalibrate with side pvc
	moveBackwardHighSpeed(5,NO_DEBUG);
	printf("====> elapsed time end of part 3: %f\n", (seconds() - start_time));

	//**************************************
	//* END OF PART 3 : prepare to get second set of poms
	//*
	//**************************************
	
	//**************************************
	//* PART 4 : bring second set of poms home
	//*
	//**************************************
	//grabs the poms, bring down claw and go home
	moveForwardHighSpeed(12.5,NO_DEBUG);
	clawDown();
	moveForwardHighSpeed(59.5, NO_DEBUG);
	//here is the code to recalibrate one more time... but do we have enough time?
	/*//recalibrate against top PVC
	rightAngleBwd(LEFT,NO_DEBUG);
	
	moveBackwardHighSpeed(10, NO_DEBUG);
	//move towards dropping poms
	
	moveForwardHighSpeed(10, NO_DEBUG);
	//msleep(500);
	printf("==> moving righ angle bwd\n");
	rightAngleFwd(LEFT, NO_DEBUG);
	*/
	//recalibrate against top PVC
	//moveForwardHighSpeed(41,NO_DEBUG);
	
	//last calibration before dropping second set of poms
	rightAngleBwd(LEFT,NO_DEBUG);
	moveBackwardHighSpeed(14, NO_DEBUG);
	//move towards dropping poms
	moveForwardSlow(1.5, NO_DEBUG);
	msleep(300);
	rightAngleFwd(LEFT, NO_DEBUG);
	msleep(300);
	clawUp();
	moveForwardTilBlackLine(15, DEBUG);

	//**************************************
	//* END OF PART 4 : bring second set of poms home
	//*
	//**************************************

	printf("====> elapsed time: %f\n", (seconds() - start_time));
	ao();
	disable_servos();
	return 0;
}



//****************************
//*  function bodies below
//*
//*****************************

void moveForwardSlow(double distanceInInches, int debug) {	
	moveForwardRoutine(distanceInInches, NO_CHECK_IR_SENSOR, SPEED_FWD_SLOW, debug);
}

void moveForwardHighSpeed(double distanceInInches, int debug) {	
	moveForwardRoutine(distanceInInches, NO_CHECK_IR_SENSOR, SPEED_FWD_HIGH_SPEED, debug);
}



void moveForward(double distanceInInches, int debug) {	
	moveForwardRoutine(distanceInInches, NO_CHECK_IR_SENSOR, SPEED_FWD, debug);
}

//moves forward without light sensor
void moveForwardTilBlackLine(double distanceInInches, int debug) {
	moveForwardRoutine(distanceInInches, CHECK_IR_SENSOR, SPEED_FWD,debug);
}


//moves forward with light sensor
void moveForwardRoutine(double distanceInInches, int checkIRSensor, int speed, int debug) {
	//checkLightSensor	do not check light sensor: see #define values
	//                do check light sensor and stop when it is over black or void
	//convert inches to clicks
	int speed_adjust_up = (int) (speed / ADJUST_SPEED);
	int speed_adjust_down = (int) (speed * ADJUST_SPEED);
	printf("speed down %d, speed up: %d\n", speed_adjust_down, speed_adjust_up);

	int clicks =(int) (156.25l * distanceInInches);
	int initial_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int initial_position_left = get_motor_position_counter(LEFT_MOTOR);
	int current_position_right = get_motor_position_counter(RIGHT_MOTOR);
	int current_position_left = get_motor_position_counter(LEFT_MOTOR);
	float differential  = 0 ;
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
		differential = (current_position_left - initial_position_left) 
					* MOTOR_CORRECTION_FACTOR_LEFT ;
		differential = differential - (current_position_right - initial_position_right);
//			if (debug == DEBUG) {
//				printf("sensor value: %d lightsensor %d \n", analog(IR_SENSOR),checkIRSensor);
//			}
		if (differential > -25 && differential < 25 ) {
		//counter are around the same 
			mav(RIGHT_MOTOR, speed);
			mav(LEFT_MOTOR, speed);
		} else if (differential < 0 ) {
		//right has moved ahead, let's slow down right until left catches up
			mav(RIGHT_MOTOR,speed_adjust_down);
			mav(LEFT_MOTOR, speed_adjust_up);
			if (debug == DEBUG) {
				printf("adjusting LEFT L: %d R: %d, diff %f\n", (current_position_left - 				initial_position_left), (current_position_right - initial_position_right), differential);
			}
		} else {
		//left has moved ahead, let's slow down left until right catches up
			mav(RIGHT_MOTOR, speed_adjust_up);
			mav(LEFT_MOTOR, speed_adjust_down);
			if (debug == DEBUG) {
				printf("adjusting RIGHT L: %d R: %d diff %f\n", (current_position_left - initial_position_left), (current_position_right - initial_position_right), differential);
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
void moveBackward(double distanceInInches,int debug) {
	//convert inches to clicks

	moveBackwardRoutine(distanceInInches, SPEED_BWD, debug);
}

void moveBackwardHighSpeed(double distanceInInches,int debug) {
	//convert inches to clicks

	moveBackwardRoutine(distanceInInches, SPEED_BWD_HIGH, debug);
}


void moveBackwardRoutine(double distanceInInches,int speed, int debug) {
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
			mav(RIGHT_MOTOR, speed);
			mav(LEFT_MOTOR, speed);
		} else if (differential > 0 ) {
			mav(RIGHT_MOTOR, (int) (speed*ADJUST_SPEED));
			mav(LEFT_MOTOR, (speed * 1.1));
		} else {
			mav(RIGHT_MOTOR, (speed * 1.1));
			mav(LEFT_MOTOR, (int) (speed*ADJUST_SPEED));
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
//right angle turn forward function
void rightAngleFwd(int direction , int debug) {
	if (MRP_OR_MAV == MRP) {
		rightAngleFwdMrp(direction, debug);
	} else {
		rightAngleFwdMav(direction, debug);
	} 
}
//right angle turn function
void rightAngleFwdMav(int direction, int debug ) {
	int clickNbrTarget = RIGHT_ANGLE_CLICKS_LEFT;
	int initial_position = get_motor_position_counter(RIGHT_MOTOR);
	if (direction == RIGHT) {
		clickNbrTarget = RIGHT_ANGLE_CLICKS_RIGHT;
		initial_position = get_motor_position_counter(LEFT_MOTOR);
	}
	int current_position = initial_position;
	if (direction == RIGHT) {
		mav(LEFT_MOTOR,SPEED_FWD/2);
	} else if (direction == LEFT) {
		mav(RIGHT_MOTOR, SPEED_FWD/2) ;
	}
	while ((current_position - initial_position)<= clickNbrTarget) {
		msleep(25);
		current_position = get_motor_position_counter(RIGHT_MOTOR);
		if (direction == RIGHT) {
			current_position = get_motor_position_counter(LEFT_MOTOR);
		}
		if (debug == DEBUG) {
			printf("right angle fwd Init %d , curr %d, tgt %d\n", initial_position,current_position , clickNbrTarget );
		}
	} 
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);
	reset_motors();
}
//right angle turn function
void rightAngleFwdMrp(int direction, int debug ) {
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);
	msleep(100);
	int initial_position = get_motor_position_counter(RIGHT_MOTOR);
	if (direction == RIGHT) {
		initial_position = get_motor_position_counter(LEFT_MOTOR);
	}
	int current_position = initial_position;
	if (direction == RIGHT) {
		mrp(LEFT_MOTOR, SPEED_FWD, RIGHT_ANGLE_CLICKS_MRP_RIGHT);
		bmd(LEFT_MOTOR);
		if (debug == DEBUG) {
			printf("right angle mrp fwd RIGHT Init %d , curr %d, tgt %d\n", initial_position,current_position, RIGHT_ANGLE_CLICKS_MRP_RIGHT);
		}
		current_position = get_motor_position_counter(LEFT_MOTOR);
	} else if (direction == LEFT) {
		mrp(RIGHT_MOTOR, SPEED_FWD, RIGHT_ANGLE_CLICKS_MRP_LEFT);
		bmd(RIGHT_MOTOR);
		if (debug == DEBUG) {
			printf("right angle mrp fwd LEFT Init %d , curr %d, tgt %d\n", initial_position,current_position, RIGHT_ANGLE_CLICKS_MRP_LEFT);
		}
		current_position = get_motor_position_counter(RIGHT_MOTOR);
	}
		
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);
	reset_motors();
}
//right angle turn forward function
void rightAngleBwd(int direction , int debug) {
	if (MRP_OR_MAV == MRP) {
		rightAngleBwdMrp(direction, debug);
	} else {
		rightAngleBwdMav(direction, debug);
	} 
}
//right angle turn function
void rightAngleBwdMav(int direction, int debug ) {
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);
	msleep(100);
	int clickNbrTarget = RIGHT_ANGLE_CLICKS_BACK;
	int initial_position = get_motor_position_counter(RIGHT_MOTOR);
	if (direction == RIGHT) {
		clickNbrTarget = RIGHT_ANGLE_CLICKS_BACK;
		initial_position = get_motor_position_counter(LEFT_MOTOR);
	}
	int current_position = initial_position;
	if (direction == RIGHT) {
		mav(LEFT_MOTOR,SPEED_BWD);
	} else if (direction == LEFT) {
		mav(RIGHT_MOTOR, SPEED_BWD) ;
	}
	while ((current_position - initial_position) >= clickNbrTarget) {
		msleep(25);
		current_position = get_motor_position_counter(RIGHT_MOTOR);
		if (direction == RIGHT) {
			current_position = get_motor_position_counter(LEFT_MOTOR);
		}
		if (debug == DEBUG) {
			printf("right angle bwd mav Init %d , curr %d, tgt %d\n", initial_position,current_position , clickNbrTarget );
		}
	} 
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);
	reset_motors();
}
//right angle turn function
void rightAngleBwdMrp(int direction, int debug ) {
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);
	if (debug == DEBUG) {
		printf("starting right angle mrp bwd \n");
	}
	msleep(100);
	int initial_position = get_motor_position_counter(RIGHT_MOTOR);
	if (direction == RIGHT) {
		initial_position = get_motor_position_counter(LEFT_MOTOR);
	}
	int current_position = initial_position;
	if (direction == RIGHT) {
		mrp(LEFT_MOTOR, SPEED_BWD, RIGHT_ANGLE_CLICKS_BACK_MRP);
		bmd(LEFT_MOTOR);
		current_position = get_motor_position_counter(LEFT_MOTOR);
	} else if (direction == LEFT) {
		mrp(RIGHT_MOTOR, SPEED_BWD, RIGHT_ANGLE_CLICKS_BACK_MRP);
		bmd(RIGHT_MOTOR);
		current_position = get_motor_position_counter(RIGHT_MOTOR);
	}
		if (debug == DEBUG) {
			printf("right angle mrp bwd Init %d , curr %d, tgt %d\n", initial_position,current_position, RIGHT_ANGLE_CLICKS_BACK_MRP);
	}
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);
	reset_motors(); 
	
	
}

void fortyFiveAngleFwd(int direction, int debug) {
	//forty five degree backwards turn
	if (direction == RIGHT) {
		mrp(LEFT_MOTOR,(SPEED_FWD),FV_ANGLE_CLICKS);
		bmd(LEFT_MOTOR);
	} else if (direction == LEFT) {
		mrp(RIGHT_MOTOR, (SPEED_FWD), FV_ANGLE_CLICKS) ;
		bmd(RIGHT_MOTOR);
	} else {
		printf("ooopppsss I did not recognize your turn... so I ignored it");
	}
	//turn off motors completely
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR,0);
	reset_motors();
}

void twentyTwoAngleFwd(int direction, int debug) {
	//twenty two .5 degree backwards turn
	if (direction == RIGHT) {
		mrp(LEFT_MOTOR,(int)(SPEED_FWD*.7),TT_ANGLE_CLICKS);
		bmd(LEFT_MOTOR);
	} else if (direction == LEFT) {
		mrp(RIGHT_MOTOR, (int)(SPEED_FWD*.7), TT_ANGLE_CLICKS) ;
		bmd(RIGHT_MOTOR);
	} else {
		printf("ooopppsss I did not recognize your turn... so I ignored it");
	}
	//turn off motors completely
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR,0);
	reset_motors();
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
void clawAlmostDownCube(){
	//moves the claw to the position we need for the claw
    set_servo_position(0,ALMOST_DOWN_SERVO_CUBE);
}
void reset_motors(){
	//resets the motor counters
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR,0);
	msleep(200);
}
