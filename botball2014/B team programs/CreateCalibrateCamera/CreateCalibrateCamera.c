// Created on Thu March 13 2014
//CreateCalibrateCamera: this program is designed to help with calibration 
//before running the entire program. It will help adjust for minute variations.
//
//Cube position (x coordinate), change when calibrating channel if needed
//see program camera calibration routine
#define POS_7 6
#define POS_6 20
#define POS_5 55
#define POS_4 90
#define POS_3 122
#define POS_2 147
#define POS_1 170




#define RIGHT_ANG_LEFT 1990
#define RIGHT_ANG_RIGHT 1990
#define FORWARD_CONSTANT 100
#define BACKWARD_CONSTANT 95

#define HALF_CIRCLE 3800
#define SPEED_FWD 250
#define SPEED_BWD -250
#define CHANNELS 1
#define DEBUG 100
#define NO_DEBUG 51
#define A 0

#define RIGHT 2
#define LEFT 3
//function stubs

void forward(int inches);
void backward(int inches);
void rightAngle(int direction);
void turnCreate(int time);
void calibrateCamera();
int getShelfPlacement(int xLocation); 




int main()
{
	printf("beginning camera calibration pgm\n");
	create_connect();
	enable_servos();
	camera_open(LOW_RES);
	printf("1.0 after initialization\n");


	//place create for camera recognition of cube positions
	forward(9);
	rightAngle(LEFT);
	forward(15);
	rightAngle(RIGHT);

	calibrateCamera();
	
	printf("the end...\n");
	camera_close();
	create_disconnect();
	return 0;
	
	
}

//routine to use the camera and see blob position based on standard create start routine
void calibrateCamera() {
	int channel = 0;
	while (a_button_clicked() == 0) {
		msleep(2000);
		camera_update();
		printf ("=> object count %d \n", get_object_count(channel));
		int i = 0; 
		int shelfPlaces[8] = {0,0,0,0,0,0,0,0};
		while (i < get_object_count(channel)) {
			printf("obj %d, ctr loc, area, shelf plcmt: %d, %d, %d\n", i, get_object_center(channel, i).x, get_object_area(channel, i), 
			getShelfPlacement(get_object_center(channel, i).x));
			shelfPlaces[getShelfPlacement(get_object_center(channel, i).x)] += get_object_area(channel, i);
			i++;
		}
		printf("==========================\n");
		printf("=RESULTS                 =\n");
		printf("==========================\n");
		i = 1; 
		while (i < 8) {
			printf ("shelfPlace : %d, total cube area : %d\n", i, shelfPlaces[i]);
			i++;
		}
		printf("==========================\n");
		printf("click b button for new camera capture, a to exit.\n");
		while (b_button_clicked() == 0 && a_button_clicked() == 0 )  {
			msleep(25); 
		}
	}
	printf("done with calibration function.\n");
	
}

//return the shelf placement based on predefined values
int getShelfPlacement(int xLocation) {
	if (xLocation > (int) ((POS_1 + POS_2) /2) ) {
		return 1; 
	} 
	if (xLocation > (int) ((POS_2 + POS_3) /2) ) {
		return 2; 
	} 
	if (xLocation > (int) ((POS_3 + POS_4) /2) ) {
		return 3; 
	} 
	if (xLocation > (int) ((POS_4 + POS_5) /2) ) {
		return 4; 
	} 
	if (xLocation > (int) ((POS_5 + POS_6) /2) ) {
		return 5; 
	} 
	if (xLocation > (int) ((POS_6 + POS_7) /2) ) {
		return 6; 
	} 
	return 7;
}
//generic right angle turn in place
void rightAngle (int direction){
	
	if (direction == RIGHT) { 
		//then well turn 90 deg to the RIGHT
		create_spin_CW(100);
		msleep(RIGHT_ANG_RIGHT);
	} else if (direction == LEFT) {
		//then well turn 90 deg to the LEFT
		create_spin_CCW(100);
		msleep(RIGHT_ANG_LEFT);
	} else {
		printf("sorry I don't understand what you want me to do... ignoring right angle turn command\n");
	}
	create_stop();
}




//generic move forward function calibrated in inches
void forward (int inches){
	create_drive_straight(SPEED_FWD);
	
	int time_conversion = inches * FORWARD_CONSTANT;
	msleep(time_conversion);
	create_stop();
}
	
//generic move backward function calibrated in inches
void backward (int inches){
	create_drive_straight(SPEED_BWD);
	
	int time_conversion = inches * BACKWARD_CONSTANT;
	msleep(time_conversion);
	create_stop();
}
	
