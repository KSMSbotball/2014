// Created on Sun February 2 2014
#define SPEED_LEFT 50
#define SPEED_RIGHT 50
#define SPEED_LEFT_TURN 50
#define SPEED_RIGHT_TURN 50
void forward(int seconds);
void left(int seconds);
void right(int seconds);
int main()
{
	printf("start\n");
	forward(3);
	printf("done with 3 seconds\n");
	while (a_button() == 0) {
		msleep(50);
	}
	forward(5);
	printf("done with 5 seconds\n");
	while (a_button() == 0) {
		msleep(50);
	}
	forward(15);
	printf("done with 15 secs\n");
	left(3);
	while (a_button() == 0){
		msleep(50);
	}
	right(3);
	return 0;
}
void forward(int seconds){
	motor(0,SPEED_LEFT);
	motor(2,SPEED_RIGHT);
	msleep(seconds * 1000);
}
void left(int seconds){
	forward(3);
	motor(0,SPEED_LEFT_TURN);
	msleep(seconds * 1000);
	forward(3);
}
void right(int seconds){
	forward(3);
	motor(0,SPEED_RIGHT_TURN);
	msleep(seconds * 1000);
	forward(3);
}
