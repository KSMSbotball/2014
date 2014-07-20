#include "KiprTests.h"
#include "KiprMovement.h"

void TickCounter(int TicksToGo)
{
	clear_motor_position_counter(RIGHT_PORT_WHEEL);
	printf("Start Ticks: %d\n", get_motor_position_counter(RIGHT_PORT_WHEEL));
	kipr_drive_distance
	
	kipr_freeze();
	msleep(15000);
	printf("End Ticks: %d\n", get_motor_position_counter(RIGHT_PORT_WHEEL));
}
