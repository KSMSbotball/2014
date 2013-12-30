//optical wait
#define chan 0
#define motorL 0
#define motorR 2
#define ARM_SERVO    2
#define CLAW_SERVO  3
#define SPEED 40
#define ARM_UP_POS 1900
#define ARM_UP_HALFWAY_POS 1000
#define ARM_DOWN_POS 200
#define CLAW_OPEN_POS 2000
#define CLAW_CLOSE_POS 550

void leftF(float dur, int speed, int straight_speed);
void rightF(float dur, int speed, int straight_speed);
void stop(float dur);
void armUp();
void armUpHalfWay();
void armDown();
void clawOpen();
void clawClose();
void moveServo(int servo_port, int position);
int abs(int number);

int main(){
   armUp();
	clawOpen();
   camera_open(LOW_RES);
   double start_wait=seconds();
   while((seconds()-start_wait)<=25){//wait for poms or for 25 seconds
       int i=0;
       while(i<10){//picks latest image from the buffer
	   camera_update();
	   i++;
       }
       if(get_object_count(chan)>0){
           break;
       }else{
           stop(0.1);
       }
   }
   while((seconds()-start_wait)<=60){
	   int area=get_object_area(chan, 0);
	   if(area>=600){
		   int i=0;
		   while(i<10){
			   camera_update();
			   i++;
		   }
		   int x=get_object_center(chan, 0).x;
		   if(x<65){
			   rightF(0.1, 100, 80);
		   }else{
			   leftF(0.1, 100, 80);
		   }
       }else{
		   break;
	   }
   }
   armDown();
   clawClose();
   armUp();
   
}
void leftF(float dur, int speed, int straight_speed){
    motor(motorL, straight_speed);
    motor(motorR, speed);
    msleep(dur*1000);
}
void rightF(float dur, int speed, int straight_speed){
    motor(motorL, speed);
    motor(motorR, straight_speed);
    msleep(dur*1000);
}
void stop(float dur){
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
