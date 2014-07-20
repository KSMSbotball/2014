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

	power.left_power = (int) (ADJUST_LEFT_MOTOR * speed);
	power.right_power = (int) (ADJUST_RIGHT_MOTOR * speed);

	return power;
}

WHEELS_MOTOR_POWER kipr_spin_powers(float speed, int direction) {
	WHEELS_MOTOR_POWER power;

	power.left_power = (int) (ADJUST_LEFT_MOTOR * speed);
	power.right_power = (int) (ADJUST_RIGHT_MOTOR * speed);

	return power;
}

void kipr_drive_distance(float distance, float speed, int direction) {
	clear_motor_position_counter(LEFT_MOTOR);
	kipr_drive(speed, direction);
	int ticks = distance * TICKS_PER_CENTIMETER;
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
