// Created on Fri February 22 2013
#define motorL 0 //left motor
#define motorR 2 // right motor
#define ETport 2
#define RIport 1
#define low_left 20
#define low_forward_turning 10
#define low_right 20
#define down 2047
#define camport 0
#define chan 0//channel for orange.config

#define ARM_SERVO    2
#define CLAW_SERVO  3
#define SPEED 40
#define ARM_UP_POS 1900
#define ARM_UP_HALFWAY_POS 1000
#define ARM_DOWN_POS 200
#define CLAW_OPEN_POS 2000
#define CLAW_CLOSE_POS 300

void straight(float dur, int speed);
void left(float dur, int speed);
void right(float dur, int speed);
void back(float dur, int speed);
void leftF(float dur, int speedL, int speedF);
void rightF(float dur, int speedR, int speedF);
void transportPos(int forward_speed, int reverse_speed);
void rightC(float dur, int speed);
void leftC(float dur, int speed);
void stop(float dur);
void detect();
void armUp();
void armUpHalfWay();
void armDown();
void clawOpen();
void clawClose();
void moveServo(int servo_port, int position);
int abs(int number);
void navigate_poms(int loc);

int main()
{
	printf("version 1.9.5\n");
	shut_down_in(0.010*1000);
	int start=seconds();//starting time for two minutes
	enable_servo(0);
	set_servo_position(0,2047);
	straight(1.8,  170);//gets in front of transport
	rightC(0.28, 100);
	leftC(0.28, -100);
	straight(1.65, 170);
	leftC(0.44, 100);
	printf("completed first dead reckoning\n");
	set_analog_pullup(ETport,  0);
	
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
	back(0.25, -50);//backs  up from wall to deposit transport
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
	
	back(0.25, -100);
	leftC(0.46, 100);
	
	camera_open(LOW_RES);
	
	armUp();
	clawOpen();
   double start_wait=seconds();
   while((seconds()-start_wait)<=25){//wait for poms or for 25 seconds
       int i=0;
       while(i<10){//picks latest image from the buffer
	   camera_update();
	   i++;
       }
       if(get_object_count(chan)>0){//if camera sees objects, skip the 25 seconds and go onto picking up stuff
           break;
       }else{//if camera doesn't see any objects, keep waiting until 25 seconds is up
           stop(0.1);
       }
   }
   int x=get_object_center(chan, 0).x;//declares global unchanging variable for the x location of the largest object
   while((seconds()-start)<=120){//while there is still time left
	   int area=get_object_area(chan, 0);//creates local changing variable. this is th area of the largest object camera sees
	   if(area<=600){//if the object is small enough(far enough), navigate towards object. 600 is threshold
		   int i=0;
		   while(i<10){//buffer updating
			   camera_update();
			   i++;
		   }
		  
		   navigate_poms(x);//similar to line followig function; gets to poms.
		 
      
	   }
	   
	   armDown();
	   clawClose();
	   armUp();
	   
	   /*
	   leftF(0.5, 100, 80);//turn and go forward until transport is contacted
	   while(digital(8)==0){
	   straight(0.1, 100);*/
   
   }

   

	/*
	back(1.5, 100);
	leftC(0.44, 100);
	
	while(digital(8)==0 && digital(9)==1){
		straight(0.1, 100);
		msleep(10);
			if(digital(9)==0){
				rightF(0.1, 100, 40);
				left(0.1, 100);
				msleep(10);
			}
	}
	straight(2, 200);
	rightC(0.44, 100);
	straight(1, 80);
	rightC(0.92, 100);
	while(analog10(ETport<=600)){
			msleep(10);
	}
	msleep(10000);
	straight(1, 80);
	leftC(0.44, 100);
	straight(2, 200);
	*/
	
	return 0;
}
void straight(float dur, int speed){
	motor(motorL, speed);
	motor(motorR, speed);
	msleep(dur*1000);
}
void left(float dur, int speed){
	motor(motorL, 0);
	motor(motorR, speed);
	msleep(dur*1000);
}
void right(float dur, int speed){
	motor(motorL, speed);
	motor(motorR, 0);
    msleep(dur*1000);
}
void back(float dur, int speed){
	motor(motorL, speed);
	motor(motorR, speed);
	msleep(dur*1000);
}
void leftF(float dur, int speedL, int speedF){
	motor(motorL, speedF);
	motor(motorR, speedL);
	msleep(dur*1000);
}

void rightF(float dur, int speedR, int speedF){
	motor(motorL, speedR);
	motor(motorR, speedF);
	msleep(dur*1000);
}
void transportPos(int forward_speed, int reverse_speed){
	straight(1800, forward_speed);
	printf("forward\n");
	back(1800, reverse_speed);
	printf("back\n");
}
void rightC(float dur, int speed){
	motor(motorL, speed);
	motor(motorR, (0-speed));
	msleep(dur*1000);
}
void leftC(float dur, int speed){
	motor(motorL, (0-speed));
	motor(motorR, speed);
	msleep(dur*1000);
}

void stop(float dur){
	printf("waiting\n");
	motor(motorL, 0);
	motor(motorR, 0);
	msleep(dur*1000);
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
void navigate_poms(int loc){//function for getting to poms
	  if(loc<65){
			   rightF(0.1, 100, 80);
		   }else{
			   leftF(0.1, 100, 80);
		   }
}
