#include "Controller_ext.h"
#include "Controller.h"
#include "ecrobot_interface.h"

#define ROBOT_MAX_SPEED 35 // cm.s^-1
#define MAX_SPEED_PERCENT 60

int interp(_real v)
{
	int speed = (int) (v*100.0);

	if (speed > ROBOT_MAX_SPEED)
		speed = ROBOT_MAX_SPEED;
	if (speed < -ROBOT_MAX_SPEED)
		speed = -ROBOT_MAX_SPEED;

	speed = (speed*100)/ROBOT_MAX_SPEED;
	if (speed > MAX_SPEED_PERCENT)
		speed = MAX_SPEED_PERCENT;
	return speed;
}

void Controller_O_v_d(_real vd)
{
	int speed = interp(vd);
	cancer_speed_d = speed;
	nxt_motor_set_speed(NXT_PORT_A, speed, 1);
}

void Controller_O_v_g(_real vg)
{
	int speed = interp(vg);
	cancer_speed_g = speed;
	nxt_motor_set_speed(NXT_PORT_C, speed, 1);
}
