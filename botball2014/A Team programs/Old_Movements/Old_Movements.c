// Created on Fri March 14 2014

int main()
{
	printf("Hello, World!\n");
	return 0;
}
void Move_X_Millimeters(int Direction, float distMillimeters, double timeLimit){ 
	
	float rightClicksStraight = TICKS_PER_REVOLUTION_RIGHT*(distMillimeters/MILLIMETERS_PER_REVOLUTION);
	float leftClicksStraight = TICKS_PER_REVOLUTION_LEFT*(distMillimeters/MILLIMETERS_PER_REVOLUTION);
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	if(Direction==FORWARD){
		//printf("CRUISING_SPEED_FWD_LEFT is: %f:\n", CRUISING_SPEED_FWD_LEFT);
		double ticksDistance = TICKS_PER_REVOLUTION * (distMillimeters/MILLIMETERS_PER_REVOLUTION);
		
		clear_motor_position_counter(RIGHT_PORT_WHEEL);
		clear_motor_position_counter(LEFT_PORT_WHEEL);
		
		int motor_left_position_start = get_motor_position_counter(LEFT_PORT_WHEEL);
		int motor_right_position_start = get_motor_position_counter(RIGHT_PORT_WHEEL);
		
		double startFWDTime = seconds();
		
		while((get_motor_position_counter(LEFT_PORT_WHEEL) < (motor_left_position_start + ticksDistance)) 
			&& (seconds() - startFWDTime <= timeLimit)){
			
			int mvt_counter_left = get_motor_position_counter(LEFT_PORT_WHEEL)-motor_left_position_start;
			int mvt_counter_right = get_motor_position_counter(RIGHT_PORT_WHEEL)-motor_right_position_start;
			
			int wheel_difference = mvt_counter_right - mvt_counter_left;
			
			if(wheel_difference < CORRECTION_THRESHOLD && wheel_difference > -CORRECTION_THRESHOLD){//If both are within the same range, wheels are going straight
				mav(LEFT_PORT_WHEEL, CRUISING_SPEED_FWD);
				mav(RIGHT_PORT_WHEEL, CRUISING_SPEED_FWD);
				msleep(5);
				printf("STRAIGHT: left: %d right: %d diff: %d\n", mvt_counter_left, mvt_counter_right, wheel_difference);
			}
			else if(mvt_counter_right > mvt_counter_left){//right wheel is ahead of left wheel
				//mav(LEFT_PORT_WHEEL, 750);
				mav(RIGHT_PORT_WHEEL, CRUISING_SPEED_FWD * CORRECTION_REDUCTION); //correction speeed is 80% of fwd speed
				printf("RIGHT diff: %d\n", wheel_difference);
				msleep(35);
			}
			else if(mvt_counter_left > mvt_counter_right){//left wheel is ahead of right wheel
				mav(LEFT_PORT_WHEEL, CRUISING_SPEED_FWD * CORRECTION_REDUCTION); //correction speeed is 80% of fwd speed
				//mav(RIGHT_PORT_WHEEL, 750);
				printf("LEFT diff: %d\n", wheel_difference);
				msleep(35);
			}
			msleep(15);
		}	
		ao();
	}
	if(Direction==BACK){
		double ticksDistance = -TICKS_PER_REVOLUTION * (distMillimeters/MILLIMETERS_PER_REVOLUTION);
		
		clear_motor_position_counter(RIGHT_PORT_WHEEL);
		clear_motor_position_counter(LEFT_PORT_WHEEL);
		
		int motor_left_position_start = get_motor_position_counter(LEFT_PORT_WHEEL);
		int motor_right_position_start = get_motor_position_counter(RIGHT_PORT_WHEEL);
		
		double startBACKTime = seconds();
		while((get_motor_position_counter(LEFT_PORT_WHEEL) > (motor_left_position_start + ticksDistance))
			&& (seconds() - startBACKTime <= timeLimit)){
			
			printf("BACK\n");	
				
			int mvt_counter_left = get_motor_position_counter(LEFT_PORT_WHEEL)-motor_left_position_start;
			int mvt_counter_right = get_motor_position_counter(RIGHT_PORT_WHEEL)-motor_right_position_start;
			
			int wheel_difference = mvt_counter_right - mvt_counter_left;
			
			if(wheel_difference < CORRECTION_THRESHOLD && wheel_difference > -CORRECTION_THRESHOLD){//If both are within the same range, wheels are going straight
				mav(LEFT_PORT_WHEEL, CRUISING_SPEED_BWD);
				mav(RIGHT_PORT_WHEEL, CRUISING_SPEED_BWD);
				msleep(5);
				printf("left: %d right: %d diff: %d\n", mvt_counter_left, mvt_counter_right, wheel_difference);
			}
			else if(mvt_counter_right > mvt_counter_left){ //right wheel is ahead of left
				//mav(LEFT_PORT_WHEEL, 750);
				mav(LEFT_PORT_WHEEL, CRUISING_SPEED_BWD * CORRECTION_REDUCTION); //correction speed is 80% of BWD Speed
				printf("correcting right diff: %d\n", wheel_difference);
				msleep(35);
			}
			else if(mvt_counter_left > mvt_counter_right){// left wheel is ahead of right
				mav(RIGHT_PORT_WHEEL, CRUISING_SPEED_BWD * CORRECTION_REDUCTION); //correction speed is 80% of BWD Speed
				//mav(RIGHT_PORT_WHEEL, 750);
				printf("correcting left diff: %d\n", wheel_difference);
				msleep(35);
			}
			msleep(15);
		}	
		ao();
	}
}


void Twenty_Two_Half_Degree_Angle(int Direction, double timeLimit){
	long rightClicksRight=0.19*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.19*TICKS_PER_REVOLUTION_LEFT;
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	double startTURN22Time = seconds();
	/*while((seconds() - startTURN22Time <= timeLimit) && ((get_motor_position_counter(LEFT_PORT_WHEEL) < leftClicksRight) && (get_motor_position_counter(LEFT_PORT_WHEEL) > -leftClicksRight))){*/
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
	//}//Close while
}

void Forty_Five_Degree_Angle(int Direction, double timeLimit){
	long rightClicksRight=0.39*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.39*TICKS_PER_REVOLUTION_LEFT;
		
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	double startTURN45Time = seconds();
	//while((seconds() - startTURN45Time <= timeLimit) && (get_motor_position_counter(LEFT_PORT_WHEEL) < leftClicksRight) && (get_motor_position_counter(LEFT_PORT_WHEEL) > -leftClicksRight)){
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
	//}//Close While
}

void Right_Angle(int Direction, double timeLimit){
	long rightClicksRight=0.6*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.6*TICKS_PER_REVOLUTION_LEFT;
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);

	double startTURN90Time = seconds();
	//while((seconds() - startTURN90Time <= timeLimit) && (get_motor_position_counter(LEFT_PORT_WHEEL) < leftClicksRight) && (get_motor_position_counter(LEFT_PORT_WHEEL) > -leftClicksRight)){	
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
	//}//Close While
}

void Twenty_Two_Half_Degree_AngleMAV(int Direction, double timeLimit){
	long rightClicksRight=0.09*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.09*TICKS_PER_REVOLUTION_LEFT;
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	if(Direction==RIGHT){
		double startTURN22Time = seconds();
		while((seconds() - startTURN22Time <= timeLimit) && ((get_motor_position_counter(LEFT_PORT_WHEEL) < leftClicksRight) && (get_motor_position_counter(RIGHT_PORT_WHEEL) > -rightClicksRight))){
			
			mav(RIGHT_PORT_WHEEL, -CRUISING_SPEED_TURNS);
			mav(LEFT_PORT_WHEEL, CRUISING_SPEED_TURNS);
			msleep(100);
		
		}
	}
	else if(Direction==LEFT){
		double startTURN22Time = seconds();
		while((seconds() - startTURN22Time <= timeLimit) && ((get_motor_position_counter(RIGHT_PORT_WHEEL) < rightClicksRight) && (get_motor_position_counter(LEFT_PORT_WHEEL) > -leftClicksRight))){
			
			mav(RIGHT_PORT_WHEEL, CRUISING_SPEED_TURNS);
			mav(LEFT_PORT_WHEEL, -CRUISING_SPEED_TURNS);
			msleep(100);
		
		}
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
}

void Forty_Five_Degree_AngleMAV(int Direction, double timeLimit){
	long rightClicksRight=0.35*TICKS_PER_REVOLUTION_RIGHT; //39
	long leftClicksRight=0.35*TICKS_PER_REVOLUTION_LEFT;
		
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	if(Direction==RIGHT){
		double startTURN45Time = seconds();
		while((seconds() - startTURN45Time <= timeLimit) && ((get_motor_position_counter(LEFT_PORT_WHEEL) < leftClicksRight) && (get_motor_position_counter(RIGHT_PORT_WHEEL) > -rightClicksRight))){
			
			mav(RIGHT_PORT_WHEEL, -CRUISING_SPEED_TURNS);
			mav(LEFT_PORT_WHEEL, CRUISING_SPEED_TURNS);
			msleep(35);
		
		}
	}
	else if(Direction==LEFT){
		double startTURN45Time = seconds();
		while((seconds() - startTURN45Time <= timeLimit) && ((get_motor_position_counter(RIGHT_PORT_WHEEL) < rightClicksRight) && (get_motor_position_counter(LEFT_PORT_WHEEL) > -leftClicksRight))){
			
			mav(RIGHT_PORT_WHEEL, CRUISING_SPEED_TURNS);
			mav(LEFT_PORT_WHEEL, -CRUISING_SPEED_TURNS);
			msleep(35);
		
		}
	}
	else{
		printf("Invalid input. LEFT and RIGHT globals accepted only\n");
	}
}
void Right_AngleMAV(int Direction, double timeLimit){
	long rightClicksRight=0.6*TICKS_PER_REVOLUTION_RIGHT;
	long leftClicksRight=0.6*TICKS_PER_REVOLUTION_LEFT;
	
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);

	double startTURN90Time = seconds();
	while((seconds() - startTURN90Time <= timeLimit) && (get_motor_position_counter(LEFT_PORT_WHEEL) < leftClicksRight) && (get_motor_position_counter(LEFT_PORT_WHEEL) > -leftClicksRight)){	
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
	}//Close While
}
void boost(){
	mav(RIGHT_PORT_WHEEL, 2000);
	mav(LEFT_PORT_WHEEL, 2000);
	msleep(1000);
}
