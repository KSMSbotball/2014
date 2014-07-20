#define LEFT_PORT_WHEEL 2
#define RIGHT_PORT_WHEEL 0

#define TICKS_PER_REVOLUTION_RIGHT 780 //Determined through testing
#define TICKS_PER_REVOLUTION_LEFT 825  //Determined through testing
#define MILLIMETERS_PER_REVOLUTION 130 //Wheel Diameter in mm

#define CORRECTION_THRESHOLD 5 //mm before correction applied
#define CORRECTION_REDUCTION .5 //percentage 

void MoveForwardMillimeters(int mmToGo, int Speed)
{ 
	//Calculate the number of ticks to go
	float RightTicksToGo = TICKS_PER_REVOLUTION_RIGHT*(mmToGo/MILLIMETERS_PER_REVOLUTION);
	float LeftTicksToGo = TICKS_PER_REVOLUTION_LEFT*(mmToGo/MILLIMETERS_PER_REVOLUTION);
	
	//Calculate mm per tick
	float RightTicksPerMM = TICKS_PER_REVOLUTION_RIGHT/MILLIMETERS_PER_REVOLUTION;
	float LeftTicksPerMM = TICKS_PER_REVOLUTION_LEFT/MILLIMETERS_PER_REVOLUTION;
	
	//Set Motor Ticks position to zero
	clear_motor_position_counter(LEFT_PORT_WHEEL);
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	
	//Set Motor Positions to a variable .. should be zero here because we just cleared them
	int LeftMotorStartPosition = get_motor_position_counter(LEFT_PORT_WHEEL);
	int RightMotorStartPosition = get_motor_position_counter(RIGHT_PORT_WHEEL);
	
	//Calculate Motor Final Tick Position for MTP Command
	int LeftMotorFinalPosition = LeftMotorStartPosition + LeftTicksToGo;
	int RightMotorFinalPosition = RightMotorStartPosition + RightTicksToGo;
	
	
	//Get time of start movement
	//Not used yet.. for timeout functionality
	double StartMovementTime = seconds();
		
	//Loop until movment complete as measured by the left wheel
	while(get_motor_position_counter(LEFT_PORT_WHEEL) < LeftMotorFinalPosition) 
	{
		//Calculate Wheel Distance Moved each loop
		int LeftDistanceMoved = (get_motor_position_counter(LEFT_PORT_WHEEL)-LeftMotorStartPosition)/LeftTicksPerMM;
		int RightDistanceMoved = (get_motor_position_counter(RIGHT_PORT_WHEEL)-RightMotorStartPosition)/RightTicksPerMM;
		
		//Calculate Wheel Split
		//Positive Values Right Wheel is Ahead, Negative Values Left Wheel is ahead
		int WheelSplit = RightDistanceMoved - LeftDistanceMoved;
		
		//See if Wheel Split is exceeding the Correction Threshhold in either direction
		if(WheelSplit < CORRECTION_THRESHOLD && WheelSplit > -CORRECTION_THRESHOLD)
		{
			//Wheels are going straight
			motor(RIGHT_PORT_WHEEL, 100);
			motor(LEFT_PORT_WHEEL, 100);
			
			//move_to_position(RIGHT_PORT_WHEEL, Speed, RightMotorFinalPosition);
			//move_to_position(LEFT_PORT_WHEEL, Speed, LeftMotorFinalPosition);
			printf("STRAIGHT: left: %d right: %d split: %d\n", LeftDistanceMoved, RightDistanceMoved, WheelSplit);
		}
		else if(WheelSplit >= CORRECTION_THRESHOLD)
		{
			//Right wheel is ahead of left wheel
			//correction reduction applied to right wheel
			
			motor(RIGHT_PORT_WHEEL, 100*CORRECTION_REDUCTION);
			motor(LEFT_PORT_WHEEL, 100);
			
			//move_to_position(RIGHT_PORT_WHEEL, Speed * CORRECTION_REDUCTION, RightMotorFinalPosition);
			//move_to_position(LEFT_PORT_WHEEL, Speed, LeftMotorFinalPosition);
			printf("CORRECT RIGHT\n");
		}
		else if(WheelSplit <= -CORRECTION_THRESHOLD)
		{
			//Left wheel is ahead of right wheel
			//correction reduction applied to left wheel
			
			motor(RIGHT_PORT_WHEEL, 100);
			motor(LEFT_PORT_WHEEL, 100*CORRECTION_REDUCTION);
			//move_to_position(RIGHT_PORT_WHEEL, Speed, RightMotorFinalPosition);
			//move_to_position(LEFT_PORT_WHEEL, Speed * CORRECTION_REDUCTION, LeftMotorFinalPosition);
			printf("CORRECT LEFT\n");
		}
		msleep(150);
	}
	//Turn All Motors Off 
	ao();
}

