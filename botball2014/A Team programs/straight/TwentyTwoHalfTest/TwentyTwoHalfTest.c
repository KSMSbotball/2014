// Created on Sun March 16 2014

#define LEFT_PORT_WHEEL 2
#define RIGHT_PORT_WHEEL 0

#define CRUISING_SPEED_TURNS 600

#define FORWARD 0 //directions 
#define RIGHT 1
#define LEFT 2
#define BACK 3

#define TIME_OUT 15

#define TICKS_PER_REVOLUTION_RIGHT 831

#define MSLEEP_VALUE 500

#define TICKS_PER_REVOLUTION_LEFT 825

#define CRUISING_SPEED_TURNS_RIGHT 500

#define CRUISING_SPEED_TURNS_LEFT 500*1.15

void Twenty_Two_Half_Degree_AngleMAV(int Direction, double timeLimit);
void Stop_Movement();
void Forty_Five_Degree_Angle(int Direction, double timeLimit);
void Twenty_Two_Half_Degree_Angle(int Direction, double timeLimit);

int main()
{	
	int i = 0;
	while (i<4){
		Forty_Five_Degree_Angle(LEFT, TIME_OUT);
		//Stop_Movement();
		msleep(MSLEEP_VALUE);
		i++;
	}
	
	return 0;
}


void Twenty_Two_Half_Degree_Angle(int Direction, double timeLimit){
	long rightClicksRight=0.41*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.39*TICKS_PER_REVOLUTION_LEFT;
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	double startTURN22Time = seconds();
	/*while((seconds() - startTURN22Time <= timeLimit) && ((get_motor_position_counter(LEFT_PORT_WHEEL) < leftClicksRight) && (get_motor_position_counter(LEFT_PORT_WHEEL) > -leftClicksRight))){*/
	if(Direction==RIGHT){
		
		//mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, -rightClicksRight);
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, leftClicksRight);
		//bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else if(Direction==LEFT){
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, rightClicksRight);
		//mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, -leftClicksRight);
		bmd(RIGHT_PORT_WHEEL);
		//bmd(LEFT_PORT_WHEEL);
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
	//}//Close while
}

void Forty_Five_Degree_Angle(int Direction, double timeLimit){
	long rightClicksRight=0.91*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.89*TICKS_PER_REVOLUTION_LEFT;
		
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	double startTURN45Time = seconds();
	//while((seconds() - startTURN45Time <= timeLimit) && (get_motor_position_counter(LEFT_PORT_WHEEL) < leftClicksRight) && (get_motor_position_counter(LEFT_PORT_WHEEL) > -leftClicksRight)){
	if(Direction==RIGHT){
		//mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, -rightClicksRight);
		mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, leftClicksRight);
		//bmd(RIGHT_PORT_WHEEL);
		bmd(LEFT_PORT_WHEEL);
	}
	else if(Direction==LEFT){
		mrp(RIGHT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_RIGHT, rightClicksRight);
		//mrp(LEFT_PORT_WHEEL, (int)CRUISING_SPEED_TURNS_LEFT, -leftClicksRight);
		bmd(RIGHT_PORT_WHEEL);
		//bmd(LEFT_PORT_WHEEL);
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
	//}//Close While
}

void Stop_Movement(){
	mav(RIGHT_PORT_WHEEL, 0);
	mav(LEFT_PORT_WHEEL, 0);
	ao();
}
