#include "KiprMovement.h"
//Definitions Go at the TOP

#define LEFT_PORT_WHEEL 2
#define RIGHT_PORT_WHEEL 0
#define FAST 1000
#define SLOW 500



//Method Declarations 
void MoveForwardMillimeters(int mmToGo, int Speed);
void GoStraight(int HowLong, int HowFast);
void TurnLeft90();
void TurnRight90();
void GoBack(int Howlong);
void Slant();
void CorrectionRight(int HowFast,int HowLong);
void TickCounter(int TicksToGo);
//void BackUp();

//Every C Program has a main() routine
//This is where the program starts
int main ()
{
	//Program Starts here
	
	//Call method GoStraight
	//TickCounter(10000);
	//lego_spin_degrees(360,100, FWD);
	kipr_drive_distance(300,100,FWD);
	//MoveForwardMillimeters(2000, 1000);
	
	//GoStraight(7000,FAST);
	//TurnRight90();
	//GoStraight(12000,FAST);
	//Slant();
	//GoStraight(9000,FAST);
	//CorrectionRight(750,500);
	//GoStraight(5000,FAST);
	//BackUp();
	//Program ends here
	return 0;
}

//Methods defined at the top of the program
//are put here with their complete code\

void GoStraight(int HowLong, int HowFast)
{
	mav(RIGHT_PORT_WHEEL, HowFast);
	mav(LEFT_PORT_WHEEL, HowFast);
	msleep(HowLong);
}
void TurnRight90()
{
	mav(RIGHT_PORT_WHEEL, 0);
	mav(LEFT_PORT_WHEEL,750 );
	msleep(2300);
}
void TurnLeft90()
{
	mav(RIGHT_PORT_WHEEL, 750);
	mav(LEFT_PORT_WHEEL, 0);
	msleep(2200);	
}
void Slant()
{
	mav(RIGHT_PORT_WHEEL, 0);
	mav(LEFT_PORT_WHEEL, 750);
	msleep(1350);
}
void CorrectionRight(int HowFast,int HowLong)
{
	mav(RIGHT_PORT_WHEEL, 0);
	mav(LEFT_PORT_WHEEL, HowFast);
	msleep(HowLong);
}
//void BackUp()
//{
//mav(RIGHT_PORT_WHEEL, -750);
//mav(LEFT_PORT_WHEEL, -750);
//msleep(2000);
//}
