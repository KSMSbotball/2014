// Created on Thu February 6 2014

#define LEFT_PORT_WHEEL 2
#define RIGHT_PORT_WHEEL 0

#define CRUISING_SPEED_FWD 350
#define CRUISING_SPEED_BWD -350
#define CRUISING_SPEED_TURNS 250
#define CRUISING_SPEED_ONE_WHEEL_90_DEGREE 1400

#define FORWARD 0 //directions 
#define RIGHT 1
#define LEFT 2
#define BACK 3

void Move_X_Inches(int Direction, int dist);
void Right_Angle(int Direction);
void Complete_90_Degree_Angle(int Direction, int CurrentTicks);
void Stop_Movement();
void Forty_Five_Degree_Angle(int Direction);
void Twenty_Two_Half_Degree_Angle(int Direction);
	
int main()
{	
	Move_X_Inches(FORWARD, 27);
	Stop_Movement();
	msleep(1000);
	
	Forty_Five_Degree_Angle(RIGHT);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Inches(FORWARD, 6);
	Stop_Movement();
	msleep(1000);
	
	Twenty_Two_Half_Degree_Angle(RIGHT);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Inches(FORWARD, 3);
	Stop_Movement();
	msleep(1000);
	
	Twenty_Two_Half_Degree_Angle(RIGHT);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Inches(FORWARD, 7); //Into the bucket
	Stop_Movement();
	msleep(1000);
	
	Move_X_Inches(BACK, 15);
	Stop_Movement();
	msleep(1000);
	
	Right_Angle(RIGHT);
	Stop_Movement();
	msleep(1000);
	
	Move_X_Inches(BACK, 7);
	Stop_Movement();
	msleep(1000);

	return 0;
}

//The direction functions accept a power as speed (int) and time as a double. the go in a certain direction at x speed for y seconds 

void Move_X_Inches(int Direction, int dist){ 
	
	long rightClicksStraight=124 * dist;
	long leftClicksStraight=rightClicksStraight;
	
	if(Direction==FORWARD){
		mrp(LEFT_PORT_WHEEL, CRUISING_SPEED_FWD, rightClicksStraight);
		mrp(RIGHT_PORT_WHEEL, CRUISING_SPEED_FWD, leftClicksStraight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	if(Direction==BACK){
		mrp(RIGHT_PORT_WHEEL, CRUISING_SPEED_BWD, -rightClicksStraight);
		mrp(LEFT_PORT_WHEEL, CRUISING_SPEED_BWD, -leftClicksStraight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
}

void Twenty_Two_Half_Degree_Angle(int Direction){
	long rightClicksRight=125;
	long leftClicksRight=125;
	//long rightClicksLeft=515;
	//long leftClicksLeft=515;
	if(Direction==RIGHT){
		mrp(RIGHT_PORT_WHEEL, CRUISING_SPEED_TURNS, -rightClicksRight);
		mrp(LEFT_PORT_WHEEL, CRUISING_SPEED_TURNS, leftClicksRight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else if(Direction==LEFT){
		mrp(RIGHT_PORT_WHEEL, CRUISING_SPEED_TURNS, rightClicksRight+25);
		mrp(LEFT_PORT_WHEEL, CRUISING_SPEED_TURNS, -leftClicksRight-25);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
}

void Forty_Five_Degree_Angle(int Direction){
	long rightClicksRight=250;
	long leftClicksRight=250;
	//long rightClicksLeft=515;
	//long leftClicksLeft=515;
	if(Direction==RIGHT){
		mrp(RIGHT_PORT_WHEEL, CRUISING_SPEED_TURNS, -rightClicksRight);
		mrp(LEFT_PORT_WHEEL, CRUISING_SPEED_TURNS, leftClicksRight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else if(Direction==LEFT){
		mrp(RIGHT_PORT_WHEEL, CRUISING_SPEED_TURNS, rightClicksRight+25);
		mrp(LEFT_PORT_WHEEL, CRUISING_SPEED_TURNS, -leftClicksRight-25);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
}

void Right_Angle(int Direction){
	long rightClicksRight=500;
	long leftClicksRight=500;
	//long rightClicksLeft=515;
	//long leftClicksLeft=515;
	if(Direction==RIGHT){
		mrp(RIGHT_PORT_WHEEL, CRUISING_SPEED_TURNS, -rightClicksRight);
		mrp(LEFT_PORT_WHEEL, CRUISING_SPEED_TURNS, leftClicksRight);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else if(Direction==LEFT){
		mrp(RIGHT_PORT_WHEEL, CRUISING_SPEED_TURNS, rightClicksRight+25);
		mrp(LEFT_PORT_WHEEL, CRUISING_SPEED_TURNS, -leftClicksRight-25);
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
	Move_X_Inches(FORWARD, 17);
	Stop_Movement();
	msleep(1000);
	/*
	Complete_90_Degree_Angle(RIGHT, PreviousTicks1);
	Stop_Movement();
	msleep(1000);
	Right_Angle(RIGHT);
	Stop_Movement();
	msleep(1000);
	long PreviousTicks2 = Move_X_Inches(FORWARD, 13);
	Stop_Movement();
	msleep(1000);
	Complete_90_Degree_Angle(RIGHT, PreviousTicks2);
	Stop_Movement();
	msleep(1000);
	Right_Angle(LEFT);/*
	Move_X_Inches(BACK, 12);
	Right_Angle(RIGHT);
	Move_X_Inches(FORWARD, 9);*/

