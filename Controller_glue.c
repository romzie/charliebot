#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "periods.h"

// GLUE CODE: include the Lustre generated header
#include "Controller.h"


/* OSEK specific code, DO NOT CHANGE */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);
void user_1ms_isr_type2(void) {
  StatusType ercd;
  ercd = SignalCounter(SysTimerCnt);
  /* Increment OSEK Alarm Counter */
  if(ercd != E_OK) { ShutdownOS(ercd); }
}
/* END OF OSEK specific code */

/* Init and terminate OSEK */
void ecrobot_device_initialize() {
   /* GLUE CODE:
		light sensor are ACTIVE devices and must be initialized
		(conversely to buttons, for instance)
   */
	ecrobot_set_light_sensor_active(NXT_PORT_S1);
	ecrobot_set_light_sensor_active(NXT_PORT_S2);
	ecrobot_init_sonar_sensor(NXT_PORT_S3);

}

void ecrobot_device_terminate() {
   /* GLUE CODE:
		light sensor must be switched off 
   */
	ecrobot_set_light_sensor_inactive(NXT_PORT_S1);
	ecrobot_set_light_sensor_inactive(NXT_PORT_S2);
	ecrobot_term_sonar_sensor(NXT_PORT_S3);
}


/* UsrTask */

/* GLUE CODE
	Since a SINGLE instance of teh Lustre gen. code is used,
	we can compile it using "-ctx-static" (cf. Makefile)
   making the interface simpler:
		- In particular, we don't have to "alocate" the node context:
   	the global, unique instance is declared in the generated.
		- all the "methods" (init, step input, output) have NO parameters
*/

  
/* GLUE CODE
	IMPORTANT !!!
	All used Lustre nodes MUST be initialized HERE
	using the procedure provided in the generated code
*/
void usr_init(void) {
	Controller_init();
}

/* GLUE CODE
	Output procedures
	Note: we directly use here the functions from 
	the "ecrobot" library (display_goto_xy, display_string etc)
*/
void robot_O_state(_boolean b){
   /* displays on 1st line */
   display_goto_xy(0,0);
   if (b) display_string("Sensor 1");
   else display_string("Sensor 2");
}
void robot_O_val(_integer i){
   /* displays on 2nd line */
   display_goto_xy(0,1);
   display_int(i,5);
}

/*
	GLUE CODE
	The "core" of a step:
   - read inputs from sensors and copy them to Lustre code
     using the corresponding input procedures
	- calls the step proc.
*/
TASK(UsrTask)
{
        static int initialized = 0;
        static int white_value_d = 0;
        static int black_value_d = 0;
        static int white_value_g = 0;
        static int black_value_g = 0;
        if (initialized == 0) {
                // initlialize white here
                // print getting white 
                display_goto_xy(0, 0);
                display_string("Blanc avec un K");
                if (ecrobot_is_ENTER_button_pressed()) {
                        initialized ++;
                        white_value_d = 
                                ecrobot_get_light_sensor(NXT_PORT_S1);
                        white_value_g = 
                                ecrobot_get_light_sensor(NXT_PORT_S2);
                        //get here the value of the white 
                }
                display_update();
                TerminateTask();
        }

        if (initialized == 1) {
                // initlialize white here
                // print getting white 
                display_goto_xy(0, 0);
                display_string("Blanc chargé");
                if (!ecrobot_is_ENTER_button_pressed()) {
                        initialized ++;
                }
                display_update();
                TerminateTask();
        }       

        if (initialized == 2) {
                // initialize black here 
                // print getting black
                display_goto_xy(0, 0);
                display_string("Noir avec un T");
                if (ecrobot_is_ENTER_button_pressed()) {
                        initialized ++;
                        black_value_d = 
                                ecrobot_get_light_sensor(NXT_PORT_S1);
                        black_value_g = 
                                ecrobot_get_light_sensor(NXT_PORT_S2);
                        //get here the value of the black
                }
                display_update();
                TerminateTask();
        }
        
        if (initialized == 3) {
                // initlialize white here
                // print getting white 
                display_goto_xy(0, 0);
                display_string("Noir chargé");
                if (!ecrobot_is_ENTER_button_pressed()) {
                        initialized ++;
                }
                display_update();
                TerminateTask();
        }

	ecrobot_device_initialize();
	int sensor_d = ecrobot_get_light_sensor(NXT_PORT_S1);
	int sensor_g = ecrobot_get_light_sensor(NXT_PORT_S2);
	int sensor_sonar = ecrobot_get_sonar_sensor(NXT_PORT_S3);
        
	sensor_d = 100 - (((sensor_d - white_value_d) * 100) 
                        / (black_value_d - white_value_d));
	sensor_g = 100 - (((sensor_g - white_value_g) * 100) 
                        / (black_value_g - white_value_g));

	if (sensor_d > 100) 
		sensor_d = 100;
	if (sensor_g > 100)
		sensor_g = 100;
	if (sensor_d < 0)
		sensor_d = 0;
	if (sensor_g < 0)
		sensor_g = 0;

	display_goto_xy(0, 0);
	display_string("Sensor D: ");
	display_goto_xy(11, 0);
	display_int(sensor_d, 5);

	display_goto_xy(0, 1);
	display_string("Sensor G: ");
	display_goto_xy(11, 1);
	display_int(sensor_g, 5);

	display_goto_xy(0, 2);
	display_string("Speed D: ");
	display_goto_xy(11, 2);
	display_int(cancer_speed_d, 5);

	display_goto_xy(0, 3);
	display_string("Speed G: ");
	display_goto_xy(11, 3);
	display_int(cancer_speed_g, 5);

	display_goto_xy(0, 4);
	display_string("Sonar Sensor: ");
	display_goto_xy(11, 4);
	display_int(sensor_sonar, 5);

	Controller_I_Cg((_real) sensor_g);
	Controller_I_Cd((_real) sensor_d);
	Controller_I_Co((_real) sensor_sonar);
	Controller_step();

	display_update();
	TerminateTask();
}
