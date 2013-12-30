// Created on Sat February 16 2013
//Dead reckoning calibration program
#define SPEED 20
#define TIME_LENGTH 100


void moveForward(int speed, int time);
void stopBot();


int main()
{
	printf("Robot starting now\n");
	printf("moving forward at speed %i for %i time",SPEED, TIME_LENGTH);
	moveForward(SPEED, TIME_LENGTH);
	stopBot();
	printf("all done!");
	return 0;
}

void moveForward(int speed, int time) {
	motor(0, speed);
	motor(2, speed);
	msleep(time);
	
	
}

void stopBot() {
	motor(0, 0);
	motor(2,0);
}
