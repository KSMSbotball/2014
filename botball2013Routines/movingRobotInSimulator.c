// Created on Fri January 25 2013

int main()
{
	
	printf("Hello, World!\n");
	int motor8 = 
	while (digital(8) == 0 && digital (9) == 0)  {
		motor(2,50);
		motor(0,50);
		
		int d8 = digital(8);
		int d9 = digital(9);
		printf("digital 8 :");
		printf("%i",d8);
		printf(" digital 9 : ");
		printf("%i",d9);
		
	}
	//if bumpig on the right back up left
	if (digital(8) != 0) {
		printf("\n\nbacking up right!");
		motor(0,-25);
		motor(2,-25);
		msleep(5000);
	}
	//if bumping on the left back up right
	if (digital(9) != 0) {
		printf("\n\nbacling up left!");
		motor(2, -50);
		motor(0,-25);
		msleep(10000);
	}

	ao(); //stop motor
	printf("the robot is now stopping");

	return 0;
}
