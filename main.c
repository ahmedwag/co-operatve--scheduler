
//OVERLAY (main ~ (switch_manage, led_update), sch_dispatcher ! (switch_manage, led_update))

#include <reg52.h>
#include "scheduler.h"
#include "switch.h"
#define LED_ON 1
#define LED_OFF 0

sbit led_bit = P1^0;

sbit led_bit2 = P1^1;


void led_init()
{
   led_bit = LED_OFF;
	 led_bit2 = LED_OFF;

}


void led_update(void)
{
		
		if(sw_status_G == SWITCH_STATUS_1 )
		{
			led_bit = LED_ON;
			led_bit2 = LED_OFF;
			
			
		}else if (sw_status_G == SWITCH_STATUS_2)
		{
				 
				 led_bit2 =LED_ON;
			   led_bit = LED_OFF;
			
		}else{
		  
			led_bit = LED_OFF;
			led_bit2 =LED_OFF;
		
		}
  
}










int main (void)
{
	
	
	sch_init();
	led_init();
	switch_init();
	sch_add_task(led_update,0,1000);
	sch_add_task(switch_multiState_update,0,200);
	
	
	sch_start();
	
	
	
	while(1)
	{
	
	  sch_dispatcher();
	
	}
	


}





