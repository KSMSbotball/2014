// Created on Sat March 2 2013
/* This program assumes that the servo for the claw 
     needs to be calibrated to 0 and the claw mounted closed when the servo is at 300
	 or change the values below to reflect a different calibration
	 
	*/


#define ARM_SERVO    2
#define CLAW_SERVO  3
#define SPEED 40
#define ARM_UP_POS 1900
#define ARM_UP_HALFWAY_POS 1000
#define ARM_DOWN_POS 200
#define CLAW_OPEN_POS 2000
#define CLAW_CLOSE_POS 300

void armUp();
void armUpHalfWay();
void armDown();
void clawOpen();
void clawClose();
void moveServo(int servo_port, int position);
int abs(int number);

int main()
{
	enable_servos();

	printf("moving arm up\n");
	armUp();
	msleep(1000);

	printf("open claw\n");
	clawOpen();
	msleep(1000);
	


	printf("moving arm down\n");
	armDown();
	msleep(1000);

	
	printf("claw close\n");
	clawClose();
	msleep(1000);
	
	printf("moving arm up\n");
	armUpHalfWay();
	msleep(1000);
	
	printf("open claw\n");
	clawOpen();
	msleep(1000);
	
	printf("claw close\n");
	clawClose();
	msleep(1000);
	
	printf("arm up\n");
	armUp();
	msleep(1000);
	printf("we are now done\n");

	disable_servos();
	return 0;
}

//this function will bring the arm up (regardless of the claw position)
void armUp() {
	
	printf("moving arm up\n");
	moveServo(ARM_SERVO, ARM_UP_POS);
	
}

//this function will bring the arm up (regardless of the claw position)
void armUpHalfWay() {
	printf("moving arm up 1/2 way\n");
	moveServo(ARM_SERVO, ARM_UP_HALFWAY_POS);
	
}

//this function will bring the arm up (regardless of the claw position)
void armDown() {
	printf("moving arm down");
	moveServo(ARM_SERVO, ARM_DOWN_POS);
	
}

//this function will bring the arm up (regardless of the claw position)
void clawOpen() {
	printf("claw open");
	moveServo(CLAW_SERVO, CLAW_OPEN_POS);
	
}

//this function will bring the arm up (regardless of the claw position)
void clawClose() {
	printf("claw close");
	moveServo(CLAW_SERVO, CLAW_CLOSE_POS);
	
}

//define the absolute value
int abs(int number){
	if(number<0){
		return number*-1;
	} 
		return number;
}


//generic servo move function
void moveServo(int servo_port, int end_position) {
	int position = end_position;
	int currentPosition = get_servo_position(servo_port);
	int movement = SPEED;
	//set the movement of the servo first based on where the servo is and where it intends to go
	if (currentPosition > end_position) {
		movement = SPEED * -1;
	}

	//printf("starting position : %i end of position %i , speed %i.\n",currentPosition, end_position, movement);
	//create a loop that will smoothly move the servos to the desired position
	do {
		if (abs(currentPosition - position) > SPEED) {
			
			//printf("current position %i end position %i.\n" , currentPosition,end_position);
			set_servo_position(servo_port, (get_servo_position(servo_port) + movement));
		} else {
			//if we are close enough to the final position let's just go there
			printf("in the else current position %i end position %i.\n" , currentPosition,end_position);
			set_servo_position(servo_port, position);
		}
		msleep(50);
		//printf ("current and target %d and %d mvt %d\n", position, currentPosition,movement);

		currentPosition = get_servo_position(servo_port);
		if (currentPosition > 2100) {
			currentPosition = 0;
		}
	//since the values on servos are not continuous we have to be ok we are some close enough
	} while (abs(currentPosition - position) > SPEED);
	//printf("exiting the moveArm\n"); 
}
