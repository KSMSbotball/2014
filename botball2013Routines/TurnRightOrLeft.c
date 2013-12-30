// Created on Fri January 25 2013
void turn_left(double seconds);
void go_straight(double seconds);
void turn_right(double seconds);
void stop();
	
	
int main()
{
	set_a_button_text("turn left");
	set_c_button_text("turn right");
	set_b_button_text("go straight");
	printf ("go stright out for 5 seconds first");
	motor(0,50);
	motor(2,50);
	msleep(5000);
	int message = 0;
	double start = seconds();
	while (seconds() - start < 20) {
		if (a_button_clicked() == 0 ) {
			turn_left(1);
		}
		if (c_button() == 1 ) {
			turn_right(1);
		}
		go_straight(1);
		if (b_button()==1) {
			go_straight(1);
		}
		stop();
		msleep(5000);
		if (seconds() - start < 5 && message == 0) {
			printf("this is he 5 seconds warning");
			message = 1;
		}
	}
	
	printf("End of the long road Cowboy\n");
	return 0;
}

void turn_left (double seconds) {
	motor(0,10);
	motor(2,50);
	msleep(seconds*1000);
	
}

void stop() {
	printf("stop");
	motor(0,0);
	motor(2,0);
}

void go_straight (double seconds) {
	motor(0,50);
	motor(2,50);
	msleep(seconds*1000);
}


void turn_right(double seconds) {
	motor(0,50);
	motor(2,10);
	msleep(seconds*1000);

	}
