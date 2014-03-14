#define MRP 0
#define MAV 1
#define MRP_OR_MAV 0
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 0
#define SPEED_FWD 800
#define SPEED_BWD -800
#define ADJUST_SPEED 0.70
#define RIGHT 76
#define LEFT 57
#define RIGHT_ANGLE_CLICKS_MRP_LEFT 1450
#define RIGHT_ANGLE_CLICKS_MRP_RIGHT 1470
#define RIGHT_ANGLE_CLICKS_BACK_MRP -1450
#define RIGHT_ANGLE_CLICKS_LEFT 1330
#define RIGHT_ANGLE_CLICKS_RIGHT 1500
#define RIGHT_ANGLE_CLICKS_BACK -1250
#define FV_ANGLE_CLICKS 744
#define FV_ANGLE_CLICKS_BACK -744
#define UP_SERVO 1900
#define DOWN_SERVO 1000
#define UP_SERVO_CUBE 1900
#define DOWN_SERVO_CUBE 1370
#define LIGHT_SENSOR 0
#define CHECK_LIGHT_SENSOR 101
#define NO_CHECK_LIGHT_SENSOR 197
#define DEBUG 10
#define NO_DEBUG 12
//declaration
void moveForward(double distanceInInches, int debug); 
void moveForwardTilBlackLine(double distanceInInches, int debug);
void moveBackward(double distanceInInces, int debug);
void moveForwardRoutine(double distanceInInches, int checkLightSensor, int debug); 
void rightAngleFwd(int direction, int debug);
void rightAngleBwd(int direction, int debug);
void rightAngleFwdMrp(int direction, int debug);
void rightAngleBwdMrp(int direction, int debug);
void rightAngleFwdMav(int direction, int debug);
void rightAngleBwdMav(int direction, int debug);
void fortyFiveAngleFwd(int direction, int debug);
void fortyFiveAngleBwd(int direction, int debug);
void clawUp();
void clawDown();
void clawDownCube();
void clawUpCube();
void reset_motors();
int main()
{
	printf("test 1.00, message to the programer, :)this is the right program you need to debug it.\n");
	double start_time = seconds();
	//wait_for_light(1);
	shut_down_in(115);
	enable_servos();
	clear_motor_position_counter(RIGHT_MOTOR);
	clear_motor_position_counter(LEFT_MOTOR);
	clawUp();
	moveBackward(1, NO_DEBUG);
	printf("==> moving forward 22 inches\n");
	moveForward(22, NO_DEBUG);
	clawDown();
	printf("==> moving R bwds\n");
	//we have the Poms
	rightAngleBwd(RIGHT, NO_DEBUG);
	//bump against the upper storage area
	printf("==> moving backward 20 inches\n");
	moveBackward(15, NO_DEBUG);
	printf("==> moving forward 20 inches\n");
	moveForward(20, NO_DEBUG);
	printf("==> moving righ angle bwd\n");
	rightAngleBwd(RIGHT, NO_DEBUG);
	//bump against upper PVC side
	printf("==> moving backward 25 inches\n");
	moveBackward(23, NO_DEBUG);
	//move towards dropping poms
	printf("==> moving forward 3 inches\n");
	moveForward(3, NO_DEBUG);
	printf("==> moving righ angle bwd\n");
	rightAngleFwd(LEFT, NO_DEBUG);
	clawUp();
	printf("==> moving forward 14 inches til black line\n");
	moveForwardTilBlackLine(15, NO_DEBUG);
	//milestone 2
	moveBackward(13, NO_DEBUG);
	rightAngleBwd(LEFT, NO_DEBUG);
	moveBackward(8, NO_DEBUG);
	moveForward(8.5, NO_DEBUG);
	//get the cube now
	rightAngleFwd(RIGHT, NO_DEBUG);
	moveForward(35, NO_DEBUG);
	clawDownCube();
	rightAngleFwd(LEFT, NO_DEBUG);
	moveForward(1, NO_DEBUG);
	rightAngleFwd(RIGHT, NO_DEBUG);
	moveForward(13,NO_DEBUG);
	rightAngleFwd(LEFT, NO_DEBUG);
	moveForward(5, NO_DEBUG);
	clawUp();
	//Dropping off the cube
	moveBackward(1, NO_DEBUG);
	rightAngleBwd(RIGHT, NO_DEBUG);
	moveBackward(3, NO_DEBUG);
	moveForward(12, NO_DEBUG);
	rightAngleFwd(LEFT, NO_DEBUG);
	moveForward(5 ,NO_DEBUG);
	clawDown();
	printf("====> elapsed time: %f\n", (seconds() - start_time));
	ao();
	disable_servos();
	return 0;
}
void moveForward(double distanceInInches, int debug) {	
	moveForwardRoutine(distanceInInches, NO_CHECK_LIGHT_SENSOR, debug);
}
//moves forward without light sensor
void moveForwardTilBlackLine(double distanceInInches, int debug) {
	moveForwardRoutine(distanceInInches, CHECK_LIGHT_SENSOR, debug);
}
//moves forward with light sensor
void moveForwardRoutine(double distanceInInches, int checkLightSensor, int debug) {
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
		if (checkLightSensor == CHECK_LIGHT_SENSOR && analog(LIGHT_SENSOR) > 512) 			{
			if (debug == DEBUG) {
				printf("exiting because of light sensor");
			}
			break;
		}
		//first let's see if one motor is going ahead of the other
		differential = current_position_left - initial_position_left - 
				(current_position_right - initial_position_right);
			if (debug == DEBUG) {
				printf("sensor value: %d lightsensor %d \n", analog(LIGHT_SENSOR),checkLightSensor);
			}
		if (differential > -25 && differential < 25 ) {
		//counter are around the same 
			mav(RIGHT_MOTOR, SPEED_FWD);
			mav(LEFT_MOTOR, SPEED_FWD);
		} else if (differential < 0 ) {
		//right has moved ahead, let's slow down right until left catches up
			mav(RIGHT_MOTOR,(int) (SPEED_FWD*ADJUST_SPEED));
			mav(LEFT_MOTOR, SPEED_FWD);
			if (debug == DEBUG) {
				printf("adjusting LEFT L: %d R: %d\n", (current_position_left - 				initial_position_left), (current_position_right - initial_position_right));
			}
		} else {
		//left has moved ahead, let's slow down left until right catches up
			mav(RIGHT_MOTOR, SPEED_FWD);
			mav(LEFT_MOTOR, (int) (SPEED_FWD*ADJUST_SPEED));
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
void moveBackward(double distanceInInches,int debug) {
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
		mav(LEFT_MOTOR,SPEED_FWD);
	} else if (direction == LEFT) {
		mav(RIGHT_MOTOR, SPEED_FWD) ;
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
		current_position = get_motor_position_counter(LEFT_MOTOR);
	} else if (direction == LEFT) {
		mrp(RIGHT_MOTOR, SPEED_FWD, RIGHT_ANGLE_CLICKS_MRP_LEFT);
		bmd(RIGHT_MOTOR);
		current_position = get_motor_position_counter(RIGHT_MOTOR);
	}
		if (debug == DEBUG) {
			printf("right angle mrp fwd Init %d , curr %d, tgt %d\n", initial_position,current_position, RIGHT_ANGLE_CLICKS_MRP_RIGHT);
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
void fortyFiveAngleBwd(int direction, int debug) {
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
void reset_motors(){
	//resets the motor counters
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR,0);
	msleep(200);
}
