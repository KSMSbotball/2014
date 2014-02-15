// Created on Thu February 6 2014

#define LEFT_PORT_WHEEL 2
#define RIGHT_PORT_WHEEL 0

#define CRUISING_SPEED_FWD 500
#define CRUISING_SPEED_BWD -500
#define CRUISING_SPEED_TURNS 500

#define FORWARD 0 //directions 
#define RIGHT 1
#define LEFT 2
#define BACK 3

void Move_X_Inches(int Direction, double Centimeters);
void Right_Angle(int Direction);
	
int main()
{
	printf("Gos forward, makes turns, collects/pushes poms.\n");
	Move_X_Centimeters(FORWARD, 19);
	Move_X_Centimeters(BACK, 5);
	Right_Angle(RIGHT);
	Move_X_Centimeters(FORWARD, 13);
	Right_Angle(LEFT);
	Move_X_Centimeters(BACK, 12);
	Right_Angle(RIGHT);
	Move_X_Centimeters(FORWARD, 9);
	return 0;
}

//The direction functions accept a power as speed (int) and time as a double. the go in a certain direction at x speed for y seconds 

void Move_X_Inches(int Direction, int dist){ 
	long rightClicksStraight=156.251 * dist;
	long leftClicksStraight=rightClicks * 0.8;
	if(Direction==FORWARD){
		mrp(RIGHT_PORT_WHEEL, CRUISING_SPEED_FWD, rightClicks);
		mrp(LEFT_PORT_WHEEL, CRUISING_SPEED_FWD, leftClicks);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	if(Direction==BACK){
		mrp(RIGHT_PORT_WHEEL, CRUISING_SPEED_BWD, rightClicks);
		mrp(LEFT_PORT_WHEEL, CRUISING_SPEED_BWD, leftClicks);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
}

void Right_Angle(int Direction){
	long rightClicks=100;
	long leftClicks=100;
	if(Direction==RIGHT){
		mrp(RIGHT_PORT_WHEEL, -CRUISING_SPEED_TURNS, rightClicks);
		mrp(LEFT_PORT_WHEEL, CRUISING_SPEED_TURNS, leftClicks);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else if(Direction==LEFT){
		mrp(RIGHT_PORT_WHEEL, CRUISING_SPEED_TURNS, rightClicks);
		mrp(LEFT_PORT_WHEEL, -CRUISING_SPEED_TURNS, leftClicks);
		bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
}
