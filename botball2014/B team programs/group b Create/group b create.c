// Created on Fri February 21 2014
void Forward(int inches);
int main(){
	printf("program started\n");
	int create_connect();
	printf("connected\n");
	msleep(1500);
	Forward(10);
	create_disconnect();
return 0;
}
void Forward(int inches){
	create_drive_straight(400);
	msleep(inches*0.0625);
}

