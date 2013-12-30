// Created on Fri March 29 2013
/* 1) definition : #define 
define motor right and left
debug flag: on the program will be in debug mode and will spew out info when it runs
					off: the program will run quietly without littering the console
*/
#define DEBUG_ON 



#define MOTOR_RIGHT 2 
#define MOTOR_LEFT 0

#define SPEED_RIGHT 12
#define SPEED_LEFT 16

#define SPEED_BACK_RIGHT -8
#define SPEED_BACK_LEFT -21

#define SLOW_SPEED 20
#define MEDIUM_SPEED 50
#define FULL_SPEED 100

#ifdef DEBUG_ON
#define DEBUG ( printf ("debug statement on line %i\n",__LINE__))
#else
#define DEBUG 
#endif

/* 2) declarations or function signatures
*/
void forward(int inches);
void forwardTest(int leftMotorSpeed, int rightMotorSpeed, int time);
void backwardTest(int leftMotorSpeed, int rightMotorSpeed, int time);
void backward(int inches);
void rightAngLeftFwd();
void rightAngRightFwd();
void rightAngLeftBwd();
void rightAngRightBwd();
void move(int leftSpeed, int rightSpeed, int time);
int abs(int val) ;
//int floor(int val) ;

/*3) main this is the body of the program the program begins with main and end at the end of main (or the shutdow in)
*/
//11.7 for 10
//23.4 for 20
int main()
{
	printf("Hello, World!\n");

	backward(5);
	rightAngLeftBwd();
	backward(5);
	foward(5);
	rightAngLeftFwd();
	forward(5);
	
	rightAngRightBwd();
	forward(5);
	rightAngRightBwd();
	forward(5);
	rightAngRightBwd();
	forward(5);
	rightAngRightBwd();
	forward(5);

	msleep(10000);

	forward(5);
	rightAngRightBwd();
	forward(5);
	
	
	int left = 17; 
	int right =12;
	int time = 1700;
	printf(" 5in test c : left %d, right %d, time %d \n", left, right, time);
	backwardTest(SPEED_BACK_LEFT, SPEED_BACK_RIGHT,time);
	msleep(5*1000);
	
	time = 3060;
	printf(" 10in test : left %d, right %d, time %d \n", left, right, time);
	//forward(10);
	backwardTest(SPEED_BACK_LEFT, SPEED_BACK_RIGHT,time);
	msleep(5*1000);

	time = 5940;
	printf(" 20in test : left %d, right %d, time %d \n", left, right, time);
	//forward(20);
	backwardTest(SPEED_BACK_LEFT, SPEED_BACK_RIGHT,time);
	msleep(5*1000);

	//	msleep(10*1000);
//	forward(20, FULL_SPEED);
//	msleep(10*1000);
//  forward(20, MEDIUM_SPEED);

	return 0;
}

void forwardTest(int leftMotorSpeed, int rightMotorSpeed, int time) {
	motor(MOTOR_LEFT, leftMotorSpeed);
	motor(MOTOR_RIGHT,rightMotorSpeed);
	msleep(time);
	motor(MOTOR_LEFT,0);
	motor(MOTOR_RIGHT,0);
	
}
void backwardTest(int leftMotorSpeed, int rightMotorSpeed, int time) {
	motor(MOTOR_LEFT, leftMotorSpeed);
	motor(MOTOR_RIGHT,rightMotorSpeed);
	msleep(time);
	motor(MOTOR_LEFT,0);
	motor(MOTOR_RIGHT,0);
	
}


/* 4) function bodies: all the funtions that are used to provide logic or repeated processing to the main function
*/
//this function will move KIPR forward  for the number of inches and at the speed indicated
// !!!!! this function will only work with the three speeds defined above, 
// attempts of using other speed will be met with disapproval, contempt and erratic results
//
void forward(int inches) {
	//calculate the amount time necessary to achieve the results
	int time = 0;
	
	time = 180 + inches * 288;
	move(SPEED_LEFT ,SPEED_RIGHT, time);
	printf("speeds left %d right %d, time %d\n " ,SPEED_LEFT, SPEED_RIGHT, time);	
}

//this function will move KIPR backwards similar to the forward but the other direction

void backward(int inches) {
	//calculate the amount time necessary to achieve the results
	int time = 180 + inches * 288;
	move(SPEED_BACK_LEFT ,SPEED_BACK_RIGHT, time);
	printf("speeds backwarks left %d right %d, time %d\n " ,SPEED_BACK_LEFT, SPEED_BACK_RIGHT, time);
}


void rightAngLeftFwd() {
	move(0, SPEED_RIGHT, 3100);
	printf("sright angle turn left. right %d, time %d\n " ,SPEED_RIGHT, 3100);
}


void rightAngRightFwd() {
	//reset wheels forwards
	move (SPEED_LEFT,SPEED_RIGHT, 100);
	move(SPEED_LEFT,0, 3550);
	printf("sright angle turn right. left %d, time %d\n " ,SPEED_LEFT, 3550);

}


void rightAngLeftBwd() {
	//reset wheels backwards
	move (SPEED_BACK_LEFT,SPEED_BACK_RIGHT, 100);
	move(SPEED_BACK_LEFT,0, 3900);
	printf("sright angle turn back left. right %d, time %d\n " ,SPEED_RIGHT, 3550);
}


void rightAngRightBwd() {
	//reset wheels backwards
	move (SPEED_BACK_LEFT,SPEED_BACK_RIGHT, 100);
	move( 0, SPEED_BACK_RIGHT, 3700);
	printf("sright angle turn back right. right %d, time %d\n " ,SPEED_RIGHT, 3550);
}

void move(int leftSpeed, int rightSpeed, int time) {
	//generic moving routine
	motor(MOTOR_LEFT, leftSpeed);
	motor(MOTOR_RIGHT, rightSpeed );
	msleep(time);
	motor(MOTOR_LEFT,0);
	motor(MOTOR_RIGHT,0);

}
//returns the absolute value of a number
int abs(int val) {
	if (val < 0) {
		return val * -1;
	}
	return val;
}
