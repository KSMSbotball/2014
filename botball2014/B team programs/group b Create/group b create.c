// Created on Fri February 21 2014
void Forward(int inches);
int main(){
	printf("program started\n");
	int create_connect();
	printf("connected\n");
	msleep(1500);ccc
	Forward(10);
	printf("Progarm Over\n");
	create_disconnect();
return 0;
}
void Forward(int inches){
	create_drive_direct(250,250); 
	msleep(inches*0.0625);
} 


	
