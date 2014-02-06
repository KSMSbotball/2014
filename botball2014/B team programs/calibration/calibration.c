#define LEFT_MOTOR_FORWARD 50
#define RIGHT_MOTOR_FORWARD 50
#define PORT_LEFT 0
#define PORT_RIGHT 2
void forward(int time);
int main()
{
	forward(3);
	while (a_button() == 0){
		msleep(50);
	}
	forward(10);
	while (a_button() == 0){
		msleep(50);
	}
	forward(15);
	return 0;
}
void forward(int time){
	motor(PORT_LEFT,LEFT_MOTOR_FORWARD);
	motor(PORT_RIGHT,RIGHT_MOTOR_FORWARD);
	msleep(time * 1000);
}
