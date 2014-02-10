// Created on Sun February 2 2014
#define SPEED_LEFT 50
#define SPEED_RIGHT 50
void left(double seconds);
void right(double seconds);
int main()
{
	left(3);
	while (a_button() == 0){
		msleep(50);
	}
	motor(2,SPEED_RIGHT);
	return 0;
}
void left(double seconds){
	motor(0,50);
	motor(2,50);
	msleep(3000);
	motor(0,SPEED_LEFT);
	msleep(seconds * 1000);
	motor(0,50);
	motor(2,50);
	msleep(3000);
}
void right(double seconds){
	motor(0,50);
	motor(2,50);
	msleep(3000);
	motor(0,SPEED_RIGHT);
	msleep(seconds * 1000);
	motor(0,50);
	motor(2,50);
	msleep(3000);
}
