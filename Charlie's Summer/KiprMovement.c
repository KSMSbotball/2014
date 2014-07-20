#include "KiprMovement.h"

void kipr_drive(float speed, int direction) {
	WHEELS_MOTOR_POWER power;
	power = kipr_drive_powers(speed, direction);

	motor(LEFT_MOTOR, power.left_power * direction);
	motor(RIGHT_MOTOR, power.right_power * direction);
}

void kipr_spin(int speed, int direction) {
	WHEELS_MOTOR_POWER power;
	power = kipr_spin_powers(speed, direction);

	motor(LEFT_MOTOR, power.left_power * -direction);
	motor(RIGHT_MOTOR, power.right_power * direction);
}

void kipr_freeze() {
	freeze(LEFT_MOTOR);
	freeze(RIGHT_MOTOR);
}

WHEELS_MOTOR_POWER kipr_drive_powers(float speed, int direction) {
	WHEELS_MOTOR_POWER power;
	if (direction == FWD)
	{
		if(speed > 90) //Set to 100
		{
			power.left_power = (int) (1.0 * 100);
			power.right_power = (int) (.99 * 100);
			printf("Power Set to FWD 100\n");
		}
		else if((speed <= 90) & (speed > 60)) //set to 75
		{
			power.left_power = (int) (.94 * 75);
			power.right_power = (int) (1.0 * 75);
			printf("Power Set to FWD 75\n");
		}
		else if(speed <= 60) //set to 50
		{
			power.left_power = (int) (.69 * 50);
			power.right_power = (int) (1.0 * 50);
			printf("Power Set to FWD 50\n");
		}
	}

	return power;
}

WHEELS_MOTOR_POWER kipr_spin_powers(float speed, int direction) {
	WHEELS_MOTOR_POWER power;

	if (direction == LEFT)
	{
		power.left_power = (int) (1.0 * 75);
		power.right_power = (int) (.98 * 75);
		printf("Power Set to LEFT 75\n");
		
		/*
		if(speed > 90) //Set to 100
		{
			power.left_power = (int) (1.0 * 100);
			power.right_power = (int) (1.0 * 100);
			printf("Power Set to LEFT 100\n");
		}
		else if((speed <= 90) & (speed > 60)) //set to 75
		{
			power.left_power = (int) (1.0 * 75);
			power.right_power = (int) (.98 * 75);
			printf("Power Set to LEFT 75\n");
		}
		else if(speed <= 60) //set to 50
		{
			power.left_power = (int) (1.0 * 50);
			power.right_power = (int) (1.0 * 50);
			printf("Power Set to LEFT 50\n");
		}
		*/
	}
	else if (direction == RIGHT)
	{
		power.left_power = (int) (.99 * 75);
		power.right_power = (int) (1.0 * 75);
		printf("Power Set to RIGHT 75\n");
		/*
		if(speed > 90) //Set to 100
		{
			power.left_power = (int) (1.0 * 100);
			power.right_power = (int) (1.0 * 100);
			printf("Power Set to RIGHT 100\n");
		}
		else if((speed <= 90) & (speed > 60)) //set to 75
		{
			power.left_power = (int) (.99 * 75);
			power.right_power = (int) (1.0 * 75);
			printf("Power Set to RIGHT 75\n");
		}
		else if(speed <= 60) //set to 50
		{
			power.left_power = (int) (1.0 * 50);
			power.right_power = (int) (1.0 * 50);
			printf("Power Set to RIGHT 50\n");
		}*/
	}

	return power;
}

void kipr_drive_distance(float distanceCM, float speed, int direction) {
	clear_motor_position_counter(LEFT_MOTOR);
	kipr_drive(speed, direction);
	int ticks = distanceCM * TICKS_PER_CENTIMETER;
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < ticks);
	kipr_freeze();
}

void kipr_spin_degrees(int degrees, int speed, int direction) {
	clear_motor_position_counter(LEFT_MOTOR);
	kipr_spin(speed, direction);
	int ticks = degrees * TICKS_PER_DEGREE;
	while (abs(get_motor_position_counter(LEFT_MOTOR)) < ticks);
	kipr_freeze();
}
