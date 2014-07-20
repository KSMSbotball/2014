#include "KiprMovement.h"
//Definitions Go at the TOP


//Every C Program has a main() routine
//This is where the program starts
int main ()
{
	//Program Starts here
	//kipr_drive_distance(float distanceCm, float speed, int direction);
	//kipr_spin_degrees(int degrees, int speed, int direction);
	
	kipr_drive_distance(10, 75, FWD);
	kipr_spin_degrees(360, 75, LEFT);
	kipr_drive_distance(10, 100, FWD);
	
	//SpinTickCounter(720, 50, LEFT);
	
	
	//Program ends here
	return 0;
}


