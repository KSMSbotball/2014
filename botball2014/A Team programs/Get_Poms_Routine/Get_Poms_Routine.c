// Created on Thu February 6 2014

#define LEFT_PORT_WHEEL 2
#define RIGHT_PORT_WHEEL 0

#define CRUISING_SPEED_FWD_RIGHT 2000
//#define CRUISING_SPEED_FWD_LEFT 2000*1.42
#define CRUISING_SPEED_FWD_LEFT 2000*1.15

#define CRUISING_SPEED_BWD_RIGHT 500
#define CRUISING_SPEED_BWD_LEFT 500*1.15

#define CRUISING_SPEED_TURNS_RIGHT 500//500
#define CRUISING_SPEED_TURNS_LEFT 500*1.15

//#define TICKS_PER_REVOLUTION_RIGHT 829
//#define TICKS_PER_REVOLUTION_LEFT 833
#define TICKS_PER_REVOLUTION_RIGHT 831
#define TICKS_PER_REVOLUTION_LEFT 825
#define CRUISING_SPEED_TURNS 250
#define MILLIMETERS_PER_REVOLUTION 173

#define FORWARD 0 //directions 
#define RIGHT 1
#define LEFT 2
#define BACK 3

void Move_X_Millimeters(int Direction, float distMillimeters);
void Right_Angle(int Direction);
void Stop_Movement();
void Forty_Five_Degree_Angle(int Direction);
void Twenty_Two_Half_Degree_Angle(int Direction);
	
int main()
{	
	//To help reduce unpredictability
	set_pid_gains(2, 30, 0 , -30, (70*1.75), 0, (70*1.75));
	set_pid_gains(0, 30, 0 , -30, (70*1.75), 0, (70*1.75));
	//set_pid_gains(2, 30, 0 , -30, 70, 0, 51);
	//set_pid_gains(0, 30, 0 , -30, 70, 0, 51);
	
	double startTime = seconds();
	printf("StartTime: %f:\n", startTime);
	printf("Seconds: %f:\n", seconds());
	printf("Seconds: %f:\n", seconds()-startTime);
	/*while(seconds() - startTime <= 3.0){		
		
	}*/
	
	/*
	Move_X_Millimeters(FORWARD, 700);
	Stop_Movement();
	msleep(1000);
	*/
	
	Move_X_Millimeters(FORWARD, 100);
	Stop_Movement();
	msleep(1000);

	Move_X_Millimeters(FORWARD, 100);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Millimeters(FORWARD, 100);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Millimeters(FORWARD, 100);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Millimeters(FORWARD, 100);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Millimeters(FORWARD, 100);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Millimeters(FORWARD, 100);
	Stop_Movement();
	msleep(1000);
	/*
	Move_X_Millimeters(FORWARD, 150);
	Stop_Movement();
	msleep(1000);
	*/
	
	Forty_Five_Degree_Angle(RIGHT);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Millimeters(FORWARD, 120);
	Stop_Movement();
	msleep(1000);
	
	Twenty_Two_Half_Degree_Angle(RIGHT);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Millimeters(FORWARD, 80);
	Stop_Movement();
	msleep(1000);
	
	Twenty_Two_Half_Degree_Angle(RIGHT);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Millimeters(FORWARD, 180); //Into the bucket
	Stop_Movement();
	msleep(1000);
	
	Move_X_Millimeters(BACK, 381);
	Stop_Movement();
	msleep(1000);
	
	Right_Angle(RIGHT);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Millimeters(BACK, 50);
	Stop_Movement();
	msleep(1000);


	return 0;
}

//The direction functions accept a power as speed (int) and time as a double. the go in a certain direction at x speed for y seconds 

void Move_X_Millimeters(int Direction, float distMillimeters){ 
	
	float rightClicksStraight = TICKS_PER_REVOLUTION_RIGHT*(distMillimeters/MILLIMETERS_PER_REVOLUTION);
	float leftClicksStraight = TICKS_PER_REVOLUTION_LEFT*(distMillimeters/MILLIMETERS_PER_REVOLUTION);
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	if(Direction==FORWARD){
		//printf("CRUISING_SPEED_FWD_LEFT is: %f:\n", CRUISING_SPEED_FWD_LEFT);
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_FWD_LEFT, (int)rightClicksStraight);
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_FWD_RIGHT, (int)leftClicksStraight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	if(Direction==BACK){
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_BWD_RIGHT, -rightClicksStraight);
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_BWD_LEFT, -leftClicksStraight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
}

void Twenty_Two_Half_Degree_Angle(int Direction){
	long rightClicksRight=0.16*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.16*TICKS_PER_REVOLUTION_LEFT;
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	if(Direction==RIGHT){
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, -rightClicksRight);
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, leftClicksRight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else if(Direction==LEFT){
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, rightClicksRight);
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, -leftClicksRight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
}

void Forty_Five_Degree_Angle(int Direction){
	long rightClicksRight=0.35*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.35*TICKS_PER_REVOLUTION_LEFT;
		
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	if(Direction==RIGHT){
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, -rightClicksRight);
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, leftClicksRight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else if(Direction==LEFT){
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, rightClicksRight);
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, -leftClicksRight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
}

void Right_Angle(int Direction){
	long rightClicksRight=0.6*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.6*TICKS_PER_REVOLUTION_LEFT;
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);

	if(Direction==RIGHT){
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, -rightClicksRight);
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, leftClicksRight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else if(Direction==LEFT){
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, rightClicksRight);
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, -leftClicksRight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
}

void Stop_Movement(){
	motor(RIGHT_PORT_WHEEL, 0);
	motor(LEFT_PORT_WHEEL, 0);
}

/*
=======================Old Code========================
/*
	printf("Goes forward, makes turns, collects/pushes poms.\n");
	Move_X_Millimeters(FORWARD, 17);
	Stop_Movement();
	msleep(1000);
	/*
	Complete_90_Degree_Angle(RIGHT, PreviousTicks1);
	Stop_Movement();
	msleep(1000);
	Right_Angle(RIGHT);
	Stop_Movement();
	msleep(1000);
	long PreviousTicks2 = Move_X_Millimeters(FORWARD, 13);
	Stop_Movement();
	msleep(1000);
	Complete_90_Degree_Angle(RIGHT, PreviousTicks2);
	Stop_Movement();
	msleep(1000);
	Right_Angle(LEFT);/*
	Move_X_Millimeters(BACK, 12);
	Right_Angle(RIGHT);
	Move_X_Millimeters(FORWARD, 9);*/

