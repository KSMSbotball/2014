// Created on Fri March 15 2013

#define chan 0
#define chan2 1
#define motorL 0
#define motorR 2
#define motorL 0
#define motorR 2
#define left -1
#define right 1
#define ARM_SERVO    2
#define CLAW_SERVO  3
#define SPEED 40
#define ARM_UP_POS 1900
#define ARM_UP_HALFWAY_POS 700
#define ARM_DOWN_POS 200
#define CLAW_OPEN_POS 2047
#define CLAW_CLOSE_POS 500
#define TOUCH_SENSOR 8

void leftF(float dur, int speedL, int speedF);
void rightF(float dur, int speedR, int speedF);
void get_to_poms();
void stop(float dur);
void navigate(int x_loc);
void back (float dur, int speed);
void rightC (float dur, int speed);
void leftC (float dur, int speed);
void right_angle(int dir);
void straight (float dur, int speed);
void armUp();
void armUpHalfWay();
void armDown();
void clawOpen();
void clawClose();
void moveServo(int servo_port, int position);
int abs(int number);
void pickup();
void dropoff();

int main()
{
	
	while(1){
		
		int servo_counter=0;//enables servos
		while(servo_counter<=3){
			enable_servo(servo_counter);
			servo_counter++;
		}
		armUp();//raises arm at start

		stop(0.5);
		
		while(digital(TOUCH_SENSOR)==0){//go forward until left wall is contacted
			straight(0.1, 100);
		}
		stop(0.1);
		back(0.3, -100);//back up
		stop(0.1);
		right_angle(left);//face poms
		stop(0.1);
		back(3+1.5, -100);//back up to rocket wall to straighten out
		stop(0.1);
		straight(3+1.5, 100);//go to poms
		stop(0.1);
		pickup();//pick poms up
		stop(0.1);
		back(3+1.5, -100);// back up until rocket wall
		stop(0.1);
		straight(2.2, 100);//go forward
		stop(0.1);
		right_angle(left);//turn to face transport
		stop(0.1);
		while(digital(TOUCH_SENSOR)==0){//go forward until transport contacted
			straight(0.1, 100);
		}
		stop(0.1);
		dropoff();//drop poms off
		stop(0.1);
		back(0.5, -100);//back up from transpor
		stop(0.1);
		right_angle(right);//orient for next iteration
		stop(0.1);
		right_angle(right);
	}
	
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
void back (float dur, int speed){
	motor(motorL, speed);
	motor(motorR, speed);
	msleep(dur*1000);
}

void straight (float dur, int speed){
	motor(motorL, speed);
	motor(motorR, speed);
	msleep(dur*1000);
}

void rightC (float dur, int speed){
	motor(motorL, speed);
	motor(motorR, (0-speed));
	msleep(dur*1000);
}

void leftC (float dur, int speed){
	motor(motorL, (0-speed));
	motor(motorR, speed);
	msleep(dur*1000);
}

void right_angle(int dir){
	if(dir==right){
		stop(0.1);
		rightC(0.57,120);
	}else{
		stop(0.1);
		leftC(0.60, 120);
	}
}

void pickup(){
	clawOpen();
	armDown();
	clawClose();
	armUpHalfWay();
}

void dropoff(){
	
	clawOpen();
	armUp();
	clawClose();
}
void stop(float dur){
	motor(motorL, 0);
	motor(motorR, 0);
	msleep(dur*1000);
}
void leftF(float dur, int speedL, int speedF){//for going left forward
	motor(motorL, speedF);
	motor(motorR, speedL);
	msleep(dur*1000);
}

void rightF(float dur, int speedR, int speedF){//for going right forward
	motor(motorL, speedR);
	motor(motorR, speedF);
	msleep(dur*1000);
}
void navigate(int x_loc){
	if(x_loc>79){
		rightF(0.1, 100, 80);
	}else{
		leftF(0.1, 100, 80);
	}
}
