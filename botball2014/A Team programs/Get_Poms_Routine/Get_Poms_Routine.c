// Created on Thu February 6 2014

#define LEFT_PORT_WHEEL 2
#define RIGHT_PORT_WHEEL 0

#define CRUISING_SPEED_BWD_RIGHT 500
#define CRUISING_SPEED_BWD_LEFT 500*1.15

#define CRUISING_SPEED_TURNS_RIGHT 500//500
#define CRUISING_SPEED_TURNS_LEFT 500*1.15

#define CRUISING_SPEED_FWD 750
#define CRUSING_SPEED_FWD_FAST 1000
#define CRUISING_SPEED_BWD -750
#define CRUISING_SPEED_BWD_FAST -1000
#define CRUISING_SPEED_TURNS 600

#define TICKS_PER_REVOLUTION_RIGHT 831
#define TICKS_PER_REVOLUTION_LEFT 825
#define MILLIMETERS_PER_REVOLUTION 130

#define TICKS_PER_REVOLUTION 825
#define CORRECTION_THRESHOLD 10
#define CORRECTION_REDUCTION .90

#define MSLEEP_VALUE 250

#define FORWARD 0 //directions 
#define RIGHT 1
#define LEFT 2
#define BACK 3
#define FAST 1
#define SLOW 0
#define FWD 1

#define TIME_OUT 15

void Right_Angle(int Direction, double timeLimit);
void Stop_Movement();
void Forty_Five_Degree_Angle(int Forward_Back, int Direction, double timeLimit);
void Twenty_Two_Half_Degree_Angle(int Forward_Back, int Direction, double timeLimit);
void Move_X_Millimeters(int Direction, float distMillimeters, int Speed, double timeLimit);
void Twenty_Two_Half_Degree_AngleMAV(int Direction, double timeLimit);
void Forty_Five_Degree_AngleMAV(int Direction, double timeLimit);
void boost();
void First_Poms();
void Move_Blue_Cube();
void Second_Poms();

	
int main()
{	
	/*
	Twenty_Two_Half_Degree_Angle(FORWARD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Twenty_Two_Half_Degree_Angle(FORWARD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Twenty_Two_Half_Degree_Angle(FORWARD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Twenty_Two_Half_Degree_Angle(FORWARD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Twenty_Two_Half_Degree_Angle(FORWARD, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Twenty_Two_Half_Degree_Angle(FORWARD, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Twenty_Two_Half_Degree_Angle(FORWARD, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Twenty_Two_Half_Degree_Angle(FORWARD, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);*/
	
	
	//wait_for_light(1);
	shut_down_in(117);
	Stop_Movement();
	
//	Second_Poms();
	
	/*
	First_Poms();
	
	//Calibrate prior to blue cube run
	Move_X_Millimeters(BACK, 620, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);	
	
	Forty_Five_Degree_Angle(BACK, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(BACK, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(BACK, 300, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	//End Calibrate prior to blue cube
	
	Move_Blue_Cube();
	
	//Calibrate prior to second poms
	
	Move_X_Millimeters(BACK, 75, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(BACK, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);

	Forty_Five_Degree_Angle(BACK, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Twenty_Two_Half_Degree_Angle(BACK, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(BACK, 690, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 100, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(BACK, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(BACK, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(BACK, 300, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	//Go Get Poms2*/
	
	Second_Poms();
	
	return 0;
}

//The direction functions accept a power as speed (int) and time as a double. the go in a certain direction at x speed for y seconds 

void Stop_Movement(){
	mav(RIGHT_PORT_WHEEL, 0);
	mav(LEFT_PORT_WHEEL, 0);
	//ao();
}

void First_Poms(){
	/*
	Move_X_Millimeters(BACK, 10, FAST, TIME_OUT);
	Stop_Movement();
	msleep(4*MSLEEP_VALUE);*/
	
	Move_X_Millimeters(FORWARD, 650, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(FWD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 80, SLOW, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);	
	
	Twenty_Two_Half_Degree_Angle(FWD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 70, SLOW, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Twenty_Two_Half_Degree_Angle(FWD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	/*
	Twenty_Two_Half_Degree_Angle(FWD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	*/
	
	Move_X_Millimeters(FORWARD, 110, SLOW, TIME_OUT); //Into the bucket
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
}

void Move_Blue_Cube() {
	
	Move_X_Millimeters(FORWARD, 200, SLOW, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(FWD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(FWD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 590, FAST, TIME_OUT);//straight run for blue thing
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Twenty_Two_Half_Degree_Angle(FWD, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 150, SLOW, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
		
	Twenty_Two_Half_Degree_Angle(FWD, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 150, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(FWD, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 50, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	/*
	Twenty_Two_Half_Degree_Angle(FWD, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	*/
	
	Move_X_Millimeters(FORWARD, 390, FAST, TIME_OUT); //cube on tape
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
}

void Second_Poms() {
	
	Move_X_Millimeters(FORWARD, 300, SLOW, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(FWD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 300, SLOW, TIME_OUT); //250
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(FWD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 700, FAST, TIME_OUT);
	
	Move_X_Millimeters(FORWARD, 620, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(BACK, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 30, SLOW, TIME_OUT); //BACK
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(BACK, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 600, SLOW, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(BACK, 30, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(FORWARD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(FORWARD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	/*
	Forty_Five_Degree_Angle(FORWARD, RIGHT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(BACK, 40, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	
	Forty_Five_Degree_Angle(FORWARD, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);*/
	
	Move_X_Millimeters(FORWARD, 340, FAST, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);
	/*
	
	Twenty_Two_Half_Degree_Angle(FWD, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	
	Move_X_Millimeters(FORWARD, 10, SLOW, TIME_OUT);
	Stop_Movement();
	msleep(MSLEEP_VALUE);*/
	
	/*
	Twenty_Two_Half_Degree_Angle(FWD, LEFT, TIME_OUT);
	msleep(MSLEEP_VALUE);
	*/
	
		
}

void Move_X_Millimeters(int Direction, float distMillimeters, int SetSpeed, double timeLimit){ 
	
	float rightClicksStraight = TICKS_PER_REVOLUTION_RIGHT*(distMillimeters/MILLIMETERS_PER_REVOLUTION);
	float leftClicksStraight = TICKS_PER_REVOLUTION_LEFT*(distMillimeters/MILLIMETERS_PER_REVOLUTION);
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	

		
	if(Direction==FORWARD){
			//Set Speed
		int Speed = 0;
		if(SetSpeed == FAST)
			Speed = CRUSING_SPEED_FWD_FAST;
		else
			Speed = CRUISING_SPEED_FWD;
	
		//printf("CRUISING_SPEED_FWD_LEFT is: %f:\n", CRUISING_SPEED_FWD_LEFT);
		double ticksDistance = TICKS_PER_REVOLUTION * (distMillimeters/MILLIMETERS_PER_REVOLUTION);
		
		clear_motor_position_counter(RIGHT_PORT_WHEEL);
		clear_motor_position_counter(LEFT_PORT_WHEEL);
		
		int motor_left_position_start = get_motor_position_counter(LEFT_PORT_WHEEL);
		int motor_right_position_start = get_motor_position_counter(RIGHT_PORT_WHEEL);
		
		double startFWDTime = seconds();
		
		while((get_motor_position_counter(LEFT_PORT_WHEEL)*0.975 < (motor_left_position_start*0.975 + ticksDistance)) 
			&& (seconds() - startFWDTime <= timeLimit)){
			
			int mvt_counter_left = get_motor_position_counter(LEFT_PORT_WHEEL)-motor_left_position_start;
			int mvt_counter_right = get_motor_position_counter(RIGHT_PORT_WHEEL)-motor_right_position_start;
			
			int wheel_difference = mvt_counter_right*1.02 - mvt_counter_left*0.975;
			
			if(wheel_difference < CORRECTION_THRESHOLD && wheel_difference > -CORRECTION_THRESHOLD){//If both are within the same range, wheels are going straight
				mav(RIGHT_PORT_WHEEL, Speed);
				mav(LEFT_PORT_WHEEL, Speed);
				msleep(5);
				printf("STRAIGHT: left: %d right: %d diff: %d\n", mvt_counter_left, mvt_counter_right, wheel_difference);
			}
			else if(mvt_counter_right*1.02 > mvt_counter_left*0.975){//right wheel is ahead of left wheel
				mav(RIGHT_PORT_WHEEL, Speed * CORRECTION_REDUCTION); //correction speeed is 80% of fwd speed
				printf("RIGHT diff: %d\n", wheel_difference);
				msleep(5);
			}
			else if(mvt_counter_left*0.975 > mvt_counter_right*1.02){//left wheel is ahead of right wheel
				mav(LEFT_PORT_WHEEL, Speed * CORRECTION_REDUCTION); //correction speeed is 80% of fwd speed
				printf("LEFT diff: %d\n", wheel_difference);
				msleep(5);
			}
			msleep(15);
		}	
		ao();
	}
	if(Direction==BACK){
		//Set Speed
		int Speed = 0;
		if(SetSpeed == FAST)
			Speed = CRUISING_SPEED_BWD_FAST;
		else
			Speed = CRUISING_SPEED_BWD;
		
		double ticksDistance = -TICKS_PER_REVOLUTION * (distMillimeters/MILLIMETERS_PER_REVOLUTION);
		
		clear_motor_position_counter(RIGHT_PORT_WHEEL);
		clear_motor_position_counter(LEFT_PORT_WHEEL);
		
		int motor_left_position_start = get_motor_position_counter(LEFT_PORT_WHEEL);
		int motor_right_position_start = get_motor_position_counter(RIGHT_PORT_WHEEL);
		
		double startBACKTime = seconds();
		while((get_motor_position_counter(LEFT_PORT_WHEEL) > (motor_left_position_start + ticksDistance))
			&& (seconds() - startBACKTime <= timeLimit)){
			
			//printf("BACK\n");	
				
			int mvt_counter_left = get_motor_position_counter(LEFT_PORT_WHEEL)-motor_left_position_start;
			int mvt_counter_right = get_motor_position_counter(RIGHT_PORT_WHEEL)-motor_right_position_start;
			
			int wheel_difference = mvt_counter_right - mvt_counter_left;
			
			if(wheel_difference < CORRECTION_THRESHOLD && wheel_difference > -CORRECTION_THRESHOLD){//If both are within the same range, wheels are going straight
				mav(LEFT_PORT_WHEEL, Speed);
				mav(RIGHT_PORT_WHEEL, Speed);
				msleep(5);
				//printf("left: %d right: %d diff: %d\n", mvt_counter_left, mvt_counter_right, wheel_difference);
			}
			else if(mvt_counter_right > mvt_counter_left){ //right wheel is ahead of left
				mav(LEFT_PORT_WHEEL, Speed * CORRECTION_REDUCTION); //correction speed is 80% of BWD Speed
				//printf("correcting right diff: %d\n", wheel_difference);
				msleep(35);
			}
			else if(mvt_counter_left > mvt_counter_right){// left wheel is ahead of right
				mav(RIGHT_PORT_WHEEL, Speed * CORRECTION_REDUCTION); //correction speed is 80% of BWD Speed
				//printf("correcting left diff: %d\n", wheel_difference);
				msleep(35);
			}
			msleep(15);
		}	
		ao();
	}
}

void Twenty_Two_Half_Degree_Angle(int Forward_Back, int Direction, double timeLimit){
	long rightClicksRight=0.42*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.44*TICKS_PER_REVOLUTION_LEFT;
	
	if (Forward_Back == BACK){
		rightClicksRight = -rightClicksRight;
		leftClicksRight = -leftClicksRight;
	}
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	double startTURN22Time = seconds();
	if(Direction==RIGHT){
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, leftClicksRight);
		bmd(LEFT_PORT_WHEEL);
	}
	else if(Direction==LEFT){
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, rightClicksRight);
		bmd(RIGHT_PORT_WHEEL);
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
}

void Forty_Five_Degree_Angle(int Forward_Back, int Direction, double timeLimit){
	long rightClicksRight=0.9*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.93*TICKS_PER_REVOLUTION_LEFT;
	
	if (Forward_Back == BACK){
		rightClicksRight = -rightClicksRight;
		leftClicksRight = -leftClicksRight;
	}
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	double startTURN45Time = seconds();
	if(Direction==RIGHT){
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, leftClicksRight);
		bmd(LEFT_PORT_WHEEL);
	}
	else if(Direction==LEFT){
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, rightClicksRight);
		bmd(RIGHT_PORT_WHEEL);
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
}
