#ifndef _KIPRMOVEMENT_H_
#define _KIPRMOVEMENT_H_

#define LEFT_MOTOR 2
#define RIGHT_MOTOR 0

#define ADJUST_LEFT_MOTOR .93
#define ADJUST_RIGHT_MOTOR 1.0

#define FWD 1
#define BACK -1
#define RIGHT -1
#define LEFT 1

#define PI 3.141592
#define WHEEL_DIAMETER = 4.3 //in cm
#define RIGHT_MOTOR_TICKS_PER_ROTATION 834
#define LEFT_MOTOR_TICKS_PER_ROTATION 849
#define TICKS_PER_DEGREE 8.72
// Calculate the following by:
//    ticks per centimeter = ticks per rotation / circumference of wheel
//                         = ticks per rotation / (diameter of wheel * pi)13.51
#define RIGHT_MOTOR_TICKS_PER_CENTIMETER 61.73
#define LEFT_MOTOR_TICKS_PER_CENTIMETER 62.84
#define TICKS_PER_CENTIMETER LEFT_MOTOR_TICKS_PER_CENTIMETER

typedef struct {
	int left_power;
	int right_power;
} WHEELS_MOTOR_POWER;

void kipr_drive(float speed, int direction); 
void kipr_spin(int speed, int direction);
void kipr_freeze();
void kipr_drive_distance(float distanceCM, float speed, int direction);
void kipr_spin_degrees(int degrees, int speed, int direction);

WHEELS_MOTOR_POWER kipr_drive_powers(float speed, int direction);
WHEELS_MOTOR_POWER kipr_spin_powers(float speed, int direction);

#endif
