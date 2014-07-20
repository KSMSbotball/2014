#include "KiprTests.h"
#include "KiprMovement.h"

void DistanceTickCounter(int Distance, int Motor)
{
	clear_motor_position_counter(Motor);
	printf("Start Ticks Motor %d: %d\n", Motor, get_motor_position_counter(Motor));
	kipr_drive_distance(Distance, 50, FWD);
	printf("End Ticks Motor %d: %d\n", Motor, get_motor_position_counter(Motor));
}

void SpinTickCounter(int Degrees, int Speed, int Direction)
{
	clear_motor_position_counter(LEFT_MOTOR);
	printf("Start Ticks: %d\n", get_motor_position_counter(LEFT_MOTOR));
	kipr_spin_degrees(Degrees, Speed, Direction);
	printf("End Ticks: %d\n", get_motor_position_counter(LEFT_MOTOR));
}
