// Created on Sun February 2 2014
#define SPEED_LEFT 50
#define SPEED_RIGHT 50
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2
void left(double seconds);
void right(double seconds);
int main()
{
	left(3);
	while (a_button() == 0){
		msleep(50);
	}
	motor(RIGHT_MOTOR,SPEED_RIGHT);
	return 0;
}
void left(double seconds){
	motor(LEFT_MOTOR,50);
	motor(RIGHT_MOTOR,50);
	msleep(3000);
	motor(LEFT_MOTOR,SPEED_LEFT);
	msleep(seconds * 1000);
	motor(LEFT_MOTOR,50);
	motor(RIGHT_MOTOR,50);
	msleep(3000);
}
void right(double seconds){
	motor(LEFT_MOTOR,50);
	motor(RIGHT_MOTOR,50);
	msleep(3000);
	motor(RIGHT_MOTOR,SPEED_RIGHT);
	msleep(seconds * 1000);
	motor(LEFT_MOTOR,50);
	motor(RIGHT_MOTOR,50);
	msleep(3000);
}
