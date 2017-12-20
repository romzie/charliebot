#ifndef CONTROLLER_EXT_H
#define CONTROLLER_EXT_H

#include "Controller.h"

#define ki_teta 0.12
#define kp_teta 0.36
#define pi 3.141592
#define T 0.02
int cancer_speed_g;
int cancer_speed_d;
void Controller_O_v_g(_real);
void Controller_O_v_d(_real);

#endif 
