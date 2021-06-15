#ifndef SWITCH_H
#define SWITCH_H

#include "scheduler_configuration.h"
#include <reg52.h>

// if the family is 8051

#if (FAMILY == 51 )
 
  sbit switch_pin = P1^2;

#endif

// switch status

#define SWITCH_OFF 1

#define SWITCH_ON 0

#define SWITCH_PRESSED 0

// switch related numbers

#define SWITCH_THRESHOLD 3


#define SWITCH_THRESHOLD_B 5

// multi state switch related status
 
 #define SWITCH_STATUS_1 2
 
 #define SWITCH_STATUS_2 3

// used as global variable to know the status of the switch

extern unsigned char sw_status_G;

// initialize the switch 

void switch_init();


// reading the switch pin and update its status

void switch_manage();



// multi state switch



void switch_multiState_update();





#endif