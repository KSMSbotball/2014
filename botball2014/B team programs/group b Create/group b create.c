// Created on Fri February 21 2014
#define SPEED_FWD 250
#define SPEED_BWD -250
void forward(int inches);
void backwar(int inches);


int main(){
	printf("program started\n");
	create_connect();
	printf("connected\n");
	msleep(1500);
	forward(10);
	printf("Progarm Over\n");
	create_disconnect();
	return 0;
}
void forward(int inches){
	create_drive_straight(SPEED_FWD); 
	msleep(inches*0.0625);
	create_stop();
} 

void backward(int inches){
	create_drive_straight(SPEED_BWD); 
	msleep(inches*0.0625);
	create_stop();
} 

	
