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
#define CLAW_CLOSE_POS 550

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
void right_angle2(int dir);

int main()
{
	//wait_for_light(1);//initialization
	printf("version 1.9.5\n");
	shut_down_in(115);
	
	
	int servo_counter=0;
	while(servo_counter<=3){
		enable_servo(servo_counter);
		servo_counter++;
	}
	//	initialize routine
	set_servo_position(0,2047);
	armUp();
	clawClose();
	//get in front of transport

	straight(1.8,  170);
	rightC(0.28, 100);
	leftC(0.28, -100);
	straight(1.65, 170);
	leftC(0.44, 100);
	printf("completed first dead reckoning\n");
	
	
	//until distance is 5 centimeter
	/*
	int claw_threshold = 13;
	while(analog10(ETport)>claw_threshold){
		back(0.1, -10);
		msleep(1000);
		printf("move once\n");
		printf("%i\n", analog10(ETport));
	}*/
	back(0.25, -20);//pushes against transport
	msleep(2000);
	set_servo_position(0, 500);//puts claw on transport
	msleep(1000);
	printf("done with attaching to transport\n");
	while(digital(8)==0)//goes forward with transport until it hits the wall
	{
		straight(0.1, 100);
		msleep(10);
	}
	printf("at wall\n");
	back(0.15, -50);//backs  up from wall to deposit transport
	set_servo_position(0, 2047);//raises claw
	msleep(1500);
	while(digital(8)==0){//goes forward until it hits wall for second time
		straight(0.1, 100);
		msleep(10);
	}
	
	printf("at wall 2\n");
	
	back(0.35, -100);//goes back and turns left in order to be oriented with left inner wall
	leftC(0.6, 142);
	
	int bump_counter=0;	
	
	while(digital(8)==0){//hits side wall
		straight(0.1, 100);
		msleep(10);
	}
	
	bump_counter++;//has one bump


    int i=0;
    while(i<10){//if hits side wall, pause
		stop(0.2);
		i++;
	}
	
	/*
	==========================
	==========End of routine 1======
	KIPR at the wall
	==========================
	*/
	// Pause here to wait for Create to drop POMS
	
	msleep(1*1000);
	//
	int start=seconds();//  start time
	
	printf("will get out of corner\n");
	
	back(0.5, -100);
	
	while(seconds()-start<=3){//separates back from right angle
		stop(0.1);
	}
	
	right_angle(left);
	
	while(seconds()-start<=5){//separates right angle from straight
		stop(0.1);
	}
	
	double start_drive=seconds();
	
	straight(0.7, 100);//go to poms
	
	
	stop(0.5);
	
	camera_open(LOW_RES);
	
	
	
	/*while(seconds()-start<=20){
		int update_counter=0;
		while(update_counter<10){
			camera_update();
			update_counter++;
		}
		if(get_object_count(chan)==0){
			stop(0.1);
		}
		int x=get_object_center(chan, 0).x;
		int area=get_object_area(chan, 0);	
		if(area<=400){
			navigate(x);
		}
		if(area>=800){
			//if objects are clumped are clumped, area will be automatically larger.
			//this means that KIPR will start earlier than it should. We counter this here
			//straight(0.18, 100);
			straight(0.1, 100);
			break;
		}
	
	}*/
	
	stop(0.1);
	
	printf("object seen\n");

	double end_drive=seconds();//only for simulation. real end and start times would have to be taken from whole routine
	//pick up POMS that are right there
	pickup();
	int offset=(end_drive-start_drive)*(3.0/4.0);;//half of distance from back of launch area to border of launch area
	back((end_drive-start_drive)+1.5,  -100);//go to the back of wall plus a little more to straighten out
	printf("at back wall\n");
	straight(2.0, 100);//goes halway between border and back of launch area
	right_angle(left);//faces transport
	int starpof=seconds();//time after right angle
	while(seconds()-starpof<=2){
		motor(motorL, 0);
		motor(motorR, 0);
	}
	while(digital(8)==0){
		straight(0.1, 100);
	}
	straight(0.1, 100);
	
	printf("touching transport\n");
	
	motor(motorL, 0);
	motor(motorR, 0);
	
	dropoff();//drops poms in launch area
	
	printf("poms in transport\n");
	
	back(0.25, -100);
	int starfop=seconds();
	while(seconds()-starfop<=2){
		motor(motorL, 0);
		motor(motorR, 0);
	}
	int turns=1;
	while(turns<=2){
		right_angle(right);
		stop(0.3);
		turns++;
	}
	

	
	
	/*
	======================
	======Part 2 of routine 2====
	======================
	*/
	while(1){

		stop(0.5);//
		
		while(digital(8)==0){
			straight(0.1, 100);
		}
		back(0.3, -100);
		right_angle(left);
		pickup();
		back((end_drive-start_drive)+1.5, -100);
		straight(2.2, 100);
		right_angle(left);
		while(digital(8)==0){
			straight(0.1, 100);
		}
		dropoff();
		back(0.5, -100);
		right_angle(left);
		right_angle(left);
	}
	
	
	/*while(1){
	
		start=0;
		while(digital(8)==0){
			straight(0.1, 80);
        }
		back(0.5, -100);
		right_angle(right);
		straight(0.5, 100);
		right_angle(right);
		right_angle(right);
		
		while(seconds()-start<=20){
			int update_counter=0;
			while(update_counter<10){
				camera_update();
				update_counter++;
			}
			if(get_object_count(chan)==0){
				stop(0.1);
			}
			int x=get_object_center(chan, 0).x;
			int area=get_object_area(chan, 0);	
			if(area<=400){
				navigate(x);
			}
			if(area>=800){
				//if objects are clumped are clumped, area will be automatically larger.
				//this means that KIPR will start earlier than it should. We counter this here
				//straight(0.18, 100);
				straight(0.1, 100);
				break;
			}
		}
		int servo_counter=1;
	while(servo_counter<=3){
		enable_servo(servo_counter);
		printf("servo %d enabled\n", servo_counter);
		servo_counter++;
	}
	pickup();
	int offset=(end_drive-start_drive)*(3.0/4.0);;//half of distance from back of launch area to border of launch area
	back((end_drive-start_drive)+1.5,  -100);//go to the back of wall plus a little more to straighten out
	printf("at back wall\n");
	straight(1.8, 100);//goes halway between border and back of launch area
	right_angle(left);//faces transport
	int starpof=seconds();//time after right angle
	while(seconds()-starpof<=2){
		motor(motorL, 0);
		motor(motorR, 0);
	}
	while(digital(8)==0){
		straight(0.1, 100);
	}
	straight(0.1, 100);
	
	printf("touching transport\n");
	
	motor(motorL, 0);
	motor(motorR, 0);
	
	dropoff();//drops poms in launch area
	
	printf("poms in transport\n");
	
	back(0.25, -100);
	int starfop=seconds();
	while(seconds()-starfop<=2){
		motor(motorL, 0);
		motor(motorR, 0);
	}
	int turns=1;
	while(turns<=2){
		right_angle(right);
		turns++;
	}
		
	
		repeat_runs++;
		
    }*/
	
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
		right_angle2(left);//face poms
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
		right_angle2(left);//turn to face transport
		stop(0.1);
		while(digital(TOUCH_SENSOR)==0){//go forward until transport contacted
			straight(0.1, 100);
		}
		stop(0.1);
		dropoff();//drop poms off
		stop(0.1);
		back(0.5, -100);//back up from transpor
		stop(0.1);
		right_angle2(right);//orient for next iteration
		stop(0.1);
		right_angle2(right);
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
		rightC(0.53,120);
	}else{
		leftC(0.53, 120);
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
void right_angle2(int dir){
	if(dir==right){
		stop(0.1);
		rightC(0.57,120);
	}else{
		stop(0.1);
		leftC(0.60, 120);
	}
}
