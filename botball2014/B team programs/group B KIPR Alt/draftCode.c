/* 
replace the current rightAngleFwd and rightAnglrBwd with the code below
it should work with the current program (the one that i didn't put on gtihub although I thought I did)
you need to define 3 new #define:
	a #define RIGHT_ANGLE_CLICKS_MRP 1300
	a #define RIGHT_ANGLE_CLICKS_BACK_MRP -1300
	an #define MRP 0
	a #define MAV 1
	and a MRP_OR_MAV and set it to 0 or 1 depending on whether you want to run MAV or MRP
	it is kinda confusing but it should allow us to easily switch and run a few tests and make a final decision on what direction to go . 
*/

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

	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);

	msleep(100);
	int clickNbrTarget = RIGHT_ANGLE_CLICKS_LEFT;
	int initial_position = get_motor_position_counter(RIGHT_MOTOR);

	if (direction == RIGHT) {
		clikNbrTarget = RIGHT_ANGLE_CLICKS_RIGHT;
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

	msleep(100);

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
		mrp(LEFT_MOTOR, SPEED_FWD, RIGHT_ANGLE_CLICKS_MRP);
		bmd(LEFT_MOTOR);
		current_position = get_motor_position_counter(LEFT_MOTOR);
	} else if (direction == LEFT) {
		mrp(RIGHT_MOTOR, SPEED_FWD, RIGHT_ANGLE_CLICKS_MRP);
		bmd(RIGHT_MOTOR);
		current_position = get_motor_position_counter(RIGHT_MOTOR);
	}
	
		if (debug == DEBUG) {
			printf("right angle mrp fwd Init %d , curr %d, tgt %d\n", initial_position,current_position, RIGHT_ANGLE_CLICKS_MRP);
	}

	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);

	msleep(100);

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
		clikNbrTarget = RIGHT_ANGLE_CLICKS_BACK;
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
			printf("right angle fwd Init %d , curr %d, tgt %d\n", initial_position,current_position , clickNbrTarget );
		}

	} 
	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);

	msleep(100);

}

//right angle turn function
void rightAngleBwdMrp(int direction, int debug ) {

	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);

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
			printf("right angle mrp fwd Init %d , curr %d, tgt %d\n", initial_position,current_position, RIGHT_ANGLE_CLICKS_BACK_MRP);
	}

	mav(RIGHT_MOTOR, 0);
	mav(LEFT_MOTOR, 0);

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
	msleep(250);

}
