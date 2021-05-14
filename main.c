
#include <reg52.h>
#include "scheduler.h"



#define LED_ON 1
#define LED_OFF 0

sbit led_bit = P1^0;


void led_update(void)
{
	
	if(led_bit == LED_ON )
	{
	  led_bit = LED_OFF;
	}else{
	     
	     led_bit =LED_ON;
	}
  
}


int main (void)
{
	
	
	sch_init();
	
	sch_add_task(led_update,0,1000);
	
	
	sch_start();
	
	
	
	while(1)
	{
	
	  sch_dispatcher();
	
	}
	
	





}